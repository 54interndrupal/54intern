<?php

/**
 * Abstract class, defines interface for swappable search backends.
 */
abstract class SearchlightBackend {
  var $id;
  var $settings;

  /**
   * Directory name of the backend library.
   */
  public $lib_name;

  /**
   * File path relative to the backend library directory.
   */
  public $file_path;

  /**
   * Backend timezone. Default to NULL.
   */
  public $backend_timezone;

  /**
   * Constructor. Unpack backend variable & populate default settings.
   */
  function __construct($id) {
    $this->id = $id;
    $this->settings = variable_get("searchlight_backend_{$this->id}", array()) + $this->settingsDefault();

    // Allow drush to override any backend settings.
    if (function_exists('drush_get_option')) {
      foreach ($this->settings as $k => $v) {
        $drush_option = drush_get_option('sl-' . str_replace('_', '-', $k));
        if (isset($drush_option)) {
          $this->settings[$k] = $drush_option;
        }
      }
    }
  }

  /**
   * Array of default settings for this search backend.
   */
  function settingsDefault() {
    return array();
  }

  /**
   * System settings form for this search backend.
   */
  function settingsForm($values) {
    return array();
  }

  /**
   * Views integration methods ================================================
   */

  /**
   * Backend callback for filter, argument views handler
   * $handler->option_definition() method.
   */
  function viewsOptionDefinition(&$handler) {
    return array(
      'hideEmpty' => array('default' => TRUE),
    );
  }

  /**
   * Backend callback for filter, argument views handler
   * $handler->options_form() method.
   */
  function viewsOptionsForm(&$form, &$form_state, &$handler) {
    $form['hideEmpty'] = array(
      '#title' => t('Hide all results when empty'),
      '#type' => 'checkbox',
      '#default_value' => $handler->options['hideEmpty'],
    );
  }

  /**
   * Backend callback for filter handler $handler->value_form() method.
   */
  function viewsValueForm(&$form, &$form_state, &$handler) {
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#size' => 30,
      '#default_value' => $handler->value,
    );
    if (isset($handler->options['expose']['identifier'])) {
      $identifier = $handler->options['expose']['identifier'];
      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier])) {
        $form_state['input'][$identifier] = $handler->value;
      }
    }
  }

  /**
   * Initialize a client for the search backend.
   *
   * @param $datasource
   */
  function initClient($datasource) { }

  /**
   * Execute a query using the search backend. Should return an array with the
   * following keys:
   *
   *   'result': An array of base field IDs, e.g. nids.
   *   'total': Total number of non-paged results.
   *   'raw': The raw result object/array/data from the search client.
   */
  function executeQuery(&$client, $datasource, $query = '') { }

  /**
   * Set any custom options for the search backend.
   */
  function setOptions(&$client, $datasource, $options) { }

  /**
   * Set a filter parameter for the search backend.
   */
  function setFilter(&$client, $datasource, $filters) { }

  /**
   * Set a sort parameter for the search backend.
   */
  function setSort(&$client, $datasource, $sorts) { }

  /**
   * Set a pager/limit parameter for the search backend.
   */
  function setPager(&$client, $offset, $limit) { }

  /**
   * Set node_access attribute filters.
   */
  function setNodeAccess(&$client) { }

  /**
   * Get defined indexes.
   */
  function getIndexes() {
    return array('main' => 'main');
  }

  /**
   * Return if field can be used for ordering.
   */
  function canOrderBy($field_info) {
    return $field_info['usage'] !== 'content';
  }

  /**
   * Backend library helpers ==================================================
   */

  /**
   * Check and display the library status.
   *
   * @see getLibrary().
   */
  function libraryStatusForm($download_link = '') {
    if ($file = $this->getLibrary()) {
      if (strpos($file, DRUPAL_ROOT . '/') === 0) {
        $file = drupal_substr($file, drupal_strlen(DRUPAL_ROOT . '/'));
      }
      $form = array(
        '#type' => 'item',
        '#title' => t('Backend library'),
        '#markup' => t('Library found at %file.', array('%file' => $file)),
      );
    }
    else {
      $form = array(
        '#type' => 'item',
        '#title' => t('Backend library'),
        '#markup' => t('Could not find the library. Please download form !link and put the library in your !libraries directory. E.g. %example.', array(
          '!libraries' => l('libraries', 'http://drupal.org/project/libraries'),
          '!link' => $download_link,
          '%example' => 'sites/all/libraries/' . $this->lib_name . '/' . $this->file_path,
        )),
      );
    }

    return $form;
  }

  /**
   * Include backend library.
   *
   * @see getLibrary().
   */
  function includeLibrary() {
    if ($file = $this->getLibrary()) {
      require_once $file;
      return $file;
    }
    return FALSE;
  }

  /**
   * Get library's full path.
   */
  function getLibrary() {
    if (empty($this->lib_name) || empty($this->file_path)) {
      return FALSE;
    }

    if (module_exists('libraries')) {
      $lib_path = libraries_get_path($this->lib_name);
    }
    else {
      // Default location.
      $lib_path = 'sites/all/libraries/' . $this->lib_name;
    }

    $file = DRUPAL_ROOT . '/' . $lib_path . '/' . $this->file_path;
    if (is_file($file)) {
      return $file;
    }

    return FALSE;
  }

  /**
   * Utility date methods =====================================================
   */

  /**
   * Retrieve a from & to timestamps for a given granularity unit and base
   * timestamp.
   */
  function dateRange($timestamp, $granularity = 'month') {
    // Query backend with the backend timezone.
    if (isset($this->backend_timezone)) {
      $timezone = date_default_timezone_get();
      date_default_timezone_set($this->backend_timezone);
    }

    switch ($granularity) {
      case 'month':
        $from = mktime(0, 0, 0, date('m', $timestamp), 1, date('Y', $timestamp));
        $to   = mktime(23, 59, 59, date('m', $timestamp), cal_days_in_month(CAL_GREGORIAN, date('m', $timestamp), date('Y', $timestamp)), date('Y', $timestamp));
        break;
      case 'day':
        $from = mktime(0, 0, 0, date('m', $timestamp), date('d', $timestamp), date('Y', $timestamp));
        $to   = mktime(23, 59, 59, date('m', $timestamp), date('d', $timestamp), date('Y', $timestamp));
        break;
      case 'year':
        $from = mktime(0, 0, 0, 1, 1, date('Y', $timestamp));
        $to   = mktime(23, 59, 59, 12, cal_days_in_month(CAL_GREGORIAN, 12, date('Y', $timestamp)), date('Y', $timestamp));
        break;
    }

    // Set back the user time zone.
    // This can be confusing if user has a different timezone than the backend.
    if (isset($timezone)) {
      date_default_timezone_set($timezone);
    }

    return array('from' => $from, 'to' => $to);
  }

  /**
   * Utility filter methods =====================================================
   */

  /**
   * To be overriden. Special handling of fitlers.
   */
  function prepareFilterValue($filter_info, $value) {
    return $value;
  }

  /**
   * Facet methods ============================================================
   */

  /**
   * Execute backend operations to determine the top facets for a given field.
   *
   * @return A result array, each with a sub-array of items containing:
   *
   * 'id': The primary ID for this item.
   * 'count': The number of entries that belong to this facet item.
   */
  function facetBuild(&$client, $datasource, $query = '', $facets) {
    return array();
  }

  /**
   * Build a views join and add it to view query to ensure only un-indexed
   * content is returned.
   */
  function queryFresh(&$sql_query) {
    $join = new views_join();
    $join->construct('searchlight_search', $sql_query->base_table, $sql_query->base_field, 'id', "searchlight_search.type = '{$sql_query->base_table}' AND searchlight_search.status = 0", 'INNER');
    $sql_query->table_queue['searchlight_search'] = array(
      'table' => 'searchlight_search',
      'num' => 1,
      'alias' => 'searchlight_search',
      'join' => $join,
      'relationship' => $sql_query->base_table,
    );
  }

  /**
   * Invalidate the search index associated with this datasource.
   */
  function invalidateIndex($datasource) { }

  /**
   * Indexing job methods ============================================================
   */

  /**
   * Main indexing function.
   *
   * @see Batch API for use of context.
   */
  function index($jobs, &$context) { }

  /**
   * Drush methods ============================================================
   */

  /**
   * Start a search backend daemon process through drush.
   */
  function drushSearchd($command = 'start') { }

  /**
   * Start a search backend indexing process through drush.
   */
  function drushIndex() { }

  /**
   * Write search backend configuration files through drush.
   */
  function drushConf() { }

  /**
   * Execute functionality on a drush cron run.
   */
  function drushCron() { }

  /**
   * When a new site is installed via Aegir.
   */
  function drushAegirInstall() { }

  /**
   * When a site is migrated via Aegir.
   */
  function drushAegirDeploy() { }
}
