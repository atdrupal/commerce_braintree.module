<?php


function commerce_braintree_subscription_views_data() {
  $data = array();

  $data['commerce_braintree_subscription']['table']['group']  = t('Commerce braintree subscription');

  $data['commerce_braintree_subscription']['table']['base'] = array(
    'field' => 'sid', 
    'title' => t('Braintree subscription'), 
    'help' => t('Braintree subscription.'), 
  );
  
  $data['commerce_braintree_subscription']['uid'] = array(
    'title' => t('Braintree subscription user id'), 
    'help' => t('The user id of subscription.'), 
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
  $data['commerce_braintree_subscription']['order_id'] = array(
    'title' => t('Braintree subscription order id'), 
    'help' => t('The subscription order id.'), 
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
  $data['commerce_braintree_subscription']['status'] = array(
    'title' => t('Braintree subscription status'), 
    'help' => t('The subscription status.'), 
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
  $data['commerce_braintree_subscription']['sid'] = array(
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
  $data['commerce_braintree_subscription']['created'] = array(
    'title' => t('Create date'), 
    'help' => t('The date subscription was created.'), 
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
  $data['commerce_braintree_subscription']['last_update'] = array(
    'title' => t('Last update'), 
    'help' => t('The date that subscription last update.'), 
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
  
  
  // Expose the owner uid.
  $data['commerce_braintree_subscription']['uid'] = array(
    'title' => t('User subscription'),
    'help' => t('Relate a profile to the user it belongs to.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('User subscription'),
    ),
  );
  // Expose the owner order_id.
  $data['commerce_braintree_subscription']['order_id'] = array(
    'title' => t('Order id of subscription'),
    'help' => t('Order relative commerce_order.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'commerce_order',
      'field' => 'order_id',
      'label' => t('Order id of subscription'),
    ),
  );
  
  // Expose links to cancel subscription.
  $data['commerce_braintree_subscription']['link_cancel_subscription'] = array(
    'field' => array(
      'title' => t('Link cancel'),
      'help' => t('Provide a simple link to cancel subscription.'),
      'handler' => 'commerce_braintree_subscription_handler_field_subscription_cancel_link',
    ),
  );
  
  return $data;
}