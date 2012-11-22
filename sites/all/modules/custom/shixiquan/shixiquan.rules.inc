<?php

/**
 * @file
 * Rules integration for shixiquan.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_action_info().
 */
function shixiquan_rules_action_info() {
  $items = array();

  // For UX also provide separate actions for user subcriptions although it is
  // technically the same as adding entities to groups.

  $items['shixiquan_subcribe_user'] = array(
    'label' => t('Subscribe user to group(shixiquan)'),
    'group' => t('Organic groups'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User'),
        'description' => t('The user who will be subscribed.'),
        'wrapped' => TRUE,
        'save' => TRUE,
      ),
      'group' => array(
        'type' => 'node',
        'label' => t('Group'),
        'wrapped' => TRUE,
      ),
      // @todo: Add membership-type setting + add in the membership-entity
      // fields via the info_alter callback + reload the form once the
      // membership-type has been chosen.
      // Then, we probably also want to provide the newly created membership
      // entity.
    ),
    'base' => 'shixiquan_rules_add_entity_to_group',
    'access callback' => 'shixiquan_rules_integration_access',
  );

  $items['og_unsubscribe_user'] = array(
    'label' => t('Unsubscribe user from group(shixiquan)'),
    'group' => t('Organic groups'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User'),
        'description' => t('The user who will be unsubscribed.'),
        'wrapped' => TRUE,
        'save' => TRUE,
      ),
      'group' => array(
        'type' => 'node',
        'label' => t('Group'),
        'wrapped' => TRUE,
      ),
    ),
    'base' => 'shixiquan_rules_remove_entity_from_group',
    'access callback' => 'shixiquan_rules_integration_access',
  );

  $items['shixiquan_create_apply'] = array(
    'label' => t('创建apply对象'),
    'group' => t('Entities'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User'),
        'description' => t('申请职位的用户.'),
        'wrapped' => TRUE,
        'save' => TRUE,
      ),
      'job' => array(
        'type' => 'node',
        'label' => t('职位'),
        'wrapped' => TRUE,
      ),
      // @todo: Add membership-type setting + add in the membership-entity
      // fields via the info_alter callback + reload the form once the
      // membership-type has been chosen.
      // Then, we probably also want to provide the newly created membership
      // entity.
    ),
    'base' => 'shixiquan_rules_create_apply',
    'access callback' => 'shixiquan_rules_integration_access',
  );

  $items['shixiquan_delete_apply'] = array(
    'label' => t('删除apply对象'),
    'group' => t('Entities'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User'),
        'description' => t('取消申请职位的用户.'),
        'wrapped' => TRUE,
        'save' => TRUE,
      ),
      'job' => array(
        'type' => 'node',
        'label' => t('职位'),
        'wrapped' => TRUE,
      ),
      // @todo: Add membership-type setting + add in the membership-entity
      // fields via the info_alter callback + reload the form once the
      // membership-type has been chosen.
      // Then, we probably also want to provide the newly created membership
      // entity.
    ),
    'base' => 'shixiquan_rules_delete_apply',
    'access callback' => 'shixiquan_rules_integration_access',
  );

  return $items;
}

/**
 * Action: Add entity to group.
 */
function shixiquan_rules_add_entity_to_group(EntityDrupalWrapper $user, EntityDrupalWrapper $group) {
  // TODO: Add field-name.
  $values = array(
    'entity_type' => 'user',
    'entity' => $user->value(),
  );
  og_group('node', $group->getIdentifier(), $values);

}

/**
 * Action: Remove entity from group.
 */
function shixiquan_rules_remove_entity_from_group(EntityDrupalWrapper $user, EntityDrupalWrapper $group) {
//print debug($user->getIdentifier());
  og_ungroup('node', $group->getIdentifier(), 'user', $user->getIdentifier());
}

/**
 * Action: Remove entity from group.
 */
function shixiquan_rules_create_apply(EntityDrupalWrapper $user, EntityDrupalWrapper $job) {
  $langcode = 'und';

  $job_id = $job->getIdentifier();
  $uid = $user->getIdentifier();

  $user_picture = $_COOKIE['druapl_user_picture'];
  if (empty($user_picture)) {
    $account = user_load($uid);
    $image_vars = array('account' => $account);
    if (module_exists('imagecache_profiles')) {
      $image_vars['user_picture_style'] = '100_100';
    }
    $user_picture = theme('user_picture', $image_vars);
  }

  //通知邮件
  $email = db_select('field_data_field_email', 'm')
    ->fields('m', array('field_email_value'))
    ->condition('bundle', 'job')
    ->condition('entity_id', $job_id)
    ->range(0, 1)
    ->execute()
    ->fetchField();
  if (empty($email)) {
    return;
  }

  //公司 ID
  $company_id = db_select('og_membership', 'm')
    ->fields('m', array('gid'))
    ->condition('entity_type', 'node')
    ->condition('etid', $job_id)
    ->condition('group_type', 'node')
  //->condition('field_name','og_group_ref')
    ->range(0, 1)
    ->execute()
    ->fetchField();

//简历 ID
  $resume_id = $_SESSION['user_resume_id'];
  if (empty($resume_id)) {
    return;
  }

  $resume_node = node_load($resume_id);
  $resume = $resume_node;
  $user_name = $resume->field_real_name[LANGUAGE_NONE][0]["value"];

  $job_title = i_title($job_id);
  $company_title = i_title($company_id);
  $apply_date = date('Y-m-d');

  $created = time();
  $apply = new stdClass();
  $apply->uid = $uid;
  $apply->created = $created;
  $apply->entity_type = 'apply';
  $apply->type = 'apply';
  $apply->bundle = 'apply';
  $apply->field_resume_id[$langcode][]['target_id'] = $resume_id;
  $apply->field_resume_id[$langcode][]['target_type'] = 'node';

  $apply->field_job_id[$langcode][]['target_id'] = $job_id;
  $apply->field_job_id[$langcode][]['target_type'] = 'node';
  $apply->field_company_id[$langcode][]['target_id'] = $company_id;
  $apply->field_company_id[$langcode][]['target_type'] = 'node';
  entity_save('apply', $apply);

  if (isset($email) && !empty($email)) {
    $values = array();
    $values['uid'] = $user->uid;
    $values['user_name'] = $user_name;
    $values['job_title'] = $job_title;
    $values['company_title'] = $company_title;
    $values['apply_date'] = $apply_date;
    $values['resume'] = $resume;
    $values['user_picture'] = $user_picture;
//    $from =  '实习圈54intern '.$user_name.'[resume@54intern.com]';
//    $from =  'resume@54intern.com';
    $from = array(
      'name' => '实习圈[54intern] ' . $user_name,
      'mail' => 'resume@54intern.com',
    );
    drupal_mail('intern_job', 'job_apply', $email, language_default(), $values, $from);
  }
}

/**
 * Action: Remove entity from group.
 */
function shixiquan_rules_delete_apply(EntityDrupalWrapper $user, EntityDrupalWrapper $job) {
//print debug($user->getIdentifier());
//  og_ungroup('node', $group->getIdentifier(), 'user',$user->getIdentifier());
//找到对应的apply_ids
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'apply');
  $query->entityCondition('bundle', 'apply');

  $query->propertyCondition('uid', $user->getIdentifier());
  $query->fieldCondition('field_job_id', 'target_id', $job->getIdentifier());
  //$query->range(0,1);
  $result = $query->execute();
  $apply_ids = array();

  //删除对应的applys
  if (!empty($result) && isset($result['apply'])) {
    $apply_ids = array_keys($result['apply']);
    entity_delete_multiple('apply', $apply_ids);
  }

}


/**
 * OG Rules integration access callback.
 */
function shixiquan_rules_integration_access($type, $name) {
  // Grant everyone access to conditions.
  return $type == 'condition' || user_access('administer group');
}