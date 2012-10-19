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
  $items['rules_order_set_status_when_canceled'] = entity_import('rules_config', '{ "rules_order_set_status_when_canceled" : {
      "LABEL" : "Order set status when  canceled",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "commerce_order", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_canceled" ],
      "DO" : [
        { "commerce_order_update_status" : { "commerce_order" : [ "order" ], "order_status" : "canceled" } }
      ]
    }
  }');
  $items['rules_order_set_status_when_went_active'] = entity_import('rules_config', '{ "rules_order_set_status_when_went_active" : {
      "LABEL" : "Order set status when went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "commerce_order", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "DO" : [
        { "commerce_order_update_status" : { "commerce_order" : [ "order" ], "order_status" : "completed" } }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_retreat_cancel'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_retreat_cancel" : {
      "LABEL" : "User set roles and profile data on Retreat cancel",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_went_past_due"
      ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "retreats" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_retreat_went_active'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_retreat_went_active" : {
      "LABEL" : "User set roles and profile data on Retreat went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "retreats" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_studio_cancel'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_studio_cancel" : {
      "LABEL" : "User set roles and profile data on Studio cancel",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_went_past_due"
      ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "studios" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_studio_went_active'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_studio_went_active" : {
      "LABEL" : "User set roles and profile data on Studio went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "studios" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "5" : "5" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_teacher_cancel'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_teacher_cancel" : {
      "LABEL" : "User set roles and profile data on Teacher cancel",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_went_past_due"
      ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "teachers" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "4" : "4" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_teacher_went_active'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_teacher_went_active" : {
      "LABEL" : "User set roles and profile data on Teacher went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "teachers" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "4" : "4" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_training_cancel'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_training_cancel" : {
      "LABEL" : "User set roles and profile data on Training cancel",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [
        "rules_braintree_event_subscription_canceled",
        "rules_braintree_event_subscription_went_past_due"
      ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "trainings" } } ],
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "7" : "7" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|1\\r\\nfield_is_premium|0\\r\\nfield_events_available|0"
          }
        }
      ]
    }
  }');
  $items['rules_user_set_roles_and_profile_data_on_training_went_active'] = entity_import('rules_config', '{ "rules_user_set_roles_and_profile_data_on_training_went_active" : {
      "LABEL" : "User set roles and profile data on Training went active",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "braintree" ],
      "REQUIRES" : [ "rules", "rules_braintree" ],
      "ON" : [ "rules_braintree_event_subscription_went_active" ],
      "IF" : [ { "data_is" : { "data" : [ "profile-type" ], "value" : "trainings" } } ],
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "7" : "7" } } } },
        { "rules_braintree_action_profile_data_set" : {
            "profile_id" : [ "profile_id" ],
            "fields" : "field_is_pastdue|0\\r\\nfield_is_premium|1\\r\\nfield_events_available|10"
          }
        }
      ]
    }
  }');
  return $items;
}
