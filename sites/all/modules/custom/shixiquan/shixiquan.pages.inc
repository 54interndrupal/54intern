<?php
// $Id$

/**
 * 帐户管理区块的主题函数
 */
function theme_zpuser_my_account_block() {
  $output = "";
  if (arg(0) == 'user' && arg(1) > 0) {
    $uid = arg(1);
    $output .= '<ul class="my_content">';
    $output .= '<li>' . l(t('我的帐户'), 'user/' . $uid) . '</li>';
    $output .= '<li>' . l(t('我的积分'), 'user/' . $uid . '/points') . '</li>';
    $output .= '<li>' . l(t('我的消息'), 'user/' . $uid . '/messages') . '</li>';
    $output .= '<li>' . l(t('我的社团'), 'user/' . $uid . '/groups') . '</li>';
    $output .= '<li>' . l(t('我关注的企业'), 'user/' . $uid . '/follow/companys') . '</li>';
    $output .= '<li>' . l(t('我关注的职位'), 'user/' . $uid . '/follow/jobs') . '</li>';
    $output .= '<li>' . l(t('我关注的人'), 'user/' . $uid . '/follow/users') . '</li>';
    $output .= '<li>' . l(t('编辑帐户信息'), 'user/' . $uid . '/edit') . '</li>';
    $output .= '</ul>';
  }
  return $output;
}

/**
 * 订单管理区块的主题函数
 */
function theme_zpuser_resume_block() {
  global $user;
  $output = "";
  if ($user->uid > 0) {
    $percent = 0;
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'resume');

    $query->propertyCondition('uid', $user->uid);
    $query->propertyOrderBy('created', 'ASC');
    $query->range(0, 1);
    $result = $query->execute();

    $nids = array();
    if (!empty($result) && isset($result['node'])) {
      $nids = array_keys($result['node']);
    }
    $path = 'node/add/resume';
    if (!empty($nids)) {
      $resume = node_load($nids[0]);
      //print debug($resume);
      $i = 0;
      $j = 0;
      $instances = field_info_instances('node', 'resume');
      foreach ($instances as $name => $instance) {
        $field = field_get_items('node', $resume, $instance['field_name']);
        $j++;
        if ($field) {
          $i++;
        }
      }

      $percent = round(($i / $j) * 100);
      $path = 'node/' . $resume->nid . '/edit';
    }

    $output .= '<div class="resume-status">';
    $output .= '<p>完成度：<big>' . $percent . '%</big></p>';
    $output .= '<div class="status"><div style="width:' . $percent . '%;"><!-- 简历完成度百分比直接输出为行内css属性width的值。 --></div></div>';
    $output .= '<a href="' . url($path) . '">完善我的简历</a>';
    $output .= '</div>';
  }
  return $output;
}

/**
 * 帐户管理区块的主题函数
 */
function theme_zpuser_microblog_block() {
  $output = "";
  global $user;
  if (arg(0) == 'user' && arg(1) > 0 && $user->uid == arg(1)) {
    $form = drupal_get_form('zpuser_microblog_form');
    $output .= drupal_render($form);
  }
  return $output;
}

function zpuser_microblog_form() {

  $form['body'] = array(
    '#type' => 'textarea',
    //'#title' => t('电子邮箱'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('分享'),
  );
  return $form;
}

function zpuser_microblog_form_validate(&$form, &$form_state) {
  if (empty($form_state['values']['body'])) {
    form_set_error('body', t('分享内容不能为空'));
  }
}

function zpuser_microblog_form_submit(&$form, &$form_state) {
  global $user;
  $micro = new stdClass;
  $micro->uid = $user->uid;
  $micro->status = 1;
  //简体中文
  $micro->language = 'zh-hans';
  $micro->type = 'microblog';
  $micro->title = substr($form_state['values']['body'], 0, 100);
  $micro->body['und'][0]['value'] = $form_state['values']['body'];
  $micro->body['und'][0]['format'] = 'filtered_html';

  node_save($micro);
  // $micro = node_load($micro->nid);
  // print debug($micro);


  //node_save($micro);
}
