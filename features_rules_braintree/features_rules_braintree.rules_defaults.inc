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
  $items['rules_set_profile_retreat_when_subsription_canceled'] = entity_import('rules_config', '{ "rules_set_profile_retreat_when_subsription_canceled" : {
      "LABEL" : "Set profile retreat when subsription canceled",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_expired"
      ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "retreats" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_retreat_when_subsription_went_active'] = entity_import('rules_config', '{ "rules_set_profile_retreat_when_subsription_went_active" : {
      "LABEL" : "Set profile retreat when subsription went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "retreats" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_studio_when_subsription_canceled'] = entity_import('rules_config', '{ "rules_set_profile_studio_when_subsription_canceled" : {
      "LABEL" : "Set profile studio when subsription canceled",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_expired"
      ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "studios" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_studio_when_subsription_went_active'] = entity_import('rules_config', '{ "rules_set_profile_studio_when_subsription_went_active" : {
      "LABEL" : "Set profile studio when subsription went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "studios" } } ],
      "DO" : [
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        },
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } }
      ]
    }
  }');
  $items['rules_set_profile_teacher_when_subsription_went_active'] = entity_import('rules_config', '{ "rules_set_profile_teacher_when_subsription_went_active" : {
      "LABEL" : "Set profile teacher when subsription went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "teachers" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "4" : "4" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_teachers_when_subsription_canceled'] = entity_import('rules_config', '{ "rules_set_profile_teachers_when_subsription_canceled" : {
      "LABEL" : "Set profile teachers when subsription canceled",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_expired"
      ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "teachers" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "4" : "4" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_training_when_subsription_canceled'] = entity_import('rules_config', '{ "rules_set_profile_training_when_subsription_canceled" : {
      "LABEL" : "Set profile training when subsription canceled",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_expired"
      ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "training" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "7" : "7" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_set_profile_training_when_subsription_went_active'] = entity_import('rules_config', '{ "rules_set_profile_training_when_subsription_went_active" : {
      "LABEL" : "Set profile training when subsription went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "planid" ], "value" : "training" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "7" : "7" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "account" : [ "account" ],
            "planid" : [ "planid" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  return $items;
}
