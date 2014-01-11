<?php

/**
 * Implements hook_views_plugins().
 */
function searchlight_views_plugins() {
  return array(
    'query' => array(
      'searchlight' => array(
        'file' => 'searchlight_plugin_query_v3.inc',
        'path' => drupal_get_path('module', 'searchlight') . '/views',
        'title' => t('Searchlight'),
        'help' => t('Searchlight query plugin.'),
        'handler' => 'searchlight_plugin_query',
      ),
    ),
    'display' => array(
      'searchlight_multivalue' => array(
        'path' => drupal_get_path('module', 'searchlight') . '/views',
        'theme' => 'views_view',
        'uses hook menu' => FALSE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'title' => t('Searchlight multivalue'),
        'help' => t('Expose a view as an multivalue attribute to be used with a Searchlight datasource.'),
        'handler' => 'searchlight_plugin_display_multivalue',
        'admin' => t('Searchlight multivalue'),
      ),
      'searchlight_solr' => array(
        'path' => drupal_get_path('module', 'searchlight') . '/views',
        'theme' => 'views_view',
        'uses hook menu' => FALSE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'title' => t('Searchlight Solr'),
        'help' => t('Expose a view as an multivalue attribute to be used with a Searchlight datasource.'),
        'handler' => 'searchlight_plugin_display_solr',
        'admin' => t('Searchlight Solr'),
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function searchlight_views_data() {
  $data = array();
  $data['searchlight']['table']['group'] = t('Search');
  $data['searchlight']['table']['join'] = array(
    '#global' => array(),
  );
  $data['searchlight']['search'] = array(
    'title' => t('Searchlight'),
    'help' => t('Filter results by a Searchlight search.'),
    'argument' => array('handler' => 'searchlight_handler_argument_search'),
    'filter' => array('handler' => 'searchlight_handler_filter_search'),
    'sort' => array('handler' => 'searchlight_handler_sort_search'),
  );
  $data['searchlight']['facets'] = array(
    'title' => t('Active facets'),
    'help' => t('Filter results by active Searchlight facets.'),
    'filter' => array('handler' => 'searchlight_handler_filter_facets'),
  );
  $data['searchlight']['facet_link'] = array(
    'title' => t('Facet URL'),
    'help' => t('Generate a facet URL that can be used as a Views render token.'),
    'field' => array('handler' => 'searchlight_handler_field_facet_link'),
  );
  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function searchlight_views_data_alter(&$data) {
  if (!empty($data['node_access']['nid']) && empty($data['node_access']['nid']['field'])) {
    $data['node_access']['nid']['field'] = array(
      'handler' => 'searchlight_handler_field_node_access',
      'help' => t('Node access fields for indexing by Searchlight search backends.'),
    );
  }

  // A special handler for taxonomy_index table. Taxonomy views integration
  // in D7 sometimes makes use of `taxonomy_term_data` but when used for
  // arguments, filters, etc. directly queries against `taxonomy_index`.
  if (module_exists('taxonomy')) {
    $data['taxonomy_index']['searchlight_tid'] = array(
      'title' => t('Term ID (Searchlight)'),
      'help' => t('The taxonomy term ID'),
      'real field' => 'tid',
      'field' => array(
        'field' => 'tid',
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
    );
  }

  // A special handler for field field.
  // TODO: node only for now.
  $base_tables = array('node' => TRUE, 'taxonomy_term_data' => TRUE);
  foreach ($data as $key_table => $table) {
    if (empty($table['table']['join']) || !array_intersect_key($table['table']['join'], $base_tables)) {
      continue;
    }
    foreach ($table as $key_column => $column) {
      if (empty($column['field']['handler']) || $column['field']['handler'] !== 'views_handler_field_field') {
        continue;
      }
      $data[$key_table][$key_column]['field']['handler'] = 'searchlight_handler_field_field';
    }
  }

  // OG UID field handler. Needed to allow filtering directly against OG UID.
  if (module_exists('og_views')) {
    $data['og_uid']['nid']['field'] = array(
      'title' => t('Group ID'),
      'handler' => 'views_handler_field',
    );
  }

  // If Searchlight buddy system is off, replace core search handlers.
  if (module_exists('search') && !variable_get('searchlight_buddysystem', FALSE)) {
    $data['search_index']['score']['sort'] = $data['searchlight']['search']['sort'];
    $data['search_index']['keys']['filter'] = $data['searchlight']['search']['filter'];

    // Remove unsupported tables.
    unset($data['search_index']['score']['field']);
    unset($data['search_dataset']);
    unset($data['search_total']);
    unset($data['search_node_links_from']);
    unset($data['search_node_links_to']);
  }
}

/**
 * Init (or more accurately "hijack") the Views query plugin. This is called
 * from the pre_query() method of the searchlight filter, argument handlers.
 */
function searchlight_views_init_query(&$view) {

  // The following is a copy of the $view->query_init() method, with the only
  // difference being that we use the searchlight backend plugin rather than
  // the default views query plugin and pass the backend to the query plugin.
  if (!empty($view->query)) {
    $class = get_class($view->query);
    if ($class && $class != 'stdClass' && !empty($view->query->searchlight)) {
      // return if query is already initialized.
      return;
    }
  }

  // Create and initialize the query object. If no backend is present, leave
  // the view alone.
  if ($backend = searchlight_get_backend()) {
    $views_data = views_fetch_data($view->base_table);
    $view->base_field = $views_data['table']['base']['field'];
    if (!empty($views_data['table']['base']['database'])) {
      $view->base_database = $views_data['table']['base']['database'];
    }

    // Check that an active datasource can be found for this base table.
    if (searchlight_get_datasource($view->base_table)) {
      // Add Searchlight JS.
      drupal_add_js(drupal_get_path('module', 'searchlight') . '/searchlight.js');

      $query_options = $view->display_handler->get_option('query');
      $view->query = searchlight_get_query($view->base_table, $view->base_field, $query_options['options']);
    }
  }
}

/**
 * Implements hook_views_default_views().
 */
function searchlight_views_default_views() {
  $views = array();

  //
  // Node access ==============================================================
  //
  $realms = array();
  $result = db_query("SELECT realm FROM {node_access} GROUP BY realm");
  foreach ($result as $row) {
    $realms[$row->realm] = $row->realm;
  }
  // Allow modules to declare their realms in an alter hook. This allows
  // searchlight datasources to include references to node_access realms
  // prior to the creation of any nodes that actually use those realms in
  // node_access entries.
  drupal_alter('searchlight_node_access_realms', $realms);

  if (!empty($realms)) {
    $view = new view;
    $view->name = 'searchlight_node_access';
    $view->description = ''; // TODO
    $view->tag = 'searchlight';
    $view->base_table = 'node';
    $view->human_name = ''; // TODO
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE;
    // Fields.
    $fields = array();
    $fields['nid']['id'] = 'nid';
    $fields['nid']['table'] = 'node';
    $fields['nid']['field'] = 'nid';
    $fields['nid']['label'] = '';
    $fields['realm']['id'] = 'realm';
    $fields['realm']['table'] = 'node_access';
    $fields['realm']['field'] = 'nid';
    $fields['realm']['label'] = '';
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['fields'] = $fields;
    /* Display: Searchlight multivalue */
    foreach ($realms as $realm) {
      $fields['realm']['realm'] = $realm;
      $handler = $view->new_display('searchlight_multivalue', $realm, 'searchlight_' . $realm);
      $handler->display->display_options['pager']['type'] = 'none';
      $handler->display->display_options['defaults']['fields'] = FALSE;
      $handler->display->display_options['fields'] = $fields;
      $handler->display->display_options['searchlight_multivalue'] = array(
        'field' => "node_access_gid_{$realm}",
        'label_field' => "node_access_gid_{$realm}",
      );
    }
    $views[$view->name] = $view;
  }

  if (module_exists('taxonomy')) {
    //
    // Node - Taxonomy =================================================================
    //
    $view = new view;
    $view->name = 'searchlight_term_data';
    $view->description = 'Multivalue fields for nodes';
    $view->tag = 'searchlight';
    $view->base_table = 'node';
    $view->human_name = 'searchlight_term_data';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE;
    // Relationship.
    $relationships['term_node_tid']['id'] = 'term_node_tid';
    $relationships['term_node_tid']['table'] = 'node';
    $relationships['term_node_tid']['field'] = 'term_node_tid';
    $relationships['term_node_tid']['required'] = 1; // TODO: do we support empty value.
    $relationships['term_node_tid']['vocabularies'] = array();
    // Fields.
    $fields = array();
    $fields['nid']['id'] = 'nid';
    $fields['nid']['table'] = 'node';
    $fields['nid']['field'] = 'nid';
    $fields['nid']['label'] = '';
    $fields['searchlight_tid']['id'] = 'searchlight_tid';
    $fields['searchlight_tid']['table'] = 'taxonomy_index';
    $fields['searchlight_tid']['field'] = 'searchlight_tid';
    $fields['searchlight_tid']['label'] = '';
    $fields['searchlight_tid']['separator'] = '';
    $fields['name']['id'] = 'name';
    $fields['name']['table'] = 'taxonomy_term_data';
    $fields['name']['field'] = 'name';
    $fields['name']['label'] = '';
    $fields['name']['relationship'] = 'term_node_tid';
    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';
    $handler->display->display_options['relationships'] = $relationships;
    $handler->display->display_options['fields'] = $fields;
    /* Display: All terms */
    $handler = $view->new_display('searchlight_multivalue', 'all', 'searchlight_multivalue_all');
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['searchlight_multivalue'] = array(
      'field' => 'taxonomy_index_tid',
      'label_field' => 'taxonomy_term_data_node_name',
      'override' => array(
        'name' => 'taxonomy_index_tid',
        'label' => t('Taxonomy (all)'),
      ),
    );
    /* Display: Searchlight multivalue */
    foreach (taxonomy_get_vocabularies() as $vocab) {
      $relationships['term_node_tid']['vocabularies'] = array($vocab->machine_name => $vocab->machine_name);
      $fields['name']['label'] = $vocab->name;
      $handler = $view->new_display('searchlight_multivalue', $vocab->name, 'searchlight_multivalue_' . $vocab->machine_name);
      $handler->display->display_options['pager']['type'] = 'some';
      $handler->display->display_options['defaults']['relationships'] = FALSE;
      $handler->display->display_options['relationships'] = $relationships;
      $handler->display->display_options['defaults']['fields'] = FALSE;
      $handler->display->display_options['fields'] = $fields;
      $handler->display->display_options['searchlight_multivalue'] = array(
        'field' => 'taxonomy_index_tid',
        'label_field' => 'taxonomy_term_data_node_name',
        'override' => array(
          'name' => 'taxonomy_index_tid_' . $vocab->machine_name,
          'label' => $vocab->name,
        ),
      );
    }
    $views[$view->name] = $view;

    //
    // Taxonomy - Taxonomy =============================================================
    //
    $view = new view;
    $view->name = 'searchlight_term_data_taxonomy';
    $view->description = 'Multivalue fields for taxonomy terms';
    $view->tag = 'searchlight';
    $view->base_table = 'taxonomy_term_data';
    $view->human_name = 'searchlight_term_data_taxonomy';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['query']['options']['query_comment'] = FALSE;
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'some';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'default';
    $handler->display->display_options['row_plugin'] = 'fields';

    /* Field: Taxonomy term: Term ID */
    $handler->display->display_options['fields']['tid']['id'] = 'tid';
    $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
    $handler->display->display_options['fields']['tid']['field'] = 'tid';


    /* Display: Searchlight multivalue */
    foreach (taxonomy_get_vocabularies() as $vocabulary) {

      $field = 'field_' . $vocabulary->machine_name;

      // If no taxonomy is tagged with this one, do not add a display.
      $info = field_info_field($field);
      if (empty($info['bundles']['taxonomy_term'])) {
        continue;
      }

      $field_table = 'field_data_' . $field;
      $field_tid = $field . '_tid';


      /* Display: VOCABULARY */
      $handler = $view->new_display('searchlight_multivalue', $vocabulary->name, 'searchlight_multivalue_' . $vocabulary->machine_name);
      $handler->display->display_options['pager']['type'] = 'some';

      $handler->display->display_options['defaults']['relationships'] = FALSE;
      /* Relationship: Field: VOCABULARY (field_VOCABULARY_MACHINE_NAME) */
      $handler->display->display_options['relationships'][$field_tid]['id'] = $field_tid;
      $handler->display->display_options['relationships'][$field_tid]['table'] = $field_table;
      $handler->display->display_options['relationships'][$field_tid]['field'] = $field_tid;
      $handler->display->display_options['relationships'][$field_tid]['required'] = 1;

      $handler->display->display_options['defaults']['fields'] = FALSE;
      /* Field: Taxonomy term: Term ID */
      $handler->display->display_options['fields']['tid']['id'] = 'tid';
      $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
      $handler->display->display_options['fields']['tid']['field'] = 'tid';

      /* Field: Taxonomy term: Name */
      $handler->display->display_options['fields']['name']['id'] = 'name';
      $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
      $handler->display->display_options['fields']['name']['field'] = 'name';
      $handler->display->display_options['fields']['name']['relationship'] = $field_tid;
      $handler->display->display_options['fields']['name']['ui_name'] = $vocabulary->name;
      $handler->display->display_options['fields']['name']['label'] = $vocabulary->name;

      $handler->display->display_options['searchlight_multivalue'] = array(
        'field' => 'taxonomy_term_data_' . $field_table . '_tid',
        'label_field' => 'taxonomy_term_data_' . $field_table . '_name',
      );
    }
    $views[$view->name] = $view;
  }

  return $views;
}
