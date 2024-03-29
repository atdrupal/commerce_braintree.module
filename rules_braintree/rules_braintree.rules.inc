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
    'profile_type' => array(
      'type' => 'text',
      'label' => t('Profiles type'),
    ),
    'profile_nid' => array(
      'type' => 'text',
      'label' => t('Profiles Id'),
    ),
    'order' => array(
      'type' => 'commerce_order',
      'label' => t('The order for this subscription')
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
      'label' => t('Profile data set'),
      'group' => t('Braintree'),
      'parameter' => array(
        'profile_id' => array(
          'type' => 'text',
          'label' => t('Profile Id'),
        ),
        'fields' => array(
          'type' => 'text',
          'label' => t('Field and value'),
          'description' => t('Enter one value per line, in the format field|value'),
          'restriction' => 'input',
        ),
      ),
    );
  }
  return $actions;
}

/**
 * Save profile
 * @param type $account
 * @param type $sid
 * @param type $fields
 */
function rules_braintree_action_profile_data_set($pid, $fields) {
  $profile = profile2_load($pid);
  $fields = explode("\n", str_replace("\r", '', $fields));
  $instances = field_info_instances('profile2', $profile->type);
  foreach ($fields as $field) {
    $field = explode('|', $field);
    foreach ($instances as $key => $insf) {
      if (strcmp($field['0'], $key) == 0) {
        $profile->{$key}[LANGUAGE_NONE][0]['value'] = $field['1'];
      }
    }
  }
  profile2_save($profile);
}