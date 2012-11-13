<?php
/**
 * @file
 * Implementation hook_views_data to intergrate views with table commerce_braintree_subscription
 */

/**
 * Implementation of hook_views_api().
 */



function subscription_informations_views_data() {
  $data = array();

  $data['commerce_braintree_subscription_informations']['table']['group']  = t('Commerce braintree subscription informations');

  $data['commerce_braintree_subscription_informations']['table']['base'] = array(
    'field' => 'sid', 
    'title' => t('Braintree subscription informations'), 
    'help' => t('Braintree subscription informations.'), 
  );
  
  $data['commerce_braintree_subscription_informations']['price'] = array(
    'title' => t('The price'), 
    'help' => t('The price.'), 
    'field' => array(
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['commerce_braintree_subscription_informations']['next_billing_period_amount'] = array(
    'title' => t('The next billing period amount'), 
    'help' => t('The price.'), 
    'field' => array(
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  
  $data['commerce_braintree_subscription_informations']['sid'] = array(
    'title' => t('Braintree subscription id'), 
    'help' => t('The subscription id.'), 
    'field' => array(
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['commerce_braintree_subscription_informations']['plan_id'] = array(
    'title' => t('The plan id'), 
    'help' => t('The plan id.'), 
    'field' => array(
      'click sortable' => TRUE,
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort',
    ), 
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['commerce_braintree_subscription_informations']['first_bill_date'] = array(
    'title' => t('first_bill_date'), 
    'help' => t('The first bill date.'), 
    'field' => array(
      'handler' => 'views_handler_field_date', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['commerce_braintree_subscription_informations']['billing_period_start_date'] = array(
    'title' => t('The billing period start date.'), 
    'help' => t('The billing period start date.'), 
    'field' => array(
      'handler' => 'views_handler_field_date', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['commerce_braintree_subscription_informations']['billing_period_end_date'] = array(
    'title' => t('The billing period end date.'), 
    'help' => t('The billing period end date.'), 
    'field' => array(
      'handler' => 'views_handler_field_date', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['commerce_braintree_subscription_informations']['paid_through_date'] = array(
    'title' => t('The paid through date.'), 
    'help' => t('The paid through date.'), 
    'field' => array(
      'handler' => 'views_handler_field_date', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['commerce_braintree_subscription_informations']['next_bill_date'] = array(
    'title' => t('The next bill date.'), 
    'help' => t('The next bill date.'), 
    'field' => array(
      'handler' => 'views_handler_field_date', 
      'click sortable' => TRUE,
    ), 
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ), 
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  
  return $data;
}