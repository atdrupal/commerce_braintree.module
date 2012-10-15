<?php
/**
 * @file
 * features_rules_braintree.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function features_rules_braintree_default_rules_configuration() {
  $items = array();
  $items['rules_set_profile_studio_when_subsription_canceled'] = entity_import('rules_config', '{ "rules_set_profile_studio_when_subsription_canceled" : {
      "LABEL" : "Set profile studio when subsription canceled",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_expired"
      ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "studios" } } ],
      "DO" : [
        { "data_set" : { "data" : [ "account:profile-studio:field-is-pastdue" ], "value" : 1 } },
        { "data_set" : {
            "data" : [ "account:profile-studio:field-events-available" ],
            "value" : "0"
          }
        },
        { "data_set" : { "data" : [ "account:profile-studio:field-is-premium" ], "value" : 0 } }
      ]
    }
  }');
  $items['rules_set_profile_studio_when_subsription_went_active'] = entity_import('rules_config', '{ "rules_set_profile_studio_when_subsription_went_active" : {
      "LABEL" : "Set profile studio when subsription went active",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "studios" } } ],
      "DO" : [
        { "data_set" : { "data" : [ "account:profile-studio:field-is-premium" ], "value" : 1 } },
        { "data_set" : {
            "data" : [ "account:profile-studio:field-events-available" ],
            "value" : "20"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_teacher_when_subsription_went_active'] = entity_import('rules_config', '{ "rules_set_profile_teacher_when_subsription_went_active" : {
      "LABEL" : "Set profile teacher when subsription went active",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "teachers" } } ],
      "DO" : [
        { "data_set" : { "data" : [ "account:profile-teacher:field-is-premium" ], "value" : 1 } },
        { "data_set" : {
            "data" : [ "account:profile-teacher:field-events-available" ],
            "value" : "10"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_teachers_when_subsription_canceled_'] = entity_import('rules_config', '{ "rules_set_profile_teachers_when_subsription_canceled_" : {
      "LABEL" : "Set profile teachers when subsription canceled ",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_expired"
      ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "teachers" } } ],
      "DO" : [
        { "data_set" : { "data" : [ "account:profile-teacher:field-is-premium" ], "value" : 0 } },
        { "data_set" : { "data" : [ "account:profile-teacher:field-is-pastdue" ], "value" : 1 } },
        { "data_set" : {
            "data" : [ "account:profile-teacher:field-events-available" ],
            "value" : "0"
          }
        }
      ]
    }
  }');
  return $items;
}
