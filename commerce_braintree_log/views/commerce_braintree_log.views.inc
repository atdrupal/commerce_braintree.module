<?php
/**
 * @file
 * Implementation hook_views_data to intergrate views with tables commerce_braintree_log
 */

/**
 * Implementation of hook_views_data().
 * @return type
 */
function commerce_braintree_log_views_data() {
  $data = array();

  $data['commerce_braintree_log']['table']['group']  = t('Commerce braintree log');

  $data['commerce_braintree_log']['table']['base'] = array(
    'field' => 'id', 
    'title' => t('Braintree log'), 
    'help' => t('Braintree log containing braintree payment action .'), 
  );
  
  $data['commerce_braintree_log']['id'] = array(
    'title' => t('Braintree log id'), 
    'help' => t('The unique internal identifier of the Braintree log.'), 
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
  $data['commerce_braintree_log']['uid'] = array(
    'title' => t('Braintree log uid'), 
    'help' => t('The user id.'), 
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
  $data['commerce_braintree_log']['data'] = array(
    'title' => t('Braintree log data'), 
    'help' => t('The subscription data.'), 
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
  $data['commerce_braintree_log']['timestamp'] = array(
    'title' => t('Create date'), 
    'help' => t('The date the profile was created.'), 
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
  $data['commerce_braintree_log']['action'] = array(
    'title' => t('Braintree log action'), 
    'help' => t('The action occur on braintree payment.'), 
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
  $data['commerce_braintree_log']['message'] = array(
    'title' => t('Braintree log message'), 
    'help' => t('The action of message.'), 
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
  
  // Expose the owner uid.
  $data['commerce_braintree_log']['uid'] = array(
    'title' => t('User log'),
    'help' => t('Relate a profile to the user it belongs to.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('User log'),
    ),
  );
  //link view
  $data['commerce_braintree_log']['id'] = array(
    'field' => array(
      'title' => t('Link view'),
      'help' => t('Provide a simple link to view log detail.'),
      'handler' => 'commerce_braintree_log_handler_field_log_view_link',
    ),
  );
  return $data;
}