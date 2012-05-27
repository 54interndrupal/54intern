<?php
/**
 * Filter by Hearbeat message ID.
 */
class views_handler_filter_heartbeat_message_id extends views_handler_filter_in_operator {
 // Populate options with different heartbeat templates.
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Message ID (type)');
      $options = array();
      ctools_include('export');
     foreach (ctools_export_crud_load_all('heartbeat_messages', TRUE) as $template) {
       $options[$template->message_id] = t("@message_id (!description)",
         array('@message_id' => $template->message_id, '!description' => $template->description));
     }
     asort($options);
      $this->value_options = $options;
   }
  }
}