<?php


/**
 * Menu callback; displays details about a braintree log.
 */
function commerce_braintree_log_detail($id) {
  module_load_include('inc', 'dblog', 'dblog.admin');
  $result = db_query('SELECT c.*, u.name, u.uid FROM {commerce_braintree_log} c INNER JOIN {users} u ON c.uid = u.uid WHERE c.id = :id', array(':id' => $id))->fetchObject();
  if ($log = $result) {
    $rows = array(
      array(
        array('data' => t('Action'), 'header' => TRUE),
        t($log->action),
      ),
      array(
        array('data' => t('Date'), 'header' => TRUE),
        format_date($log->timestamp, 'long'),
      ),
      array(
        array('data' => t('User'), 'header' => TRUE),
        theme('username', array('account' => $log)),
      ),
      array(
        array('data' => t('Message'), 'header' => TRUE),
        t($log->message),
      ),
      array(
        array('data' => t('Hostname'), 'header' => TRUE),
        check_plain($log->hostname),
      ),
    );
    $build['log_table'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#attributes' => array('class' => array('log-event')),
    );
    $build['log_data_form'] = drupal_get_form('commerce_braintree_log_data_view_form', $id);
    return $build;
  }
  else {
    return '';
  }
}

/**
 * Views data
 * @param type $form
 * @param type $form_state
 * @param type $id
 * @return type
 */
function commerce_braintree_log_data_view_form($form, $form_state, $id) {
  $data = array_map('unserialize', db_query('SELECT id, data FROM {commerce_braintree_log} c WHERE c.id = :id', array(':id' => $id))->fetchAllKeyed());
  $form['value'] = array(
    '#type' => 'item',
    '#title' => t('Data'),
    '#markup' => dpr($data, TRUE),
  );
  return $form;
}

