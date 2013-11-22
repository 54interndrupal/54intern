<?php
/**
 * @file
 * feature_review.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_review_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_views_api().
 */
function feature_review_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function feature_review_node_info() {
  $items = array(
    'review' => array(
      'name' => t('点评'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('点评标题'),
      'help' => '',
    ),
  );
  return $items;
}
