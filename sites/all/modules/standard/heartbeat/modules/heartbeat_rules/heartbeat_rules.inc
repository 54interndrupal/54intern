<?php

/**
 * @file
 * Rules action callbacks.
 *
 */

/**
 * Rules action to log activity.
 */
function rules_action_heartbeat_activity_log() {

  // I did not find yet how to receive dynamic variables and catch them wisely.
  //$entity_id, $uid, $entity_id_target, $uid_target, $message_id, $variables
  $args = func_get_args();

  array_pop($args);
  array_pop($args);
  $rulesState = array_pop($args);

  // Prepare the arguments we need.
  $arguments = $rulesState->currentArguments;
  unset($arguments['settings'], $arguments['state']);

  // Fix the message id and load the template.
  $info = $arguments['message_id']->info();
  $message_id = $info['default value'];
  $variables = array('variables' => array());

  ctools_include('export');
  $template = heartbeat_message_template_load($message_id);
  foreach ($arguments as $key => $value) {

    if ($value instanceof EntityValueWrapper) {
      $val = $value->value();
    }
    else {
      $val = $value;
    }

    if (isset($template->variables[$key])) {
      $variables['variables'][$key] = $val;
    }
    else {
      $variables[$key] = $val;
    }

    if (in_array($key, array('nid', 'uid', 'nid_target', 'uid_target', 'cid'))) {
      $variables[$key] = (int) $variables[$key];
    }
  }
  $variables['access'] = _heartbeat_activity_get_access($variables['uid'], $template);
  $variables['message_id'] = $message_id;

  // Break logging if no actor is specified.
  if (!is_numeric($variables['uid'])) {
    return;
  }

  heartbeat_log($variables, $variables['variables']);

}