<?php
/**
 * @file
 * Implementation hook_views_data to intergrate views with table commerce_braintree_subscription
 */

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
  $data['commerce_braintree_subscription']['pid'] = array(
    'title' => t('The profile id'), 
    'help' => t('The profile.'), 
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
  $data['commerce_braintree_subscription']['token'] = array(
    'title' => t('The credit card token'), 
    'help' => t('The credit card token.'), 
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
  
  
  
  
  $data['commerce_braintree_subscription']['first_bill_date'] = array(
    'title' => t('First Bill Date'), 
    'help' => t('First Bill Date.'), 
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
  $data['commerce_braintree_subscription']['billing_period_start_date'] = array(
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
  $data['commerce_braintree_subscription']['billing_period_end_date'] = array(
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
  $data['commerce_braintree_subscription']['paid_through_date'] = array(
    'title' => t('Paid Through Date.'), 
    'help' => t('Paid Through Date.'), 
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
  $data['commerce_braintree_subscription']['next_bill_date'] = array(
    'title' => t('Next Bill Date.'), 
    'help' => t('Next Bill Date.'), 
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
  $data['commerce_braintree_subscription']['next_billing_period_amount'] = array(
    'title' => t('Next Billing Period Amount.'), 
    'help' => t('Next Billing Period Amount.'), 
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
  $data['commerce_braintree_subscription']['price'] = array(
    'title' => t('The Subscription price.'), 
    'help' => t('The Subscription price.'), 
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
  $data['commerce_braintree_subscription']['pid'] = array(
    'title' => t('Node'),
    'help' => t('Node relative.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'field' => 'pid',
      'label' => t('Node'),
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
  $data['commerce_braintree_subscription']['link_edit_credit_card'] = array(
    'field' => array(
      'title' => t('Link edit'),
      'help' => t('Provide a simple link to edit credit card.'),
      'handler' => 'commerce_braintree_subscription_handler_field_credit_card_edit_link',
    ),
  );
  
  return $data;
}