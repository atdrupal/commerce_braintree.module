<?php 
/**
 * @file
 * The form to update customer 
 *
 * Hook callback base braintree webhook
 * 
 * Status page and cancel link to orders views
 */

include_once DRUPAL_ROOT . "/sites/all/libraries/braintree/lib/Braintree.php";

/**
 * Build hook base braintree server webhook
 * @return boolean
 */
function commerce_braintree_webhook_callback() {
  $bt_challenge = "";
  commerce_braintree_initialize_library();

  // Handle the BT Destination Verification
  // https://www.braintreepayments.com/docs/php/webhooks/destination_verification
  if (isset($_GET['bt_challenge'])) {
    $bt_challenge = $_GET['bt_challenge'];
  }
  if (isset($bt_challenge) && $bt_challenge != "") {
    watchdog('braintree', 'Commerce braintree webhook destination verification accepted.');
    echo Braintree_WebhookNotification::verify($bt_challenge);
    exit();
  }
  
  if (!isset($_POST['bt_payload']) || !isset($_POST['bt_signature'])) {
    watchdog('braintree', 'Commerce braintree webhook recieved bad data', array(), WATCHDOG_ERROR);
    drupal_add_http_header('Status', '400 Bad Request');
    print t('Bad Request');
    exit();
  }
  
  try {
	  $bt_payload_param   = $_POST["bt_payload"];
	  $bt_signature_param = $_POST["bt_signature"];
	  
	  $webhook = Braintree_WebhookNotification::parse($bt_signature_param, $bt_payload_param);

	  $kind = $webhook->kind;
	  $sid  = $webhook->subscription->id;
	  watchdog('braintree', 'Commerce braintree webhook %kind for %sid .', array('%kind' => $kind, '%sid' => $sid));
	  commerce_braintree_webhook_process($kind, $sid);
	  print "Done kind: $kind, sid: $sid\n" . print_r($webhook, TRUE);
	  exit;
  }
  catch(Exception $e) {
    // Send 500 status if we have problems for what ever reason.
    // Should force BrainTree to resend the request.
    watchdog('braintree', "Commerce braintree webhook failed.\n<pre>HOOK:\n!webhook,\n\nEXCEPTION:\n!exception\n", array('!webhook' => print_r($webhook, TRUE), '!exception' => print_r($e, TRUE)), WATCHDOG_ERROR);
    drupal_add_http_header('Status', '500 Internal Server Error');
    print t('Failed to process');
    exit();
  }
}

function commerce_braintree_webhook_process($kind, $sid) {
  // TODO: Update these hook names to use braintree instead of cb prefix.
  $user = commerce_braintree_user_load_by_sid($sid);
  commerce_braintree_webhook_log($kind, $sid);

  switch ($kind) {
    case Braintree_WebhookNotification::SUBSCRIPTION_CANCELED:
      module_invoke_all('cb_subscription_canceled', $user, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_SUCCESSFULLY:
      module_invoke_all('cb_subscription_charged_successfully', $user, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_UNSUCCESSFULLY:
      module_invoke_all('cb_subscription_charged_unsuccessfully', $user, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_EXPIRED:
      module_invoke_all('cb_subscription_expired', $user, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_TRIAL_ENDED:
      module_invoke_all('cb_subscription_trial_ended', $user, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_WENT_ACTIVE:
      module_invoke_all('cb_subscription_went_active', $user, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_WENT_PAST_DUE:
      module_invoke_all('cb_subscription_went_past_due', $user, $sid);
      break;
    default:
      watchdog('braintree', t('We got a braintree Webhook, which is not programmed for.'), array(), WATCHDOG_ERROR);
      break;
  }
}

/**
 * Write webhook to log
 * @param type $kind
 * @param type $sid
 */
function commerce_braintree_webhook_log($kind, $sid) {
  $log = new stdClass();
  $log->action = COMMERCE_BRAINTREE_WEBHOOK_CALLBACK;
  $log->data = array('kind' => $kind, 'sid' => $sid);
  commerce_braintree_log_save($log);
}

/**
 * View status subscription on order
 * @param type $order
 * @return type
 */
function commerce_braintree_subscription_overview($user) {
  $results = commerce_braintree_subscription_load_by_user($user->uid);
  if ($results == FALSE) {
    return '<h4>' . t('You do not currently have subscriptions.') . '</h4>';
  }
  $rows []= array();
  foreach ($results as $row) {
    $order = commerce_order_load($row->order_id);
    $product = commerce_braintree_get_product_from_order($order);
    // TODO: This is not the place to do this. Slows down page load.
    // it should be done in cron.
    $sub = commerce_braintree_subscription_get_by_id($row->sid);
    if ($sub->status != $row->status) {
      commmerce_braintree_subscription_status_update($row->uid, $row->sid, $sub->status);
    }
    $status = $row->status;
    // TODO: Profiles are actually normal nodes, and not profile entities.
    // The $node->uid is the owner of the profile.
    $profile = commerce_braintree_get_profile_from_order($order);
    $price_display = commerce_currency_format($product->commerce_price[LANGUAGE_NONE]['0']['amount'], $product->commerce_price[LANGUAGE_NONE]['0']['currency_code'], $product);
   
    // TODO: All this information needs to get stored locally in the commerce_braintree_subscription table.
    // So that we don't have to look it up from BrainTree each time we need it.
    // This information needs to be syncronized via cron. 
    $first_billing_date = $sub->firstBillingDate->format('m/d/Y');
    $next_billing_date = (strcmp($sub->status, 'Canceled') != 0) ? $sub->nextBillingDate->format('m/d/Y') : '-';
    $billing_period_start_date = $sub->billingPeriodStartDate->format('m/d/Y');
    $billing_period_end_date = $sub->billingPeriodEndDate->format('m/d/Y');
    $paid_through_date = $sub->paidThroughDate->format('m/d/Y');
    $next_bill_amount = (strcmp($sub->status, 'Canceled') != 0) ? $sub->nextBillAmount : '-';
    
    $rows[] = array(l($profile->title, 'user/' . $row->uid . '/subscription/' . $row->sid), 
                $product->title,
                $price_display,
                $first_billing_date,
                $billing_period_start_date . ' - ' . $billing_period_end_date,
                $paid_through_date,
                $next_billing_date,
                $next_bill_amount,
                $status, 
                (strcmp($sub->status, 'Canceled') != 0) ? l(t("edit"), "user/{$row->uid}/subscription/{$row->sid}/update") : '',
                (strcmp($sub->status, 'Canceled') != 0) ? l(t("cancel"), "user/{$row->uid}/subscription/{$row->sid}/cancel") : '',
              );
  }
    
  $header = array('Profile', 'Subscription Type',
              'Price',
              'First Bill Date',
              'Current Billing Period',
              'Paid Through Date',
              'Next Bill Date',
              'Next Billing Period Amount', 
              'Status', 
              'Credit Card',
              'Cancel'
            );
  
  $output = theme('table', array('header' => $header,
                                 'rows'   => $rows ));
  return $output;
}

function commerce_braintree_subscription_page_view($user, $sid) {
  return t('This page should show details about a single subscription');
}

function commerce_braintree_subscription_page_update($user, $sid) {
  include_once('commerce_braintree.form.inc');
  //$sub = commerce_braintree_subscription_local_get(array('sid' => $sid));
  return drupal_get_form('commerce_braintree_creditcard_edit_form', $sid);
}

function commerce_braintree_subscription_page_cancel($user, $sid) {
  include_once('commerce_braintree.form.inc');
  $sub = commerce_braintree_subscription_local_get(array('sid' => $sid));
  return drupal_get_form('commerce_braintree_subscription_cancel_form', $sub['pid']);
}

function commerce_braintree_subscription_page_webhooks($user, $sid) {
  return drupal_get_form('commerce_braintree_subscription_page_webhooks_form', $user, $sid);
}

function commerce_braintree_subscription_page_webhooks_form($form, $form_state, $user, $sid) {
  $options = array(
      Braintree_WebhookNotification::SUBSCRIPTION_CANCELED                => Braintree_WebhookNotification::SUBSCRIPTION_CANCELED,
      Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_SUCCESSFULLY    => Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_SUCCESSFULLY,
      Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_UNSUCCESSFULLY  => Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_UNSUCCESSFULLY,
      Braintree_WebhookNotification::SUBSCRIPTION_EXPIRED                 => Braintree_WebhookNotification::SUBSCRIPTION_EXPIRED,
      Braintree_WebhookNotification::SUBSCRIPTION_TRIAL_ENDED             => Braintree_WebhookNotification::SUBSCRIPTION_TRIAL_ENDED,
      Braintree_WebhookNotification::SUBSCRIPTION_WENT_ACTIVE             => Braintree_WebhookNotification::SUBSCRIPTION_WENT_ACTIVE,
      Braintree_WebhookNotification::SUBSCRIPTION_WENT_PAST_DUE           => Braintree_WebhookNotification::SUBSCRIPTION_WENT_PAST_DUE,
      );

  $form['disclaimer']['#type'] = 'item';
  $form['disclaimer']['#markup'] = t('Once the site is live, never used this feature, unless it\'s on a test account.');

  $form['uid'] = array(
      '#type' => 'value',
      '#value' => $user->uid,
      );

  $form['sid'] = array(
      '#type' => 'value',
      '#value' => $sid,
      );

  $form['webhook_action'] = array(
      '#title' => t('Webhook action'),
      '#type' => 'select',
      '#options' => $options,
      );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
      );
  return $form;
}

function commerce_braintree_subscription_page_webhooks_form_submit($form, $form_state) {
  commerce_braintree_initialize_library();

  $sample = Braintree_WebhookTesting::sampleNotification(
      $form_state['values']['webhook_action'],
      $form_state['values']['sid']
      );

  $payment = commerce_payment_method_instance_load('braintree|commerce_payment_braintree');
  $webhook_path = $payment['settings']['webhook_link'];
  $query = array('bt_signature' => $sample['signature'], 'bt_payload' => $sample['payload']);

  $result = drupal_http_request(url($webhook_path, array('absolute' => TRUE)), array(
        'method' => 'POST',
        'data' => http_build_query($query, '', '&'),
        'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
        ));

  if(function_exists('dpm')) {
    // Too lazy to check watchdog each time.
    dpm(array('submit' => $form, 'form_state' => $form_state, 'sampleNotification' => $sample, 'result' => $result));
  }
  watchdog('braintree', "Test Webhook: <pre>FORM:---------------\n@form\n\n"
      . "FORM_STATE--------------------\n@from_state\n\n"
      . "SAMPLENOTIFICATION------------\n@sample\n\n"
      . "RESULT------------------------\n@result</pre>",
      array('@form' => print_r($form, TRUE), "@form_state" => print_r($form_state, TRUE), "@sample" => print_r($sample, TRUE), "@result" => print_r($result, TRUE))
      );

  drupal_set_message('Submitted test webhook. Check watchdog for result.');
}

