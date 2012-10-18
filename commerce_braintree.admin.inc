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
function commerce_braintree_hooks() {
  commerce_braintree_initialize_library();
  $bt_challenge = "";
  if (isset($_GET['bt_challenge'])) {
    $bt_challenge = $_GET['bt_challenge'];
  }
  if (isset($bt_challenge) && $bt_challenge != "") {
    echo Braintree_WebhookNotification::verify($bt_challenge);
    exit();
  }
  
  $bt_payload_param   = $_POST["bt_payload"];
  $bt_signature_param = $_POST["bt_signature"];
  
  if (!isset($bt_signature_param) || !isset($bt_signature_param)) {
    watchdog('braintree', 'Commerce braintree no recive webhook data.');
    return FALSE;
  }
  
  $web_hook = Braintree_WebhookNotification::parse($bt_signature_param, $bt_payload_param);
  
  $kind = $web_hook->kind;
  $sid  = $web_hook->subscription->id;
  watchdog('braintree', 'Commerce braintree occur %kind .', array('%kind' => $kind));
  $user = commerce_braintree_user_load_by_sid($sid);
  commerce_braintree_callback_hook($kind, $user, $sid);
  commerce_braintree_webhook_log($kind, $sid);
  
}

function commerce_braintree_callback_hook($kind, $user, $sid) {
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
  }
}


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
function commerce_braintree_subscription_view($order) {
  $plan_id  = commerce_braintree_planid_get($order);
  $sub      = commerce_braintree_subscription_get_by_cid_planid($order->uid, $plan_id);
  $op       = commerce_braintree_product_get_by_order($order);
  $header   = array('Title', 'Price', 'Status', 'Operation');
  $price    = commerce_currency_format($op->commerce_price['und']['0']['amount'], $op->commerce_price['und']['0']['currency_code']);
  $status   = "Not found";
  if ($sub) {
    $status = $sub->status;
  }
  $rows[] = array($op->title, $price, $status, l(t("cancel"), "braintree/{$plan_id}/uid/{$order->uid}/cancel"));
  $output = theme('table', array('header' => $header,
                                 'rows'   => $rows ));
  return $output;
}
/**
 * View status subscription on order
 * @param type $order
 * @return type
 */
function commerce_braintree_subscription_overview($user) {
  $resluts = commerce_braintree_subscription_load_by_user($user->uid);
  if ($resluts == FALSE) {
    return "<h4>Don't data<h4>";
  }
  $rows []= array();
  foreach ($resluts as $row) {
    $order = commerce_order_load($row->order_id);
    $product = commerce_braintree_product_get_by_order($order);
    $sub = commerce_braintree_subscription_get_by_id($row->sid);
    if ($sub->status != $row->status) {
      commmerce_braintree_subscription_status_update($row->uid, $row->sid, $sub->status);
    }
    $status = $sub->status;
    $price = $sub->price;
    //$plan_id = (strcmp($sub->status, 'Canceled') != 0) ? $sub->planId : '';
    
    $first_billing_date = $sub->firstBillingDate->format('m/d/Y');
    $next_billing_date = (strcmp($sub->status, 'Canceled') != 0) ? $sub->nextBillingDate->format('m/d/Y') : '-';
    $billing_period_start_date = $sub->billingPeriodStartDate->format('m/d/Y');
    $billing_period_end_date = $sub->billingPeriodEndDate->format('m/d/Y');
    $paid_through_date = $sub->paidThroughDate->format('m/d/Y');
    $next_bill_amount = (strcmp($sub->status, 'Canceled') != 0) ? $sub->nextBillAmount : '-';
    $rows[] = array($product->title, 
                $price,
                $first_billing_date,
                $billing_period_start_date . ' - ' . $billing_period_end_date,
                $paid_through_date,
                $next_billing_date,
                $next_bill_amount,
                $status, 
                (strcmp($sub->status, 'Canceled') != 0) ? l(t("cancel"), "braintree/{$sub->id}/cancel") : ''
              );
  }
    
  $header = array('Title', 
              'Price',
              'First Bill Date',
              'Current Billing Period',
              'Paid Through Date',
              'Next Bill Date',
              'Next Billing Period Amount', 
              'Status', 
              'Operation'
            );
  
  $output = theme('table', array('header' => $header,
                                 'rows'   => $rows ));
  return $output;
}


/**
 * Upgrade form submit
 * @global type $user
 * @param type $form
 * @param array $form_state
 */
function commerce_braintree_form_upgrade_submit($form, &$form_state) {
  $pid = $form_state['values']['profile'];
  $order = commerce_cart_order_load($GLOBALS['user']->uid);
  
  if (!empty($order->commerce_line_items)) {
    $line_items = array_shift($order->commerce_line_items);
    foreach ($line_items as $item) {
      commerce_cart_order_product_line_item_delete($order, $item['line_item_id']);
    }
  }
  $order = commerce_cart_product_add_by_id($pid);
  $form_state['redirect'] = "checkout/{$order->order_id}";
}

/**
 * Get all product 
 * @param type $type
 * @return boolean
 */
function commerce_braintree_product_list($type = 'product') {
  $selects = db_select('commerce_product', 'c')
            ->fields('c')
            ->condition('type', $type)
            ->execute();
  if (!$selects ) {
    return FALSE;
  }
  $products = array();
  foreach ( $selects as $row ) {
    $products[$row->product_id] = $row->title;
  }
  return $products;
}

