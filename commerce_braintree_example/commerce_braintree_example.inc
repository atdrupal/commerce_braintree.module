<?php

/**
 * Define form edit for customer
 * @global type $user
 * @return string
 */
function commerce_braintree_example_form_customer() {
  
  global $user;
  $is_new = FALSE;
  //$customer = commerce_braintree_customer_get($user->uid);
  $customer = commerce_braintree_customer_get(5);
  if (is_object($customer)) {
    $creditcard = $customer->creditCards[0];
    $billing_address = $creditcard->billingAddress;
  }
  else {
    $customer = array();
    $creditcard = array();
    $billing_address = array();
    $is_new = TRUE;
    variable_set('commerce_braintree_example_is_new', TRUE);
  }
  
  dsm($customer);
  dsm($creditcard);
  dsm($billing_address);

  
  $form = array();
  
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
  $form['payment_method']['ca_exp_date '] = array(
    '#type' => 'textfield',
    '#title' => t('Expiration Date '),
    '#description' => t('Expiration Date (MM/YYYY)'),
    '#default_value' => isset($creditcard->expirationDate) ? $creditcard->expirationDate : '',
    '#required' => TRUE,
  );
  $form['payment_method']['ca_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Payment Method Token'),
    '#default_value' => isset($creditcard->token) ? $creditcard->token : '',
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
    '#value' => $is_new ? t('Create') : t('Save'),
  );
  
  return $form;
}


/**
 * validate form
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_example_form_customer_validate($form, &$form_state) {
  
}

/**
 * implement form submit
 * @param type $form
 * @param type $form_state
 */
function commerce_braintree_example_form_customer_submit($form, &$form_state) {
  global $user;
  $is_new = variable_get('commerce_braintree_example_is_new', FALSE);
  //billing address
  $billing_address['firstName']       = $form_state['values ']['ad_first_name'];
  $billing_address['lastName']        = $form_state['values ']['ad_last_name'];
  $billing_address['company']         = $form_state['values ']['ad_company'];
  $billing_address['streetAddress']   = $form_state['values ']['ad_street_address'];
  $billing_address['extendedAddress'] = $form_state['values ']['ad_extended_address'];
  $billing_address['locality']        = $form_state['values ']['ad_city'];
  $billing_address['region']          = $form_state['values ']['ad_state'];
  $billing_address['postalCode']      = $form_state['values ']['ad_postal_code'];
  $billing_address['countryName']     = $form_state['values ']['ad_country_name'];
  
  //creditcard
  $creditcard['cardholderName'] = $form_state['values ']['ca_cardholder_name'];
  $creditcard['expirationDate'] = $form_state['values ']['ca_exp_date'];
  $creditcard['billingAddress'] = $billing_address;
  $creditcard['options']        = array('verifyCard' => TRUE);
  
  //customer
  $customer['firstName']  = $form_state['values ']['c_first_name '];
  $customer['lastName']   = $form_state['values ']['c_last_name'];
  $customer['company']    = $form_state['values ']['c_company'];
  $customer['email']      = $form_state['values ']['c_emai'];
  $customer['phone']      = $form_state['values ']['c_phone'];
  $customer['fax']        = $form_state['values ']['c_fax'];
  $customer['creditCard'] = $creditcard;
  if ($is_new) {
    $result = commerce_braintree_customer_create($customer);
    if ($result->success) {
      drupal_set_message(t('Create customer successfull') , 'status');
    } 
    else {
      drupal_set_message(t('Cannot create customer') , 'error');
    }
  }
  else {
    commerce_braintree_customer_update($user->uid,$customer);
  }
  
  
}



 
function commerce_braintree_example_form_customer_cancel() {
  global $user;
  $form = array();
  $sub = commerce_braintree_subscription_get_by_cid($user->uid);
  if (!$sub) {
    $title = t('You are not subsciption');
  }
  else {
    $title = t('Are you sure you want to cancel');
  }
    
  $form['description'] = array(
    '#type' => 'item', 
    '#title' =>  $title,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Ok'),
  );
  return $form;
}

function commerce_braintree_example_form_customer_cancel_submit($form, &$form_state) {
  global $user;
  $sub = commerce_braintree_subscription_get_by_cid($user->uid);
  commerce_braintree_subscription_cancel($sub->id);
  drupal_set_message(t("cancel success"),"status");
}