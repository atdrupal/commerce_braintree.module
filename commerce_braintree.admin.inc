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
    watchdog('braintree', 'Commerce braintree no recive webhook data.', array('%action' => $verify));
    return FALSE;
  }
  
  $web_hook = Braintree_WebhookNotification::parse($bt_signature_param, $bt_payload_param);
  
  $kind = $web_hook->kind;
  $sid  = $web_hook->subscription->id;
  $user = commerce_braintree_user_load($sid);
  commerce_braintree_callback_hook($kind, $user, $sid);
  commerce_braintree_webhook_log($kind, $sid);
  watchdog('braintree', 'Commerce braintree occur %action .', array('%action' => $webhookNotification->kind));
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
  if (empty($sid)) {
    $cid = $sid = $sub = -1;
    $kind .= " was failed";
  }
  else {
    $sub = commerce_braintree_subscription_get_by_id($sid);
    $cid = commerce_braintree_customer_get_by_token($sub->paymentMethodToken);
  }
  
  commerce_braintree_log_write($cid, $cid, $sid, 0, 'webhook callback',$kind);
}


/**
 * Cancel braintree recurring billing by uid and plan id
 * @param type $sub
 * @return type
 */
function commerce_braintree_page_cancel($sub) {
  $uid  = $sub['uid'];
  $plan = $sub['planid'];
  $user = user_load($uid);
  $er   = FALSE;
  if (!$user) {
    drupal_set_message(check_plain("User {$uid} doesnt exist"), 'error'); 
    $er = TRUE;
  }
  if (!commerce_braintree_plan_check($plan)) {
    drupal_set_message(check_plain("Plan {$plan} doesnt exist"), 'error'); 
    $er = TRUE;
  }
  if ($er) {
    return '<div></div>';
  }
  $sub  = commerce_braintree_subscription_get_by_cid_planid($uid, $plan);
  if (!$sub) {
    $message = check_plain("Not found subscription with plan id is {$plan} and user id is {$uid}");
    drupal_set_message($message, "error");
    return '<div>Faile</div>';
  }
  $result = commerce_braintree_subscription_cancel($sub->id, $message);
  drupal_set_message($message, $result ? "status" : "error");
  return '<div>' . $message . '</div>';
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
  
 
  $rows = commerce_braintree_subscription_load($user->uid);
  dsm($rows);return '<div>Faile</div>';
  foreach ($rows as $key => $value)
  $header   = array('Title', 'Price', 'Status', 'Operation');
  $plan_id  = commerce_braintree_planid_get($order);
  $rows[] = array($op->title, $price, $status, l(t("cancel"), "braintree/{$plan_id}/uid/{$order->uid}/cancel"));
  $output = theme('table', array('header' => $header,
                                 'rows'   => $rows ));
  return $output;
}

/**
 * Define form edit for customer
 * @global type $user
 * @return string
 */
function commerce_braintree_form_customer($form, &$form_state, $user) {
  $customer = commerce_braintree_customer_get($user->uid);
  if (is_object($customer)) {
    $creditcard = $customer->creditCards[0];
    $billing_address = $creditcard->billingAddress;
  }
  else {
    $customer = array();
    $creditcard = array();
    $billing_address = array();
  }
  
  $form['customer'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Customer Details'),
  );
  $form['customer']['c_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => isset($customer->firstName) ? $customer->firstName : '',
  );
  $form['customer']['c_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => isset($customer->lastName) ? $customer->lastName : '',
  );
  $form['customer']['c_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company'),
    '#default_value' => isset($customer->company) ? $customer->company : '',
  );
  $form['customer']['c_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => isset($customer->email) ? $customer->email : '',
  );
  $form['customer']['c_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => isset($customer->phone) ? $customer->phone : '',
  );
  $form['customer']['c_fax'] = array(
    '#type' => 'textfield',
    '#title' => t('Fax'),
    '#default_value' => isset($customer->fax) ? $customer->fax :'',
  );
  $form['customer']['c_website'] = array(
    '#type' => 'textfield',
    '#title' => t('Website'),
    '#default_value' => isset($customer->website) ? $customer->website : '',
  );
  
  $form['payment_method'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Payment Method Details'),
  );
  $form['payment_method']['ca_cardholder_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Cardholder Name'),
    '#default_value' => isset($creditcard->cardholderName) ? $creditcard->cardholderName : '',
  );
  $form['payment_method']['ca_card_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Credit Card Number'),
    //'#description' => t('Your private key'),
    '#default_value' => isset($creditcard->maskedNumber) ? $creditcard->maskedNumber : '',
    '#required' => TRUE,
  );
  $form['payment_method']['ca_exp_date'] = array(
    '#type' => 'textfield',
    '#title' => t('Expiration Date'),
    '#description' => t('Expiration Date (MM/YYYY)'),
    '#default_value' => isset($creditcard->expirationDate) ? $creditcard->expirationDate : '',
    '#required' => TRUE,
  );
  $form['payment_method']['ca_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Payment Method Token'),
    '#default_value' => isset($creditcard->token) ? $creditcard->token : '',
    '#disabled' => TRUE
  );
  $form['billing_address'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Billing Address'),
  );
  
  
  $form['billing_address']['ad_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => isset($billing_address->firstName) ? $billing_address->firstName :'' ,
  );
  $form['billing_address']['ad_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => isset($billing_address->lastName) ? $billing_address->lastName : '',
  );
  $form['billing_address']['ad_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company'),
    '#default_value' => isset($billing_address->company) ? $billing_address->company :'' ,
  );
  $form['billing_address']['ad_street_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Address'),
    '#default_value' => isset($billing_address->streetAddress) ? $billing_address->streetAddress : '' ,
  );
  $form['billing_address']['ad_extended_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Extended Address'),
    '#default_value' => isset($billing_address->extendedAddress) ? $billing_address->extendedAddress : '',
  );
  
  $form['billing_address']['ad_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City (Locality)'),
    '#default_value' => isset($billing_address->locality) ? $billing_address->locality : '',
  );
  $form['billing_address']['ad_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State/Province (Region)'),
    '#default_value' => isset($billing_address->region) ? $billing_address->region : '',
  );
  $form['billing_address']['ad_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#default_value' => isset($billing_address->postalCode) ? $billing_address->postalCode : '',
  );
  $form['billing_address']['ad_country_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Country Name'),
    '#default_value' => isset($billing_address->countryName) ? $billing_address->countryName : '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * validate form
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_form_customer_validate($form, &$form_state) {
  
}

/**
 * implement form submit
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_form_customer_submit($form, &$form_state) {
  global $user;
//  dsm($form_state);
  $token  = commerce_braintree_customer_get($user->uid);
  if (!$token) {
    return FALSE;
  }
  $token = $token->creditCards[0]->token;
  
  //billing address
  $billing_address['firstName']       = $form_state['values']['ad_first_name'];
  $billing_address['lastName']        = $form_state['values']['ad_last_name'];
  $billing_address['company']         = $form_state['values']['ad_company'];
  $billing_address['streetAddress']   = $form_state['values']['ad_street_address'];
  $billing_address['extendedAddress'] = $form_state['values']['ad_extended_address'];
  $billing_address['locality']        = $form_state['values']['ad_city'];
  $billing_address['region']          = $form_state['values']['ad_state'];
  $billing_address['postalCode']      = $form_state['values']['ad_postal_code'];
  $billing_address['countryName']     = $form_state['values']['ad_country_name'];
  
  //creditcard
  $creditcard['cardholderName'] = $form_state['values']['ca_cardholder_name'];
  $creditcard['number']         = $form_state['values']['ca_card_number'];
  $creditcard['expirationDate'] = $form_state['values']['ca_exp_date'];
  $creditcard['billingAddress'] = $billing_address;
  $creditcard['options']        = array('verifyCard' => TRUE, 'updateExistingToken' => $form_state['values']['ca_token'],
                                        'updateExistingToken' => $token
                                       );
  $creditcard['billingAddress']['options'] = array('updateExisting' => TRUE);
  
  //customer
  $customer['firstName']  = $form_state['values']['c_first_name'];
  $customer['lastName']   = $form_state['values']['c_last_name'];
  $customer['company']    = $form_state['values']['c_company'];
  $customer['email']      = $form_state['values']['c_email'];
  $customer['phone']      = $form_state['values']['c_phone'];
  $customer['fax']        = $form_state['values']['c_fax'];
  $customer['website']    = $form_state['values']['c_website'];
  $customer['creditCard'] = $creditcard;
  
  $result = commerce_braintree_customer_update($user->uid, $customer, $message);
  $status = 'status';
  if (!$result) {
    $status = 'error';
  }
  drupal_set_message(check_plain($message), $status);
}

/**
 * Define form to upgrade
 * @return type
 */
function commerce_braintree_form_upgrade() {
  $form = array();
  $form['profile'] = array(
    '#type' => 'select',
    '#title' => t('Choose a profile'),
    '#options' => commerce_braintree_product_list(),
  );  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Upgrade'),
  );
  return $form;
}

/**
 * Upgrade form submit
 * @global type $user
 * @param type $form
 * @param array $form_state
 */
function commerce_braintree_form_upgrade_submit($form, &$form_state) {
  global $user;
  $pid = $form_state['values']['profile'];
  $order = commerce_cart_order_load($user->uid);
  
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
  $select = db_select('commerce_product', 'c')
            ->fields('c')
            ->condition('type', $type)
            ->execute();
  if (!$select ) {
    return FALSE;
  }
  $products = array();
  foreach ( $select as $row ) {
    $products[$row->product_id] = $row->title;
  }
  return $products;
}

/**
 * Record columns
 * uid
 * cid
 * nid
 * timestamp
 * action
 * @param array $record
 */
function commerce_braintree_log_write($uid = 0, $cid = 0, $sid = NULL, $nid, $action, $message) {
  global $user;
  if ($uid == 0) {
    $uid = $user->uid;
  }
  if ($cid == 0) {
    $cid = $user->uid;
  }
  $record = array();
  $record['uid'] = $uid;
  $record['cid'] = $cid;
  $record['nid'] = $nid;
  $record['action'] = $action;
  $record['timestamp'] = REQUEST_TIME;
  $record['message'] = $message;
  drupal_write_record ("commerce_braintree_log", $record);
}