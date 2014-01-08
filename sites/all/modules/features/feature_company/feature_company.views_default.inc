<?php
/**
 * @file
 * feature_company.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function feature_company_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'companys';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'companys';
  $view->core = '7';
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'companys';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重设';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '22';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['total_pages'] = '100';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = '没有找到任何企业';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Flags: bookmarks counter */
  $handler->display->display_options['relationships']['flag_count_rel']['id'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_count_rel']['field'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['flag'] = 'bookmarks';
  /* Relationship: Flags: bookmarks */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'bookmarks';
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* 字段: 内容: 公司Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* 字段: 内容: 公司规模 */
  $handler->display->display_options['fields']['field_company_size']['id'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['table'] = 'field_data_field_company_size';
  $handler->display->display_options['fields']['field_company_size']['field'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['label'] = '';
  $handler->display->display_options['fields']['field_company_size']['element_label_colon'] = FALSE;
  /* 字段: 内容: 行业类别 */
  $handler->display->display_options['fields']['field_industry']['id'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['table'] = 'field_data_field_industry';
  $handler->display->display_options['fields']['field_industry']['field'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['label'] = '';
  $handler->display->display_options['fields']['field_industry']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: Flags: Flag counter */
  $handler->display->display_options['fields']['count']['id'] = 'count';
  $handler->display->display_options['fields']['count']['table'] = 'flag_counts';
  $handler->display->display_options['fields']['count']['field'] = 'count';
  $handler->display->display_options['fields']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['fields']['count']['label'] = '';
  $handler->display->display_options['fields']['count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['count']['suffix'] = '人关注';
  /* Sort criterion: Flags: Flag counter */
  $handler->display->display_options['sorts']['count']['id'] = 'count';
  $handler->display->display_options['sorts']['count']['table'] = 'flag_counts';
  $handler->display->display_options['sorts']['count']['field'] = 'count';
  $handler->display->display_options['sorts']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['sorts']['count']['order'] = 'DESC';
  $handler->display->display_options['sorts']['count']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['count']['expose']['label'] = '关注人数';
  /* Sort criterion: 内容: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created']['expose']['label'] = '发布时间';
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
    'company' => 'company',
  );

  /* Display: 企业点评台 */
  $handler = $view->new_display('panel_pane', '企业点评台', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '搜企业';
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['link_url'] = 'companys1';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重设';
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'sort' => array(
      'bef_format' => 'default',
      'combine' => 1,
      'reset' => 0,
      'reset_label' => '',
    ),
    'field_industry_tid' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
      ),
    ),
    'search' => array(
      'more_options' => array(
        'bef_filter_description' => '',
      ),
    ),
  );
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: bookmarks */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'bookmarks';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'company/[nid]';
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = '[ 更多... ]';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = 'company/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = 'span';
  $handler->display->display_options['fields']['body']['element_class'] = 'body-field';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* 字段: 内容: 公司Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_logo']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_logo']['element_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_wrapper_class'] = 'framed';
  $handler->display->display_options['fields']['field_logo']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '120_30',
    'image_link' => 'content',
  );
  /* 字段: 内容: 公司规模 */
  $handler->display->display_options['fields']['field_company_size']['id'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['table'] = 'field_data_field_company_size';
  $handler->display->display_options['fields']['field_company_size']['field'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['label'] = '';
  $handler->display->display_options['fields']['field_company_size']['element_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 行业类别 */
  $handler->display->display_options['fields']['field_industry']['id'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['table'] = 'field_data_field_industry';
  $handler->display->display_options['fields']['field_industry']['field'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['label'] = '';
  $handler->display->display_options['fields']['field_industry']['element_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_industry']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['element_type'] = '0';
  $handler->display->display_options['fields']['ops']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['ops']['element_default_classes'] = FALSE;
  /* 字段: Content revision: Vid */
  $handler->display->display_options['fields']['vid']['id'] = 'vid';
  $handler->display->display_options['fields']['vid']['table'] = 'node_revision';
  $handler->display->display_options['fields']['vid']['field'] = 'vid';
  $handler->display->display_options['fields']['vid']['label'] = '';
  $handler->display->display_options['fields']['vid']['alter']['text'] = '[vid]';
  $handler->display->display_options['fields']['vid']['element_type'] = '0';
  $handler->display->display_options['fields']['vid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['vid']['element_default_classes'] = FALSE;
  /* 字段: 内容: 工作地点 */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['element_type'] = '0';
  $handler->display->display_options['fields']['field_location']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_location']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_location']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_location']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 综合实习价值 */
  $handler->display->display_options['fields']['field_overall_value']['id'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['table'] = 'field_data_field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['field'] = 'field_overall_value';
  $handler->display->display_options['fields']['field_overall_value']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['field_overall_value']['settings'] = array(
    'widget' => array(
      'fivestar_widget' => 'default',
    ),
    'expose' => 0,
    'style' => 'average',
    'text' => 'none',
  );
  /* 字段: 内容: 点评数 */
  $handler->display->display_options['fields']['field_review_count']['id'] = 'field_review_count';
  $handler->display->display_options['fields']['field_review_count']['table'] = 'field_data_field_review_count';
  $handler->display->display_options['fields']['field_review_count']['field'] = 'field_review_count';
  $handler->display->display_options['fields']['field_review_count']['element_type'] = '0';
  $handler->display->display_options['fields']['field_review_count']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_review_count']['empty'] = '0';
  $handler->display->display_options['fields']['field_review_count']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_review_count']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_review_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: 内容: 最近点评时间 (field_last_review_created) */
  $handler->display->display_options['sorts']['field_last_review_created_value']['id'] = 'field_last_review_created_value';
  $handler->display->display_options['sorts']['field_last_review_created_value']['table'] = 'field_data_field_last_review_created';
  $handler->display->display_options['sorts']['field_last_review_created_value']['field'] = 'field_last_review_created_value';
  $handler->display->display_options['sorts']['field_last_review_created_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_last_review_created_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_last_review_created_value']['expose']['label'] = '最近点评时间 ';
  /* Sort criterion: 内容: 点评数 (field_review_count) */
  $handler->display->display_options['sorts']['field_review_count_value']['id'] = 'field_review_count_value';
  $handler->display->display_options['sorts']['field_review_count_value']['table'] = 'field_data_field_review_count';
  $handler->display->display_options['sorts']['field_review_count_value']['field'] = 'field_review_count_value';
  $handler->display->display_options['sorts']['field_review_count_value']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_review_count_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_review_count_value']['expose']['label'] = '点评数';
  /* Sort criterion: 内容: 综合实习价值 (field_overall_value:rating) */
  $handler->display->display_options['sorts']['field_overall_value_rating']['id'] = 'field_overall_value_rating';
  $handler->display->display_options['sorts']['field_overall_value_rating']['table'] = 'field_data_field_overall_value';
  $handler->display->display_options['sorts']['field_overall_value_rating']['field'] = 'field_overall_value_rating';
  $handler->display->display_options['sorts']['field_overall_value_rating']['order'] = 'DESC';
  $handler->display->display_options['sorts']['field_overall_value_rating']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_overall_value_rating']['expose']['label'] = '综合实习价值';
  /* Sort criterion: 内容: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['expose']['label'] = '更新日期';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: 内容: 行业类别 (field_industry) */
  $handler->display->display_options['arguments']['field_industry_tid']['id'] = 'field_industry_tid';
  $handler->display->display_options['arguments']['field_industry_tid']['table'] = 'field_data_field_industry';
  $handler->display->display_options['arguments']['field_industry_tid']['field'] = 'field_industry_tid';
  $handler->display->display_options['arguments']['field_industry_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_industry_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_industry_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_industry_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'company' => 'company',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: 内容: 行业类别 (field_industry) */
  $handler->display->display_options['filters']['field_industry_tid']['id'] = 'field_industry_tid';
  $handler->display->display_options['filters']['field_industry_tid']['table'] = 'field_data_field_industry';
  $handler->display->display_options['filters']['field_industry_tid']['field'] = 'field_industry_tid';
  $handler->display->display_options['filters']['field_industry_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_industry_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_industry_tid']['expose']['operator_id'] = 'field_industry_tid_op';
  $handler->display->display_options['filters']['field_industry_tid']['expose']['label'] = '按行业查看';
  $handler->display->display_options['filters']['field_industry_tid']['expose']['operator'] = 'field_industry_tid_op';
  $handler->display->display_options['filters']['field_industry_tid']['expose']['identifier'] = 'field_industry_tid';
  $handler->display->display_options['filters']['field_industry_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_industry_tid']['vocabulary'] = 'industry';
  /* Filter criterion: 搜索: Searchlight */
  $handler->display->display_options['filters']['search']['id'] = 'search';
  $handler->display->display_options['filters']['search']['table'] = 'searchlight';
  $handler->display->display_options['filters']['search']['field'] = 'search';
  $handler->display->display_options['filters']['search']['group'] = 1;
  $handler->display->display_options['filters']['search']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['search']['expose']['label'] = '关键字';
  $handler->display->display_options['filters']['search']['expose']['operator'] = 'search_op';
  $handler->display->display_options['filters']['search']['expose']['identifier'] = 'search';
  $handler->display->display_options['filters']['search']['hideEmpty'] = 0;
  $handler->display->display_options['filters']['search']['matchMode'] = '2';
  $handler->display->display_options['argument_input'] = array(
    'field_industry_tid' => array(
      'type' => 'panel',
      'context' => 'entity:apply.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => '内容: 行业类别 (field_industry)',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: 热门企业 */
  $handler = $view->new_display('panel_pane', '热门企业', 'panel_pane_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '热门企业';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['use_more_text'] = '更多...';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'companys';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* 标题: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '热门企业';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: 公司Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '110_64',
    'image_link' => 'content',
  );
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  /* 字段: 内容: 行业类别 */
  $handler->display->display_options['fields']['field_industry']['id'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['table'] = 'field_data_field_industry';
  $handler->display->display_options['fields']['field_industry']['field'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['label'] = '';
  $handler->display->display_options['fields']['field_industry']['alter']['max_length'] = '5';
  $handler->display->display_options['fields']['field_industry']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['element_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 公司规模 */
  $handler->display->display_options['fields']['field_company_size']['id'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['table'] = 'field_data_field_company_size';
  $handler->display->display_options['fields']['field_company_size']['field'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['label'] = '';
  $handler->display->display_options['fields']['field_company_size']['element_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: Flags: Flag counter */
  $handler->display->display_options['fields']['count']['id'] = 'count';
  $handler->display->display_options['fields']['count']['table'] = 'flag_counts';
  $handler->display->display_options['fields']['count']['field'] = 'count';
  $handler->display->display_options['fields']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['fields']['count']['label'] = '';
  $handler->display->display_options['fields']['count']['element_type'] = '0';
  $handler->display->display_options['fields']['count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['count']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['count']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['count']['separator'] = '';
  $handler->display->display_options['fields']['count']['suffix'] = '人关注';
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '36';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  /* 字段: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['element_type'] = '0';
  $handler->display->display_options['fields']['ops']['element_wrapper_type'] = '0';

  /* Display: 我关注的企业 */
  $handler = $view->new_display('panel_pane', '我关注的企业', 'panel_pane_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '搜企业';
  $handler->display->display_options['link_url'] = 'companys1';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '搜索企业';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重设';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'sort' => array(
      'bef_format' => 'default',
      'combine' => 1,
      'reset' => 0,
      'reset_label' => '',
    ),
    'keys' => array(
      'more_options' => array(
        'bef_filter_description' => '',
      ),
    ),
    'field_industry_tid' => array(
      'bef_format' => 'bef_links',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
      ),
    ),
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: bookmarks counter */
  $handler->display->display_options['relationships']['flag_count_rel']['id'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_count_rel']['field'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['flag'] = 'bookmarks';
  /* Relationship: Flags: bookmarks */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'bookmarks';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'company/[nid]';
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = '[ 更多... ]';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = 'company/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = 'span';
  $handler->display->display_options['fields']['body']['element_class'] = 'body-field';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* 字段: 内容: 公司Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_wrapper_class'] = 'framed';
  $handler->display->display_options['fields']['field_logo']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '120_30',
    'image_link' => 'content',
  );
  /* 字段: 内容: 公司规模 */
  $handler->display->display_options['fields']['field_company_size']['id'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['table'] = 'field_data_field_company_size';
  $handler->display->display_options['fields']['field_company_size']['field'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['label'] = '';
  $handler->display->display_options['fields']['field_company_size']['element_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 行业类别 */
  $handler->display->display_options['fields']['field_industry']['id'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['table'] = 'field_data_field_industry';
  $handler->display->display_options['fields']['field_industry']['field'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['label'] = '';
  $handler->display->display_options['fields']['field_industry']['element_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: Flags: Flag counter */
  $handler->display->display_options['fields']['count']['id'] = 'count';
  $handler->display->display_options['fields']['count']['table'] = 'flag_counts';
  $handler->display->display_options['fields']['count']['field'] = 'count';
  $handler->display->display_options['fields']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['fields']['count']['label'] = '';
  $handler->display->display_options['fields']['count']['element_type'] = '0';
  $handler->display->display_options['fields']['count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['count']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['count']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['count']['separator'] = '';
  /* 字段: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['element_type'] = '0';
  $handler->display->display_options['fields']['ops']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['ops']['element_default_classes'] = FALSE;
  /* 字段: Content revision: Vid */
  $handler->display->display_options['fields']['vid']['id'] = 'vid';
  $handler->display->display_options['fields']['vid']['table'] = 'node_revision';
  $handler->display->display_options['fields']['vid']['field'] = 'vid';
  $handler->display->display_options['fields']['vid']['label'] = '';
  $handler->display->display_options['fields']['vid']['alter']['text'] = '[vid]';
  $handler->display->display_options['fields']['vid']['element_type'] = '0';
  $handler->display->display_options['fields']['vid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['vid']['element_default_classes'] = FALSE;
  /* 字段: 内容: 工作地点 */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['element_type'] = '0';
  $handler->display->display_options['fields']['field_location']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_location']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 最近点评时间 */
  $handler->display->display_options['fields']['field_last_review_created']['id'] = 'field_last_review_created';
  $handler->display->display_options['fields']['field_last_review_created']['table'] = 'field_data_field_last_review_created';
  $handler->display->display_options['fields']['field_last_review_created']['field'] = 'field_last_review_created';
  $handler->display->display_options['fields']['field_last_review_created']['label'] = '';
  $handler->display->display_options['fields']['field_last_review_created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_last_review_created']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* 字段: 内容: 点评数 */
  $handler->display->display_options['fields']['field_review_count']['id'] = 'field_review_count';
  $handler->display->display_options['fields']['field_review_count']['table'] = 'field_data_field_review_count';
  $handler->display->display_options['fields']['field_review_count']['field'] = 'field_review_count';
  $handler->display->display_options['fields']['field_review_count']['label'] = '';
  $handler->display->display_options['fields']['field_review_count']['element_type'] = '0';
  $handler->display->display_options['fields']['field_review_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_review_count']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_review_count']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_review_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
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
    'style' => 'average',
    'text' => 'none',
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Flags: Flagged time */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'flag_content';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'company' => 'company',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['argument_input'] = array(
    'field_industry_tid' => array(
      'type' => 'panel',
      'context' => 'entity:apply.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => '内容: 行业类别 (field_industry)',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';

  /* Display: 企业搜索结果（搜索结果页面） */
  $handler = $view->new_display('panel_pane', '企业搜索结果（搜索结果页面）', 'panel_pane_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '搜企业';
  $handler->display->display_options['link_url'] = 'companys1';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '搜索企业';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重设';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'sort' => array(
      'bef_format' => 'default',
      'combine' => 1,
      'reset' => 0,
      'reset_label' => '',
    ),
    'keys' => array(
      'more_options' => array(
        'bef_filter_description' => '',
      ),
    ),
    'field_industry_tid' => array(
      'bef_format' => 'bef_links',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'bef_filter_description' => '',
      ),
    ),
  );
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: bookmarks */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'bookmarks';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* 字段: 内容: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nid']['element_default_classes'] = FALSE;
  /* 字段: 内容: 标题 */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'company/[nid]';
  $handler->display->display_options['fields']['title']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '10';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* 字段: 内容: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['body']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['body']['alter']['more_link'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['more_link_text'] = '[ 更多... ]';
  $handler->display->display_options['fields']['body']['alter']['more_link_path'] = 'company/[nid]';
  $handler->display->display_options['fields']['body']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = 'span';
  $handler->display->display_options['fields']['body']['element_class'] = 'body-field';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_plain';
  /* 字段: 内容: 公司Logo */
  $handler->display->display_options['fields']['field_logo']['id'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['table'] = 'field_data_field_logo';
  $handler->display->display_options['fields']['field_logo']['field'] = 'field_logo';
  $handler->display->display_options['fields']['field_logo']['label'] = '';
  $handler->display->display_options['fields']['field_logo']['element_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_logo']['element_wrapper_class'] = 'framed';
  $handler->display->display_options['fields']['field_logo']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_logo']['settings'] = array(
    'image_style' => '120_30',
    'image_link' => 'content',
  );
  /* 字段: 内容: 公司规模 */
  $handler->display->display_options['fields']['field_company_size']['id'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['table'] = 'field_data_field_company_size';
  $handler->display->display_options['fields']['field_company_size']['field'] = 'field_company_size';
  $handler->display->display_options['fields']['field_company_size']['label'] = '';
  $handler->display->display_options['fields']['field_company_size']['element_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_company_size']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_company_size']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 行业类别 */
  $handler->display->display_options['fields']['field_industry']['id'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['table'] = 'field_data_field_industry';
  $handler->display->display_options['fields']['field_industry']['field'] = 'field_industry';
  $handler->display->display_options['fields']['field_industry']['label'] = '';
  $handler->display->display_options['fields']['field_industry']['element_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_industry']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_industry']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = '';
  $handler->display->display_options['fields']['ops']['element_label_colon'] = FALSE;
  /* 字段: 内容: 工作地点 */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['label'] = '';
  $handler->display->display_options['fields']['field_location']['element_type'] = '0';
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_location']['type'] = 'taxonomy_term_reference_plain';
  /* 字段: 内容: 点评数 */
  $handler->display->display_options['fields']['field_review_count']['id'] = 'field_review_count';
  $handler->display->display_options['fields']['field_review_count']['table'] = 'field_data_field_review_count';
  $handler->display->display_options['fields']['field_review_count']['field'] = 'field_review_count';
  $handler->display->display_options['fields']['field_review_count']['label'] = '';
  $handler->display->display_options['fields']['field_review_count']['element_type'] = '0';
  $handler->display->display_options['fields']['field_review_count']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_review_count']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_review_count']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_review_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
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
    'style' => 'average',
    'text' => 'none',
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: 搜索: Searchlight */
  $handler->display->display_options['arguments']['search']['id'] = 'search';
  $handler->display->display_options['arguments']['search']['table'] = 'searchlight';
  $handler->display->display_options['arguments']['search']['field'] = 'search';
  $handler->display->display_options['arguments']['search']['default_action'] = 'default';
  $handler->display->display_options['arguments']['search']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['search']['default_argument_options']['index'] = '2';
  $handler->display->display_options['arguments']['search']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['search']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['search']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['search']['hideEmpty'] = 0;
  $handler->display->display_options['arguments']['search']['matchMode'] = '2';
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'company' => 'company',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['argument_input'] = array(
    'field_industry_tid' => array(
      'type' => 'panel',
      'context' => 'entity:apply.uid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => '内容: 行业类别 (field_industry)',
    ),
  );
  $handler->display->display_options['inherit_panels_path'] = '1';
  $translatables['companys'] = array(
    t('Master'),
    t('companys'),
    t('more'),
    t('Apply'),
    t('重设'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('没有找到任何企业'),
    t('counter'),
    t('flag'),
    t('.'),
    t(','),
    t('人关注'),
    t('关注人数'),
    t('发布时间'),
    t('企业点评台'),
    t('搜企业'),
    t('company/[nid]'),
    t('_blank'),
    t('[ 更多... ]'),
    t('Flag link'),
    t('[vid]'),
    t('工作地点'),
    t('综合实习价值'),
    t('点评数'),
    t('最近点评时间 '),
    t('更新日期'),
    t('全部'),
    t('按行业查看'),
    t('关键字'),
    t('View panes'),
    t('热门企业'),
    t('更多...'),
    t('我关注的企业'),
    t('搜索企业'),
    t('排序'),
    t('升序'),
    t('降序'),
    t('企业搜索结果（搜索结果页面）'),
  );
  $export['companys'] = $view;

  return $export;
}
