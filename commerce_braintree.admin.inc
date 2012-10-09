<?php 

include_once DRUPAL_ROOT . "/sites/all/libraries/braintree/lib/Braintree.php";

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
  
  if (!isset($bt_signature_param) || !isset($bt_signature_param)){
    watchdog('braintree', 'Commerce braintree no recive webhook data.', array('%action' => $verify));
    return FALSE;
  }
  
  $webhookNotification = Braintree_WebhookNotification::parse($bt_signature_param, $bt_payload_param);
  
  $kind = $webhookNotification->kind;
  $sid  = $webhookNotification->subscription->id;
  switch ($kind) {
    case Braintree_WebhookNotification::SUBSCRIPTION_CANCELED:
      module_invoke_all('cb_subscription_canceled', $kind, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_SUCCESSFULLY:
      module_invoke_all('cb_subscription_charged_successfully', $kind, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_CHARGED_UNSUCCESSFULLY:
      module_invoke_all('cb_subscription_charged_unsuccessfully', $kind, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_EXPIRED:
      module_invoke_all('cb_subscription_expired', $kind, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_TRIAL_ENDED:
      module_invoke_all('cb_subscription_trial_ended', $kind, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_WENT_ACTIVE:
      module_invoke_all('cb_subscription_went_active', $kind, $sid);
      break;
    case Braintree_WebhookNotification::SUBSCRIPTION_WENT_PAST_DUE:
      module_invoke_all('cb_subscription_went_past_due', $kind, $sid);
      break;
  }
  watchdog('braintree', 'Commerce braintree occur %action .', array('%action' => $webhookNotification->kind));
}


/**
 * Cancel braintree recurring billing by uid and plan id
 * @param type $sub
 * @return type
 */
function commerce_braintree_page_cancel($sub) {
  $uid  = $sub['uid'];
  $plan = $sub['planid'];
  $sub  = commerce_braintree_subscription_get_by_cid_planid($uid, $plan);
  if (!$sub) {
    $message = "Not found subscription with plan id is {$plan} and user id is {$uid}";
    drupal_set_message("Not found subscription with plan id <strong>{$plan}</strong> and user id <strong>{$uid}</strong>", "error");
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
  dsm($sub);
  $op       = commerce_braintree_product_get_by_order($order);
  $header   = array('Title', 'Price', 'Status', 'Operation');
  $price    = commerce_currency_format($op->commerce_price['und']['0']['amount'],$op->commerce_price['und']['0']['currency_code']);
  $status   = "Not found";
  if($sub) {
    $status = $sub->status;
  }
  $rows[] = array($op->title, $price, $status, l("cancel", "braintree/{$plan_id}/uid/{$order->uid}/cancel"));
  $output = theme('table', array('header' => $header,
                                 'rows'   => $rows ));
  return $output;
}


