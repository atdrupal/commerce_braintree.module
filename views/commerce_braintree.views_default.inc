<?php
/**
 * @file
 * commerce_braintree_braintree_log.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_braintree_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'commerce_braintree_log';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_braintree_log';
  $view->human_name = 'Braintree log';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Braintree log';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Commerce braintree log: Braintree log uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'commerce_braintree_log';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'User ID';
  /* Field: Commerce braintree log: Braintree log sid */
  $handler->display->display_options['fields']['sid']['id'] = 'sid';
  $handler->display->display_options['fields']['sid']['table'] = 'commerce_braintree_log';
  $handler->display->display_options['fields']['sid']['field'] = 'sid';
  $handler->display->display_options['fields']['sid']['label'] = 'Subscription';
  /* Field: Commerce braintree log: Braintree log action */
  $handler->display->display_options['fields']['action']['id'] = 'action';
  $handler->display->display_options['fields']['action']['table'] = 'commerce_braintree_log';
  $handler->display->display_options['fields']['action']['field'] = 'action';
  $handler->display->display_options['fields']['action']['label'] = 'Action';
  /* Field: Commerce braintree log: Braintree log message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'commerce_braintree_log';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['label'] = 'Message';
  /* Field: Commerce braintree log: Create date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'commerce_braintree_log';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'braintree/log';
  $export['commerce_braintree_log'] = $view;

  return $export;
}
