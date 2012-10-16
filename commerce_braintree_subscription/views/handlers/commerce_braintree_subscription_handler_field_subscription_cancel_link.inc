<?php

/**
 * Field handler to present a link to cancel subscription.
 */
class commerce_braintree_subscription_handler_field_subscription_cancel_link extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['sid'] = 'sid';
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
    $sid = $this->get_value($values, 'sid');

    return l($text, 'braintree/' . $sid . '/cancel');
  }
}
