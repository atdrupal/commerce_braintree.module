<?php

/**
 * Form edit credit card by token
 * @param type $form
 * @param type $form_state
 * @param type $token
 * @return type
 */
function commerce_braintree_creditcard_edit_form($form, &$form_state, $token) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');
  $payment = commerce_payment_method_instance_load('braintree|commerce_payment_braintree');
  $creditcard = commerce_braintree_creditcard_get_by_token($token);
  $billing_address = $creditcard->billingAddress;
  
  $form['payment_method'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Payment Method Details'),
  );
  $form['payment_method']['ca_cardholder_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Cardholder Name'),
    '#default_value' => isset($creditcard->cardholderName) ? $creditcard->cardholderName : '',
  );
  $form['payment_method']['ca_token'] =  array('#type' => 'hidden', '#value' => $token);
  
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
  
  // Prepare the fields to include on the credit card form.
  $fields = array(
    'code' => '',
  );

  // Add the credit card types array if necessary.
  $card_types = array_diff(array_values($payment['settings']['card_types']), array(0));
  if (!empty($card_types)) {
    $fields['type'] = $card_types;
  }
  
  $defaults = array(
    'type' => $creditcard->cardType,
    'number' => isset($creditcard->maskedNumber) ? $creditcard->maskedNumber : '', 
    'exp_month' => $creditcard->expirationMonth, 
    'exp_year' => $creditcard->expirationYear,
  );

  $form['payment_method'] += commerce_payment_credit_card_form($fields, $defaults);
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Validate credit card
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_creditcard_edit_form_validate($form, &$form_state) {
  // Ensure non-default values are valid numbers.
  if (!commerce_payment_validate_credit_card_number($form_state['values']['credit_card']['number'])) {
      form_set_error('credit_card][number', t('The credit card number you entered is invalid.'));
  }
  // Ensure the expiration date is not being updated to a past date.
  $exp_valid = commerce_payment_validate_credit_card_exp_date($form_state['values']['credit_card']['exp_month'], $form_state['values']['credit_card']['exp_year']);

  if ($exp_valid !== TRUE) {
    form_set_error('credit_card][exp_' . $exp_valid, t('You have specified an expired credit card.'));
  }
}

/**
 * Form edit credit card submit
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_creditcard_edit_form_submit($form, &$form_state) {
  $token  = $form_state['values']['ca_token'];
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
  $creditcard['number']         = $form_state['values']['credit_card']['number'];
  $creditcard['cvv']            = $form_state['values']['credit_card']['code'];
  $creditcard['expirationDate'] = $form_state['values']['credit_card']['exp_month'];
  $creditcard['expirationDate'] .= '/' . $form_state['values']['credit_card']['exp_year'];
  $creditcard['billingAddress'] = $billing_address;
  $creditcard['options']        = array('verifyCard' => TRUE);
  $creditcard['billingAddress']['options'] = array('updateExisting' => TRUE);
  
  commerce_braintree_credit_card_update($creditcard, $token);
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
 * Cancel braintree recurring billing by uid and plan id
 * @param type $sub
 * @return type
 */
function commerce_braintree_subscription_cancel_form($form, &$form_state, $pid) {
  $sub = commerce_braintree_subscription_local_get(array('pid' => $pid));
  $form['sid'] = array('#type' => 'value', '#value' => $sub['sid']);
  $profile = profile2_load($pid);
  $output = confirm_form($form,
    t('Are you sure you want to cancel the subscription %pid?', array('%pid' => $profile->label)),
    'user/' . $GLOBALS['user']->uid . '/subscription',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel'),
    'confirm'
  );
  return $output;
}

function commerce_braintree_subscription_cancel_form_submit($form, &$form_state) {
  $sid = $form_state['values']['sid'];
  $result = commerce_braintree_subscription_cancel($sid, $message);
  $form_state['redirect'] = 'user/' . $GLOBALS['user']->uid . '/subscription';
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

