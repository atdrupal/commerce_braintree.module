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
    //watchdog('actions', 'Commerce braintree %action verify .', array('%action' => $verify));
    exit();
  }
  
  $bt_payload_param   = $_POST["bt_payload"];
  $bt_signature_param = $_POST["bt_signature"];
  
  if (!isset($bt_signature_param) || !isset($bt_signature_param))    return FALSE;
  
  $webhookNotification = Braintree_WebhookNotification::parse($bt_signature_param, $bt_payload_param);
  
  $kind = $webhookNotification->kind;
  $sid = $webhookNotification->subscription->id;
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
  watchdog('actions', 'Commerce braintree %action .', array('%action' => $webhookNotification->kind));
}

/**
 * Add field to bundle
 * @param type $entity_type
 * @param type $bundle
 * @param type $label
 * @return type
 */
function commerce_braintree_add_field($entity_type, $bundle , $label) {
  $field = field_info_field('field_braintree_planid');
  $instance = field_info_instance($entity_type, 'field_braintree_planid', $bundle);
  if (empty($field)) {
    $field = array(
      'field_name' => 'field_braintree_planid', 
      'type' => 'text_textfield', 
      'entity_types' => array($entity_type),
    );
    $field = field_create_field($field);
  }
  if (empty($instance)) {
    $instance = array(
      'field_name' => 'field_braintree_planid', 
      'entity_type' => $entity_type, 
      'bundle' => $bundle, 
      'label' => $label, 
      'widget' => array('type' => 'text_textfield'), 
      'display' => array(
        'default' => array(
          'label' => 'hidden', 
          'type' => 'text_default',
        ), 
        'teaser' => array(
          'label' => 'hidden', 
          'type' => 'text_default',
        ),
      ),
    );
    $instance = field_create_instance($instance);
  }
  return $instance;
}