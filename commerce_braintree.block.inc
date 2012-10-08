<?php

function commerce_braintree_form_alter(&$form, &$form_state, $form_id){
  dsm($form);
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
function commerce_braintree_cancel_form(){
  $vocabularies = taxonomy_get_vocabularies();
  $form['#tree'] = TRUE;
  foreach ($vocabularies as $vocabulary) {
    $form[$vocabulary->vid]['#vocabulary'] = $vocabulary;
    $form[$vocabulary->vid]['name'] = array('#markup' => check_plain($vocabulary->name));
    $form[$vocabulary->vid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight for @title', array('@title' => $vocabulary->name)),
      '#title_display' => 'invisible',
      '#delta' => 10,
      '#default_value' => $vocabulary->weight,
    );
    $form[$vocabulary->vid]['edit'] = array('#type' => 'link', '#title' => t('edit vocabulary'), '#href' => "admin/structure/taxonomy/$vocabulary->machine_name/edit");
    $form[$vocabulary->vid]['list'] = array('#type' => 'link', '#title' => t('list terms'), '#href' => "admin/structure/taxonomy/$vocabulary->machine_name");
    $form[$vocabulary->vid]['add'] = array('#type' => 'link', '#title' => t('add terms'), '#href' => "admin/structure/taxonomy/$vocabulary->machine_name/add");
  }

  // Only make this form include a submit button and weight if more than one
  // vocabulary exists.
  if (count($vocabularies) > 1) {
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  }
  elseif (isset($vocabulary)) {
    unset($form[$vocabulary->vid]['weight']);
  }
  return $form;
}
