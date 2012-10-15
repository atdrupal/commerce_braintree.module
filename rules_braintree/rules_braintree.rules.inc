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

