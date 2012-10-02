<?php 

include_once DRUPAL_ROOT . "/sites/all/libraries/braintree/lib/Braintree.php";

/**
 * define form setting url receive trigger from braintree
 * @return string
 */
function commerce_braintree_webhooks_link_form() {
  $form['commerce_braintree_link'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#description' => t('URL revice trigger from braintree'),
    '#default_value' => variable_get('commerce_braintree_link'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * set values when submit form
 * @param type $form_state
 */
function commerce_braintree_webhooks_link_form_submit(&$form_state) {
  dsm($form_state);
  variable_set('commerce_braintree_link', $form_state['commerce_braintree_link']['#value']);
  menu_cache_clear_all();
}


function commerce_braintree_hooks() {
  commerce_braintree_initialize_library();
  $bt_challenge = "";
  if (isset($_GET['bt_challenge'])) {
    $bt_challenge = $_GET['bt_challenge'];
  }
  if (isset($bt_challenge) && $bt_challenge != "") {
    $verify = Braintree_WebhookNotification::verify($bt_challenge);
    echo $verify;
    watchdog('actions', 'Commerce braintree %action verify .', array('%action' => $verify));
    exit();
  }
  
  $bt_signature_param = $_POST["bt_signature"];
  $bt_payload_param = $_POST["bt_payload"];
  $webhookNotification = Braintree_WebhookNotification::parse(
    $bt_signature_param, $bt_payload_param
  );
  
  $webhookNotification->kind;
  # => "subscription_went_past_due"

  $webhookNotification->timestamp;
  # => Sun Jan 1 00:00:00 UTC 2012

  $webhookNotification->subscription->id;
  watchdog('actions', 'Commerce braintree %action .', array('%action' => $webhookNotification->kind));
  
  
}