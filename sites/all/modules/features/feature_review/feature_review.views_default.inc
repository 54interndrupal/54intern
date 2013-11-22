<?php
/**
 * @file
 * feature_review.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function feature_review_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'company_reviews_in_blocks';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'company reviews in blocks';
  $view->core = '7';
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重设';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = '当前还没有任何点评';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: 内容: 作者 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: 内容: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['gid']['default_argument_options']['code'] = 'return arg(1);';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: 内容: 已发表 */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: 内容: 类型 */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'review' => 'review',
  );

  /* Display: 热门企业点评 */
  $handler = $view->new_display('block', '热门企业点评', 'block_company_top_reviews');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '最新企业点评';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['element_type'] = '0';
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* 字段: 字段: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'field_data_og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['path'] = 'company/[og_group_ref-target_id]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['alt'] = '[og_group_ref]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['og_group_ref']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '8',
  );
  /* 字段: OG membership: Group ID */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['gid']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['gid']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['gid']['element_type'] = '0';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: 内容: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;

  /* Display: 最新企业点评 */
  $handler = $view->new_display('block', '最新企业点评', 'block_company_recent_reviews');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '热门企业评论';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['element_type'] = '0';
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* 字段: 字段: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'field_data_og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['path'] = 'company/[og_group_ref-target_id]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['alt'] = '[og_group_ref]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['max_length'] = '12';
  $handler->display->display_options['fields']['og_group_ref']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['element_type'] = '0';
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '10',
  );
  /* 字段: OG membership: Group ID */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['element_type'] = '0';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: 内容: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;

  /* Display: 企业最新点评 */
  $handler = $view->new_display('panel_pane', '企业最新点评', 'panel_pane_1');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'c-10';
  $handler->display->display_options['display_description'] = '企业的最新一条点评';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '2';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 用户: 头像 */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_class'] = 'framed';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['picture']['link_photo_to_profile'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = '50_50';
  $handler->display->display_options['fields']['picture']['imagecache_preset'] = '50_50';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '5';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['element_class'] = 'c-6';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '120';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* 字段: OG membership: Group ID */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['gid']['alter']['text'] = '查看更多>>';
  $handler->display->display_options['fields']['gid']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['gid']['alter']['path'] = '/company/[gid]';
  $handler->display->display_options['fields']['gid']['alter']['alt'] = '查看更多点评';
  $handler->display->display_options['fields']['gid']['alter']['link_class'] = 'c-7';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  /* 字段: 内容: 企业印象 */
  $handler->display->display_options['fields']['field_company_evaluation']['id'] = 'field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['table'] = 'field_data_field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['field'] = 'field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['label'] = '';
  $handler->display->display_options['fields']['field_company_evaluation']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_evaluation']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_company_evaluation']['delta_offset'] = '0';
  /* 字段: 内容: 培训力度 */
  $handler->display->display_options['fields']['field_training_value']['id'] = 'field_training_value';
  $handler->display->display_options['fields']['field_training_value']['table'] = 'field_data_field_training_value';
  $handler->display->display_options['fields']['field_training_value']['field'] = 'field_training_value';
  $handler->display->display_options['fields']['field_training_value']['label'] = '';
  $handler->display->display_options['fields']['field_training_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_training_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_training_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_training_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: 内容: 实习待遇 */
  $handler->display->display_options['fields']['field_treatment_value']['id'] = 'field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['table'] = 'field_data_field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['field'] = 'field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['label'] = '';
  $handler->display->display_options['fields']['field_treatment_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treatment_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_treatment_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_treatment_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: 内容: 综合实习价值 */
  $handler->display->display_options['fields']['field_overall_value']['id'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['table'] = 'field_data_field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['field'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['label'] = '';
  $handler->display->display_options['fields']['field_overall_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_overall_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_overall_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 0,
    'style' => 'user',
    'text' => 'none',
  );
  /* 字段: 内容: 转正可能性 */
  $handler->display->display_options['fields']['field_regularize_value']['id'] = 'field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['table'] = 'field_data_field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['field'] = 'field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_regularize_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_regularize_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['gid']['default_argument_options']['code'] = 'return arg(1);';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';

  /* Display: 企业点评列表 */
  $handler = $view->new_display('panel_pane', '企业点评列表', 'panel_pane_2');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'c-1';
  $handler->display->display_options['display_description'] = '企业的最新点评列表';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: 内容: 作者 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 用户: 头像 */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_class'] = 'framed';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = '50_50';
  $handler->display->display_options['fields']['picture']['imagecache_preset'] = '50_50';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '5';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['element_class'] = 'c-6';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* 字段: 内容: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="">查看详细>></a>';
  $handler->display->display_options['fields']['nid']['alter']['path'] = '/node/[nid]';
  $handler->display->display_options['fields']['nid']['alter']['link_class'] = 'c-7';
  $handler->display->display_options['fields']['nid']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* 字段: 内容: 综合实习价值 */
  $handler->display->display_options['fields']['field_overall_value']['id'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['table'] = 'field_data_field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['field'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['label'] = '';
  $handler->display->display_options['fields']['field_overall_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_overall_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_overall_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'user',
    'text' => 'none',
  );
  /* 字段: 内容: 培训力度 */
  $handler->display->display_options['fields']['field_training_value']['id'] = 'field_training_value';
  $handler->display->display_options['fields']['field_training_value']['table'] = 'field_data_field_training_value';
  $handler->display->display_options['fields']['field_training_value']['field'] = 'field_training_value';
  $handler->display->display_options['fields']['field_training_value']['label'] = '';
  $handler->display->display_options['fields']['field_training_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_training_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_training_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_training_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: 内容: 企业印象 */
  $handler->display->display_options['fields']['field_company_evaluation']['id'] = 'field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['table'] = 'field_data_field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['field'] = 'field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['label'] = '';
  $handler->display->display_options['fields']['field_company_evaluation']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_evaluation']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_company_evaluation']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_company_evaluation']['delta_offset'] = '0';
  /* 字段: Content revision: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'm-d';
  /* 字段: 内容: 实习待遇 */
  $handler->display->display_options['fields']['field_treatment_value']['id'] = 'field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['table'] = 'field_data_field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['field'] = 'field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['label'] = '';
  $handler->display->display_options['fields']['field_treatment_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treatment_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_treatment_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_treatment_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: 内容: 转正可能性 */
  $handler->display->display_options['fields']['field_regularize_value']['id'] = 'field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['table'] = 'field_data_field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['field'] = 'field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['label'] = '';
  $handler->display->display_options['fields']['field_regularize_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_regularize_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_regularize_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_regularize_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* 字段: OG membership: Group ID */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  /* 字段: 字段: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'field_data_og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['path'] = 'company/[og_group_ref-target_id]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['alt'] = '[og_group_ref]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['og_group_ref']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['og_group_ref']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['gid']['default_argument_options']['code'] = 'return arg(1);';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';

  /* Display: 公司点评 */
  $handler = $view->new_display('block', '公司点评', 'block_company_reviews');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '公司点评';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: Content revision: 用户 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: 内容: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
    'value_type' => '',
    'tag' => '',
    'function' => '',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '25',
  );
  /* 字段: Content revision: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['exclude'] = TRUE;
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'Y-m-d';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 字段: Vote results: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['relationship'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value']['precision'] = '0';
  $handler->display->display_options['fields']['value']['separator'] = '';
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div>
  <div class=\'c-5 d-1\'>[name] [timestamp]</div>
  <div class=\'d-2\'><!--[value]--></div>
  <div class=\'c-10 d-3\'>
     [body] 
  </div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['gid']['default_argument_options']['code'] = 'return args[1];';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';

  /* Display: 关于我的最新点评 */
  $handler = $view->new_display('block', '关于我的最新点评', 'block_my_company_reviews');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '公司点评';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: Content revision: 用户 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: 内容: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
    'value_type' => '',
    'tag' => '',
    'function' => '',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '25',
  );
  /* 字段: Content revision: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['exclude'] = TRUE;
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'Y-m-d';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 字段: Vote results: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['relationship'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value']['precision'] = '0';
  $handler->display->display_options['fields']['value']['separator'] = '';
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div>
  <div class=\'c-5 d-1\'>[name] [timestamp]</div>
  <div class=\'d-2\'><!--[value]--></div>
  <div class=\'c-10 d-3\'>
     [body] 
  </div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['gid']['default_argument_options']['code'] = 'return arg(1);';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';

  /* Display: 最新企业实习点评 */
  $handler = $view->new_display('block', '最新企业实习点评', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '最新企业实习点评';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: Content revision: 用户 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: 内容: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
    'value_type' => '',
    'tag' => '',
    'function' => '',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '25',
  );
  /* 字段: Content revision: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['exclude'] = TRUE;
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'Y-m-d';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 字段: Vote results: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['relationship'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value']['precision'] = '0';
  $handler->display->display_options['fields']['value']['separator'] = '';
  /* 字段: 字段: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'field_data_og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['path'] = 'company/[og_group_ref-target_id]';
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  /* 字段: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div>
  <div class=\'c-5 d-1\'>[name] &nbsp;&nbsp;&nbsp; [timestamp]</div>
  <div class=\'d-4\'>[og_group_ref]</div> 
  <div class=\'d-2\'><!--[value]--></div>
  <div class=\'c-10 d-3\'>
     [body] 
  </div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;

  /* Display: 收藏的点评列表 */
  $handler = $view->new_display('panel_pane', '收藏的点评列表', 'panel_pane_3');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'c-1';
  $handler->display->display_options['display_description'] = '用户收藏的最新点评列表';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: 内容: 作者 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: OG membership: OG membership from 节点 */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: Flags: collect */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'collect';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 用户: 头像 */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_class'] = 'framed';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = '50_50';
  $handler->display->display_options['fields']['picture']['imagecache_preset'] = '50_50';
  /* 字段: 用户: 名称 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['max_length'] = '5';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['name']['element_class'] = 'c-6';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* 字段: 内容: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['text'] = '<a href="">查看详细>></a>';
  $handler->display->display_options['fields']['nid']['alter']['path'] = '/node/[nid]';
  $handler->display->display_options['fields']['nid']['alter']['link_class'] = 'c-7';
  $handler->display->display_options['fields']['nid']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* 字段: 内容: 综合实习价值 */
  $handler->display->display_options['fields']['field_overall_value']['id'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['table'] = 'field_data_field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['field'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['label'] = '';
  $handler->display->display_options['fields']['field_overall_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_overall_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_overall_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'user',
    'text' => 'none',
  );
  /* 字段: 内容: 培训力度 */
  $handler->display->display_options['fields']['field_training_value']['id'] = 'field_training_value';
  $handler->display->display_options['fields']['field_training_value']['table'] = 'field_data_field_training_value';
  $handler->display->display_options['fields']['field_training_value']['field'] = 'field_training_value';
  $handler->display->display_options['fields']['field_training_value']['label'] = '';
  $handler->display->display_options['fields']['field_training_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_training_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_training_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_training_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: 内容: 企业印象 */
  $handler->display->display_options['fields']['field_company_evaluation']['id'] = 'field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['table'] = 'field_data_field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['field'] = 'field_company_evaluation';
  $handler->display->display_options['fields']['field_company_evaluation']['label'] = '';
  $handler->display->display_options['fields']['field_company_evaluation']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_evaluation']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_company_evaluation']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_company_evaluation']['delta_offset'] = '0';
  /* 字段: Content revision: Updated date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'node_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = '';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'm-d';
  /* 字段: 内容: 实习待遇 */
  $handler->display->display_options['fields']['field_treatment_value']['id'] = 'field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['table'] = 'field_data_field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['field'] = 'field_treatment_value';
  $handler->display->display_options['fields']['field_treatment_value']['label'] = '';
  $handler->display->display_options['fields']['field_treatment_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_treatment_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_treatment_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_treatment_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: 内容: 转正可能性 */
  $handler->display->display_options['fields']['field_regularize_value']['id'] = 'field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['table'] = 'field_data_field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['field'] = 'field_regularize_value';
  $handler->display->display_options['fields']['field_regularize_value']['label'] = '';
  $handler->display->display_options['fields']['field_regularize_value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_regularize_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_regularize_value']['type'] = 'fivestar_formatter_rating';
  $handler->display->display_options['fields']['field_regularize_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 1,
    'style' => 'average',
    'text' => 'average',
  );
  /* 字段: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '';
  $handler->display->display_options['fields']['counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* 字段: OG membership: Group ID */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['label'] = '';
  $handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  /* 字段: 字段: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'field_data_og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['label'] = '';
  $handler->display->display_options['fields']['og_group_ref']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['path'] = 'company/[og_group_ref-target_id]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['alt'] = '[og_group_ref]';
  $handler->display->display_options['fields']['og_group_ref']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['og_group_ref']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['og_group_ref']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $translatables['company_reviews_in_blocks'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('重设'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('当前还没有任何点评'),
    t('author'),
    t('OG membership from node'),
    t('全部'),
    t('热门企业点评'),
    t('最新企业点评'),
    t('company/[og_group_ref-target_id]'),
    t('[og_group_ref]'),
    t('.'),
    t('热门企业评论'),
    t('企业最新点评'),
    t('企业的最新一条点评'),
    t('查看更多>>'),
    t('/company/[gid]'),
    t('查看更多点评'),
    t('转正可能性'),
    t('View panes'),
    t('企业点评列表'),
    t('企业的最新点评列表'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('<a href="">查看详细>></a>'),
    t('/node/[nid]'),
    t('_blank'),
    t('公司点评'),
    t('revision user'),
    t('Vote results'),
    t('<div>
  <div class=\'c-5 d-1\'>[name] [timestamp]</div>
  <div class=\'d-2\'><!--[value]--></div>
  <div class=\'c-10 d-3\'>
     [body] 
  </div>
</div>'),
    t('关于我的最新点评'),
    t('最新企业实习点评'),
    t('<div>
  <div class=\'c-5 d-1\'>[name] &nbsp;&nbsp;&nbsp; [timestamp]</div>
  <div class=\'d-4\'>[og_group_ref]</div> 
  <div class=\'d-2\'><!--[value]--></div>
  <div class=\'c-10 d-3\'>
     [body] 
  </div>
</div>'),
    t('收藏的点评列表'),
    t('用户收藏的最新点评列表'),
    t('flag'),
  );
  $export['company_reviews_in_blocks'] = $view;

  return $export;
}
