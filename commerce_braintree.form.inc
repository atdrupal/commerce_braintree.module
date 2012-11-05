<?php

/**
 * Form edit credit card by token
 * @param type $form
 * @param type $form_state
 * @param type $token
 * @return type
 */
function commerce_braintree_creditcard_edit_form($form, &$form_state, $sid) {
  module_load_include('inc', 'commerce_payment', 'includes/commerce_payment.credit_card');

  $sub = commerce_braintree_subscription_local_get(array('sid' => $sid), FALSE);

  $payment = commerce_payment_method_instance_load('braintree|commerce_payment_braintree');
  $creditcard = commerce_braintree_creditcard_get_by_token($sub['token']);
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
  // NOTE: A hidden field is changable via Firebug. Value is not.
  // Because there's no validation, this would have allowed any user with access to this form
  // to change any credit card on the website for any user, providing they guess another ca_token.
  //$form['payment_method']['ca_token'] =  array('#type' => 'value', '#value' => $token);
  $form['payment_method']['sid'] = array('#type' => 'value', '#value' => $sid);
  
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
  $sub = commerce_braintree_subscription_local_get(array('sid' => $form_state['values']['sid']), FALSE);
  // Double check to make sure there's no funny business going on. Shouldn't happen...
  // but doesn't hurt to double check.
  if($sub['uid'] != $GLOBALS['user']->uid && (!user_access('edit any credit card'))) {
    form_set_error('', t('You don\'t have permission to edit this subscription'));
  }
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
  $sub = commerce_braintree_subscription_local_get(array('sid' => $form_state['values']['sid']), FALSE);
  $token  = $sub['token'];
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
  $form['profile_nid'] = array(
    '#type' => 'select',
    '#title' => t('Choose a profile'),
    '#options' => commerce_braintree_profile_list(),
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
  $profile = node_load($pid);
  $output = confirm_form($form,
    t('Are you sure you want to cancel the subscription %title?', array('%title' => $profile->title)),
    'user/' . $GLOBALS['user']->uid . '/subscription',
    t('This action cannot be undone.'),
    t('Yes'), t('Cancel'),
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
  $nid = $form_state['values']['profile_nid'];

  $order = commerce_cart_order_load($GLOBALS['user']->uid);
 
  // clear existing cart. 
  if (!empty($order->commerce_line_items)) {
    $line_items = array_shift($order->commerce_line_items);
    foreach ($line_items as $item) {
      commerce_cart_order_product_line_item_delete($order, $item['line_item_id']);
    }
  }

  // TODO: Add some verification to make sure select field was not tampered with and that
  // this user can purchase subscription for profile node in question.
  $line_item_data = array(
      'profile_nid' => $nid,
      );
  $product_id = commerce_braintree_get_product_from_profile_nid($nid);
  $line_item = commerce_braintree_product_add_by_id($product_id, $line_item_data);
  $form_state['redirect'] = "checkout/{$line_item->order_id}";
}

function commerce_braintree_product_add_by_id($product_id, $data = array(), $quantity = 1, $combine = TRUE, $uid = NULL) {
  global $user;

  // If the specified product exists...
  if ($product = commerce_product_load($product_id)) {
    // Create a new product line item for it.
    $line_item = commerce_product_line_item_new($product, $quantity, 0, $data);

    // Default to the current user if a uid was not passed in.
    if ($uid === NULL) {
      $uid = $user->uid;
    }

    return commerce_cart_product_add($uid, $line_item, $combine);
  }

  return FALSE;
}

function commerce_braintree_get_product_from_profile_nid($profile_nid) {
  $profile = node_load($profile_nid);
  return commerce_braintree_get_product_from_profile($profile);
}

function commerce_braintree_get_product_from_profile($profile) {
  $products = commerce_braintree_get_products();
  foreach($products as $product_id => $bt_planid) {
    if($profile->type == $bt_planid) {
      return $product_id;
    }
  }
  return NULL;
}

function commerce_braintree_get_products() {
  $query = db_select('commerce_product', 'c');
  $query->join('field_data_field_braintree_planid', 'p', 'c.product_id = p.entity_id AND c.type=p.bundle');
  $query->fields('c', array('product_id'))
    ->fields('p', array('field_braintree_planid_value'))
    ->condition('type', 'product');

  $result = $query->execute();

  foreach($result as $record) {
    $products[$record->product_id] = $record->field_braintree_planid_value;
  }
  return $products;
}

/**
 * Get all product 
 * @param type $type
 * @return boolean
 */

function commerce_braintree_profile_list($account = NULL) {
  if(empty($account)) {
    $account = $GLOBALS['user'];
  }
  $products = commerce_braintree_get_products();

  $results = db_select('node', 'n')
            ->fields('n', array('title', 'nid'))
            ->condition('type', array_values($products), 'IN')
            ->condition('status', 1)
            ->condition('uid', $account->uid)
            ->execute();
  if (!$results) {
    return FALSE;
  }
  $profiles = array();
  foreach($results as $record) {
    $profiles[$record->nid] = $record->title;
  }
  return $profiles;
}

