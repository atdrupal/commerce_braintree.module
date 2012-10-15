<?php


function commerce_braintree_views_data() {
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
  $data['commerce_braintree_log']['sid'] = array(
    'title' => t('Braintree log sid'), 
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
  return $data;
}