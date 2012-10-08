<?php

function commerce_braintree_form_alter(&$form, &$form_state, $form_id){
  //dsm($form);
}

function commerce_braintree_block_info() {
  $blocks['braintree_payment_order'] = array(
    'info' => t('Cancel braintree recurring billing'),
    //'status' => TRUE,
    //'region' => 'content',  // Not usually provided.
    'visibility' => BLOCK_VISIBILITY_LISTED,  // Not usually provided.
    'pages' => 'admin/commerce/orders/*', // Not usually provided here.
  );
  return $blocks;
}

function commerce_braintree_block_view($delta = '') {
  //The $delta parameter tells us which block is being requested.
  switch ($delta) {
    case 'braintree_payment_order':
      $block['subject'] = t("Cancel braintree recurring billing");
      $block['content'] = "<h1>Chao block</h1>";//commerce_braintree_cancel_form();
      break;
  }
  return $block;
}

