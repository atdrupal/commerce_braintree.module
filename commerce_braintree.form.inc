<?php

/**
 * Define form edit for customer
 * @global type $user
 * @return string
 */
function commerce_braintree_form_customer($form, &$form_state, $user) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');
  $payment = commerce_payment_method_instance_load('braintree|commerce_payment_braintree');
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
 * validate form
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_form_customer_validate($form, &$form_state) {
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
 * implement form submit
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_form_customer_submit($form, &$form_state) {
  $token  = commerce_braintree_customer_get($GLOBALS['user']->uid);
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
  $creditcard['number']         = $form_state['values']['credit_card']['number'];
  $creditcard['expirationDate'] = $form_state['values']['credit_card']['exp_month'];
  $creditcard['expirationDate'] .= '/' . $form_state['values']['credit_card']['exp_year'];
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
  
  $result = commerce_braintree_customer_update($GLOBALS['user']->uid, $customer, $message);
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
 * Cancel braintree recurring billing by uid and plan id
 * @param type $sub
 * @return type
 */
function commerce_braintree_subscription_cancel_form($form, &$form_state, $sid) {
  
  $form['sid'] = array('#type' => 'value', '#value' => $sid);

  $output = confirm_form($form,
    t('Are you sure you want to cancel the subscription %sid?', array('%sid' => $sid)),
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

