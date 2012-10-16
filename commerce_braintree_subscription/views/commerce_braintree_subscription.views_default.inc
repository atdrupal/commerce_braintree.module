<?php
/**
 * @file
 * commerce_braintree_braintree_log.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_braintree_subscription_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'braintree_subscription';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_braintree_subscription';
  $view->human_name = 'Braintree Subscription';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Braintree Subscription Overview';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'order_id' => 'order_id',
    'sid' => 'sid',
    'status' => 'status',
    'created' => 'created',
    'last_update' => 'last_update',
    'link_cancel_subscription' => 'link_cancel_subscription',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'sid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_update' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'link_cancel_subscription' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Commerce braintree subscription: Order id of subscription */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  /* Relationship: Commerce braintree subscription: User subscription */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['relationship'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['link_to_order'] = 'customer';
  /* Field: Commerce braintree subscription: Braintree subscription id */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  $handler->display->display_options['fields']['sid']['label'] = 'Subscription ID';
  /* Field: Commerce braintree subscription: Braintree subscription status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status ';
  /* Field: Commerce braintree subscription: Create date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Commerce braintree subscription: Last update */
  $handler->display->display_options['fields']['last_update']['id'] = 'last_update';
  $handler->display->display_options['fields']['last_update']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['fields']['last_update']['field'] = 'last_update';
  $handler->display->display_options['fields']['last_update']['date_format'] = 'short';
  /* Field: Commerce braintree subscription: Link cancel */
  $handler->display->display_options['fields']['link_cancel_subscription']['id'] = 'link_cancel_subscription';
  $handler->display->display_options['fields']['link_cancel_subscription']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['fields']['link_cancel_subscription']['field'] = 'link_cancel_subscription';
  $handler->display->display_options['fields']['link_cancel_subscription']['label'] = 'cancel';
  /* Sort criterion: Commerce braintree subscription: Last update */
  $handler->display->display_options['sorts']['last_update']['id'] = 'last_update';
  $handler->display->display_options['sorts']['last_update']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['sorts']['last_update']['field'] = 'last_update';
  $handler->display->display_options['sorts']['last_update']['order'] = 'DESC';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );
  /* Filter criterion: Commerce braintree subscription: Braintree subscription id */
  $handler->display->display_options['filters']['sid']['id'] = 'sid';
  $handler->display->display_options['filters']['sid']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['filters']['sid']['field'] = 'sid';
  $handler->display->display_options['filters']['sid']['operator'] = 'word';
  $handler->display->display_options['filters']['sid']['group'] = 1;
  $handler->display->display_options['filters']['sid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['sid']['expose']['operator_id'] = 'sid_op';
  $handler->display->display_options['filters']['sid']['expose']['label'] = 'Subscription ID';
  $handler->display->display_options['filters']['sid']['expose']['operator'] = 'sid_op';
  $handler->display->display_options['filters']['sid']['expose']['identifier'] = 'sid';
  $handler->display->display_options['filters']['sid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );
  /* Filter criterion: Commerce braintree subscription: Braintree subscription status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'commerce_braintree_subscription';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['operator'] = 'word';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/commerce/braintree/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Subscription Overview';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Braintree';
  $handler->display->display_options['tab_options']['description'] = 'Mange braintree subscription and their log';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';


  $export['braintree_subscription'] = $view;

  return $export;
}
