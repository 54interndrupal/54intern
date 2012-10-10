<?php

/**
 * A field that displays fields.
 */
class searchlight_handler_field_field extends views_handler_field_field {

  /**
   * TODO: description.
   */
  function query($use_groupby = FALSE) {
    parent::query($use_groupby);

    // TODO: searchlight killswitch.
    if ($this->view->name !== 'searchlight_datasource') {
      return;
    }

    // TODO: review.
    if ($this->add_field_table($use_groupby)) {
      return;
    }

    $fields = array();
    foreach ($this->additional_fields as $field) {
      if (in_array($field, array('entity_type', 'delta', 'language', 'bundle')) || strpos($field, '_format') !== FALSE) {
        continue;
      }
      $fields[] = $field;
    }

    $this->ensure_my_table();
    $this->add_additional_fields($fields);
  }
}
