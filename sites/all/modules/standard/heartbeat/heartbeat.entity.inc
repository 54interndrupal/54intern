<?php

/**
 * Implement hook_entity_info().
 */
function heartbeat_entity_info() {
  $return = array(
    'heartbeat_activity' => array(
      'label' => t('Heartbeat Activity Entity'),
      'controller class' => 'HeartbeatActivityController',
      'base table' => 'heartbeat_activity',
      'uri callback' => 'heartbeat_activity_uri',
      'fieldable' => TRUE,
      'entity keys' => array(
        'id' => 'uaid',
        'bundle' => 'message_id',
        'label' => 'message_id',
      ),
      'bundle keys' => array(
        'bundle' => 'message_id',
      ),
      'bundles' => array(),
      'view modes' => array(
        'full' => array(
          'label' => t('Full activity message'),
          'custom settings' => FALSE,
        ),
      ),
    ),
  );
  // Bundles must provide a human readable name so we can create help and error
  // messages, and the path to attach Field admin pages to.
  foreach (heartbeat_templates_names() as $name => $description) {
    $return['heartbeat_activity']['bundles'][$name] = array(
      'label' => $description,
      'admin' => array(
        'path' => 'admin/structure/heartbeat/templates/list/%heartbeat_message_template',
        'real path' => 'admin/structure/heartbeat/templates/list/' . $name,
        'bundle argument' => 5,
        'access arguments' => array('admin heartbeat templates'),
      ),
    );
  }
  $return['heartbeat_activity_template'] = array(
    'label' => t('Heartbeat activity entity type'),
    'controller class' => 'HeartbeatTemplateController',
    'base table' => 'heartbeat_messages',
    'entity keys' => array(
      'id' => 'hid',
      'label' => 'message_id',
    ),
    'fieldable' => FALSE,
  );

  return $return;
}

/**
 * Entity uri callback.
 */
function heartbeat_activity_uri($heartbeatActivity) {
  return array(
    'path' => 'heartbeat/message/' . $heartbeatActivity->uaid,
  );
}

/**
 * Implements hook_field_extra_fields().
 */
function heartbeat_field_extra_fields() {

  $return = array();
  $info = entity_get_info('heartbeat_activity');
  foreach (array_keys($info['bundles']) as $bundle) {
    $return['heartbeat_activity'][$bundle] = array(
      'display' => array(
        'avatar' => array(
          'label' => 'Avatar',
          'description' => t('Heartbeat activity avatar element'),
          'weight' => 0,
        ),
        'message' => array(
          'label' => 'Message',
          'description' => t('Heartbeat activity message element'),
          'weight' => 1,
        ),
        'time' => array(
          'label' => 'Time',
          'description' => t('Heartbeat activity time element'),
          'weight' => 2,
        ),
        'buttons' => array(
          'label' => 'Buttons',
          'description' => t('Heartbeat activity buttons'),
          'weight' => 3,
        ),
      ),
    );
  }

  $return['user']['user'] = array(
    'form' => array(
      'heartbeat' => array(
        'label' => 'Heartbeat activity templates',
        'description' => t('Heartbeat activity template form element.'),
        'weight' => 6,
      ),
    ),
  );

  return $return;
}

/**
 * Controller class for heartbeat activity.
 *
 * This extends the DrupalDefaultEntityController class, adding required
 * special handling for heartbeat activity objects.
 */
class HeartbeatActivityController extends DrupalDefaultEntityController {

  /**
   * Implements buildQuery().
   */
  protected function buildQuery($ids, $conditions = array(), $revision_id = FALSE) {

    $query = parent::buildQuery($ids, $conditions, $revision_id);

    $query->addTag('translatable');
    $query->addTag('heartbeat_activity_access');
    $query->addField('base', 'variables', 'variables');
    $query->addField('base', 'access', 'access');

    $query->join('users', 'u', 'u.uid = base.uid');
    // Base table fields are automatically create in the parent.
    //$query->fields('base');
    $query->fields('u');

    // Override the permission based on the user profile status.
    $query->leftJoin('heartbeat_user_templates', 'hut', ' base.uid = hut.uid AND base.message_id = hut.message_id ');
    $query->addField('hut', 'status', 'access_status');

    $query->addField('base', 'access', 'access');
    $query->addField('u', 'access', 'users_access');

    // This part is done by base.uaid in ($ids).
    //$query->condition('ha.uaid', $uaid);

    return $query;

  }

  /**
   * Implements cacheGet().
   *
   * TODO think of conditions to use. Currently none.
   */
  protected function cacheGet($ids, $conditions = array()) {

    $activities = parent::cacheGet($ids, $conditions);

    return $activities;

  }


}

/**
 * Controller class for heartbeat templates.
 *
 * This extends the DrupalDefaultEntityController class, adding required
 * special handling for heartbeat template objects.
 */
class HeartbeatTemplateController extends DrupalDefaultEntityController {

  /**
   * Implements DrupalEntityControllerInterface::load().
   *
   * We make sure there is no query run, but ctools does this job for heartbeat.
   */
  public function load($ids = array(), $conditions = array()) {
    ctools_include('export');
    return ctools_export_load_object('heartbeat_templates', 'conditions', $conditions);
  }

}

/**
 * Generate the heartbeat activity add/edit form.
 */
function heartbeat_activity_form($form, &$form_state, HeartbeatActivity $heartbeatActivity) {

  // During initial form build, add the heartbeatActivity entity to the form state for use
  // during form building and processing. During a rebuild, use what is in the form state.
  if (!isset($form_state['heartbeat_activity'])) {
    if (!isset($heartbeatActivity->title)) {
      $heartbeatActivity->title = NULL;
    }
    $form_state['heartbeat_activity'] = $heartbeatActivity;
  }
  else {
    $heartbeatActivity = $form_state['heartbeat_activity'];
  }

  $form['#attributes']['class'][] = 'heartbeat-activity-form';
  if (!empty($heartbeatActivity->type)) {
    $form['#attributes']['class'][] = 'heartbeat-activity-' . $heartbeatActivity->type . '-form';
  }

  // Basic heartbeat activity information.
  // These elements are just values so they are not even sent to the client.
  foreach (array('uaid', 'uid', 'uid_target', 'nid', 'nid_target', 'timestamp', 'message_id', 'language') as $key) {
    $form[$key] = array(
      '#type' => 'value',
      '#value' => isset($heartbeatActivity->$key) ? $heartbeatActivity->$key : 0,
    );
  }

  // @todo D8: Remove. Modules should access the activity using $form_state['heartbeat_activity'].
  $form['#heartbeat_activity'] = $heartbeatActivity;

  // Activity author information.
  $form['name'] = array(
    '#type' => 'value',
    '#value' => !empty($heartbeatActivity->actor->name) ? $heartbeatActivity->actor->name : '',
  );

  // Add action buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 5,
    '#ajax' => array(
      'callback' => 'heartbeat_activity_form_callback',
      'wrapper' => 'heartbeat-status-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // The complete form as ajax wrapper, validate and submit callbacks.
  $form['#prefix'] = '<div id="heartbeat-status-wrapper">';
  $form['#suffix'] = '</div>';
  $form['#validate'][] = 'heartbeat_activity_form_validate';
  $form['#submit'][] = 'heartbeat_activity_form_submit';

  field_attach_form('heartbeat_activity', $heartbeatActivity, $form, $form_state, $heartbeatActivity->language);

  return $form;

}

/**
 * Ajax callback function when Heartbeat Activity is posted as Profile Status.
 */
function heartbeat_activity_form_callback($form, $form_state) {

  $commands = array();

  $commands[] = ajax_command_invoke(NULL, 'heartbeatNotifyStreams', array());

  $commands[] = ajax_command_invoke('.heartbeat-activity-form textarea', 'val', array(''));
  $commands[] = ajax_command_invoke('.heartbeat-activity-form .text-field', 'val', array(''));

  $html = drupal_render($form);
  $commands[] = ajax_command_insert(NULL, $html);//heartbeat-status-wrapper

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );

}

/**
 * Validate handler to save an heartbeat activity entity.
 */
function heartbeat_activity_form_validate($form, &$form_state) {

}

/**
 * Submit handler to save an heartbeat activity entity.
 */
function heartbeat_activity_form_submit($form, &$form_state) {

  //form_execute_handlers('submit', $form, $form_state);

  $heartbeatActivity = $form_state['heartbeat_activity'];

  $instances = _field_invoke_get_instances('heartbeat_activity', $heartbeatActivity->template->message_id, array(
    'default' => FALSE,
    'deleted' => FALSE,
    'language' => NULL,
  ));

  entity_form_submit_build_entity('heartbeat_activity', $heartbeatActivity, $form, $form_state);

  $heartbeatActivity->timestamp = $_SERVER['REQUEST_TIME'];

  // Prepare the fields.
  field_attach_presave('heartbeat_activity', $heartbeatActivity);
  module_invoke_all('heartbeat_activity_presave', $heartbeatActivity);

  // Save the record to the activity table.
  $saved = $heartbeatActivity->save();
  // Save fields.
  field_attach_insert("heartbeat_activity", $heartbeatActivity);

  // Invoke the heartbeat activity hooks.
  module_invoke_all("heartbeat_activity_insert", $heartbeatActivity);
  module_invoke_all("entity_insert", $heartbeatActivity, 'heartbeat_activity');

  entity_get_controller('heartbeat_activity')->resetCache(array($heartbeatActivity->uaid));

}