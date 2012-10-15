<?php

/**
 * @file
 * Example Rules code: actions, conditions and events.
 */


/**
 * Implements hook_rules_event_info().
 */
function rules_braintree_rules_event_info() {
  $events = array();
  $variables = array(
    'account' => array(
      'type' => 'user',
      'label' => t('The user of webhook callback'),
    ),
    'planid' => array(
      'type' => 'text',
      'label' => t('Braintree plan id'),
    ),
  );
  $events['rules_braintree_event_subscription_canceled'] = array(
      'label' => t('Subscription canceled'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  $events['rules_braintree_event_subscription_charged_successfully'] = array(
      'label' => t('Subscription charged successfully'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  $events['rules_braintree_event_subscription_charged_unsuccessfully'] = array(
      'label' => t('Subscription charged unsuccessfully'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  $events['rules_braintree_event_subscription_expired'] = array(
      'label' => t('Subscription expired'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  $events['rules_braintree_event_subscription_trial_ended'] = array(
      'label' => t('Subscription trial ended'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  $events['rules_braintree_event_subscription_went_past_due'] = array(
      'label' => t('Subscription went past due'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  $events['rules_braintree_event_subscription_went_active'] = array(
      'label' => t('Subscription went active'),
      'group' => t('Braintree'),
      'variables' => $variables
  );
  
  return $events;
}


/**
 * Implements hook_rules_action_info().
 */
function rules_braintree_rules_action_info() {
  $actions = array();
  if (module_exists('commerce_braintree')) {
    $actions['rules_braintree_action_profile_data_set'] = array(
      'label' => t('Set profile data of user from webhook callback'),
      'group' => t('Braintree'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('The user of webhook callback'),
        ),
        'planid' => array(
          'type' => 'text',
          'label' => t('Braintree plan id'),
        ),
        
        'fields' => array(
          'type' => 'text',
          'label' => t('Field and value'),
          'help' => t('Enter one value per line, in the format field|label'),
          'restriction' => 'input',
        ),
      ),
    );
  }
  return $actions;
}

function rules_braintree_action_profile_data_set($account, $planid, $fields) {
  $profile = profile2_by_uid_load($account->uid,$planid);
  $fields = explode("\n", str_replace("\r", '', $fields));
  $instances = field_info_instances('profile2', $planid);
  
  foreach ($fields as $field) {
    $field = explode('|',$field);
    if (in_array($field['0'], $instances)) {
      $profile->$field['0'][LANGUAGE_NONE][0]['value'] = $field['1'];
    }
    
  }
  profile2_save($profile);
}