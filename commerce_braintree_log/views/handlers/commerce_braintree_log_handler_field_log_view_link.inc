<?php
/**
 * @file
 * Create link handle cancel subscription
 */

/**
 * Field handler to present a link to cancel subscription.
 */
class commerce_braintree_log_handler_field_log_view_link extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['id'] = 'id';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('cancel');
    $id = $this->get_value($values, 'id');

    return l($text, 'admin/commerce/braintree/log/detail/' . $id);
  }
}
