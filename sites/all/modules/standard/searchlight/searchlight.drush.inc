<?php
// $Id$

/**
 * Implements hook_drush_command().
 */
function searchlight_drush_command() {
  $items = array();
  $items['searchlight-conf'] = array(
    'callback' => 'drush_searchlight_conf',
    'description' => 'Set the Searchlight configuration for the current site.',
    'drupal dependencies' => array('searchlight'),
  );
  $items['searchlight-index'] = array(
    'callback' => 'drush_searchlight_index',
    'description' => 'Re-generate the Searchlight index for the current site.',
    'drupal dependencies' => array('searchlight'),
  );
  $items['searchlight-searchd'] = array(
    'callback' => 'drush_searchlight_searchd',
    'description' => 'Start the backend search daemon for the current site.',
    'drupal dependencies' => array('searchlight'),
    'options' => array(
      '--sl-jar-path=path' => 'Solr: Full path to the Apache Solr application to be used.',
    ),
  );
  $items['searchlight-unlock'] = array(
    'callback' => 'drush_searchlight_unlock',
    'description' => 'Unlock indexing (force).',
    'drupal dependencies' => array('searchlight'),
  );
  $items['searchlight-batch-index'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array('job' => ''),
    'description' => 'Start a batch indexing process.',
    'drupal dependencies' => array('searchlight'),
  );
  return $items;
}

/**
 * Generate the configuration file for the current site.
 */
function drush_searchlight_conf() {
  $backend = searchlight_get_backend();
  $backend->drushConf();
}

/**
 * Generate new indexes for the current site.
 */
function drush_searchlight_index() {
  $backend = searchlight_get_backend();
  $backend->drushIndex();
}

/**
 * Start or stop the search daemon.
 */
function drush_searchlight_searchd($command = 'start') {
  $backend = searchlight_get_backend();
  $backend->drushSearchd($command);
}

/**
 * Unlock indexing (force).
 */
function drush_searchlight_unlock() {
  variable_del('searchlight_indexing_locked');
  drush_log('Indexing unlocked.', 'success');
}

/**
 * After cron has been run succesfully.
 */
function drush_searchlight_post_core_cron() {
  $backend = searchlight_get_backend();
  $backend->drushCron();
}

/**
 * Start batch indexing.
 */
function drush_searchlight_batch_index($job) {
  searchlight_create_batch_indexing($job, TRUE);
}
