<?php

define('SEARCHLIGHT_SPHINX_FILTER_MAX', 100000000000);
define('SEARCHLIGHT_SPHINX_FILTER_MIN', 0);

/**
 * Provides integration with Sphinx.
 */
class SearchlightBackendSphinx extends SearchlightBackend {

  /**
   * Constructor.
   */
  function __construct($id) {
    parent::__construct($id);

    $this->lib_name = 'sphinx';
    $this->file_path = 'sphinxapi.php';

    // TODO: have a settings for this.
    // Assumes PHP has the same timezone with Sphinx server for now.
    $this->backend_timezone = ini_get('date.timezone');
  }

  /**
   * Override of getIndexes().
   */
  function getIndexes() {
    if (!empty($this->settings['delta_index']['enabled'])) {
      return array('main' => 'main', 'delta' => 'delta');
    }
    return array('main' => 'main');
  }

  /**
   * Override of settingsDefault().
   */
  function settingsDefault() {
    return array(
      // Indexing control.
      'main_index' => array(
        'cron' => TRUE,
        'ttl' => 0,
      ),
      // Live index updates.
      'delta_index' => array(
        'enabled' => FALSE,
        'ttl' => 0,
      ),
      // Searchd program configuration options.
      'searchd' => array(
        'port' => 9312,
      ),
      // Data source configuration options.
      'datasource' => array(
        'sql_sock' => '',
      ),
      // Index configuration options.
      'index' => array(
        'morphology' => 'stem_en',
        'charset_table' => NULL,
        'ngram_len' => NULL,
        'ngram_chars' => NULL,
      ),
      'indexer' => array(
        'mem_limit' => '32M',
        'max_iops' => 0,
        'max_iosize' => 0,
        'write_buffer' => '1M',
        'sql_range_step' => 2500,
        'sql_ranged_throttle' => 0,
      ),
    );
  }

  /**
   * Override of settingsForm().
   */
  function settingsForm() {
    $form = array();

    // Library.
    $form['library'] = $this->libraryStatusForm(l('Sphinx 0.9.9-release downloads', 'http://sphinxsearch.com/downloads/release/'));

    // Indexing control.
    $form['main_index'] = array(
      '#type' => 'fieldset',
      '#title' => t('Indexing control'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['main_index']['cron'] = array(
      '#title' => t('Index with cron'),
      '#description' => t('Use TTL to trigger indexing (can be used in addition to actions and triggers).'),
      '#type' => 'checkbox',
      '#default_value' => $this->settings['main_index']['cron'],
    );
    $form['main_index']['ttl'] = array(
      '#title' => t('Main index TTL'),
      '#description' => t('In seconds. Set to "0" to re-index on every run.'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['main_index']['ttl'],
      '#size' => 6,
    );

    // Live index updates.
    // @see http://sphinxsearch.com/docs/manual-0.9.9.html#live-updates
    $form['delta_index'] = array(
      '#type' => 'fieldset',
      '#title' => t('Live index updates'),
      '#collapsible' => TRUE,
      '#collapsed' => empty($this->settings['delta_index']['enabled']),
    );
    $form['delta_index']['enabled'] = array(
      '#title' => t('Enable live index updates'),
      '#description' => t('Use a combination of main and delta indices.'),
      '#type' => 'checkbox',
      '#default_value' => $this->settings['delta_index']['enabled'],
    );
    $form['delta_index']['ttl'] = array(
      '#title' => t('Delta index TTL'),
      '#description' => t('In seconds. Set to "0" to re-index on every run.'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['delta_index']['ttl'],
      '#size' => 6,
    );

    // Searchd program configuration options.
    // @see http://sphinxsearch.com/docs/manual-0.9.9.html#confgroup-searchd
    $form['searchd'] = array(
      '#type' => 'fieldset',
      '#title' => t('Searchd program configuration options'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['searchd']['port'] = array(
      '#title' => t('Searchd port'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['searchd']['port'],
      '#size' => 6,
    );

    // Data source configuration options.
    // @see http://sphinxsearch.com/docs/manual-0.9.9.html#confgroup-source
    $form['datasource'] = array(
      '#type' => 'fieldset',
      '#title' => t('Data source configuration options'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['datasource']['sql_sock'] = array(
      '#title' => t('DB sock'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['datasource']['sql_sock'],
      '#description' => t('The DB sock file to use. Example: <code>/var/lib/mysql/mysql.sock</code>. If left empty, Sphinx will try to autodetect its location.'),
      '#size' => 30,
    );

    // Index configuration options.
    // @see http://sphinxsearch.com/docs/manual-0.9.9.html#confgroup-index
    $form['index'] = array(
      '#type' => 'fieldset',
      '#title' => t('Index configuration options'),
      '#description' => t('Advanced configuration options for Sphinx. Use these options to enable CJK or other character set handling for Sphinx. Otherwise, you can leave these blank.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['index']['morphology'] = array(
      '#title' => t('Morphology'),
      '#description' => t('Morphology processors to apply. See !link', array(
        '!link' => l(t('Sphinx: morphology'), 'http://www.sphinxsearch.com/docs/current.html#conf-morphology'),
      )),
      '#type' => 'textfield',
      '#default_value' => $this->settings['index']['morphology'],
    );
    $form['index']['charset_table'] = array(
      '#title' => t('Character set table'),
      '#description' => t('Character set table. See !link and !charset for a variety of options', array(
        '!link' => l(t('Sphinx: charset_table'), 'http://www.sphinxsearch.com/docs/current.html#conf-charset-table'),
        '!charset' => l(t('Unicode character set tables'), 'http://sphinxsearch.com/wiki/doku.php?id=charset_tables'),
      )),
      '#type' => 'textarea',
      '#default_value' => $this->settings['index']['charset_table'],
    );
    $form['index']['ngram_len'] = array(
      '#title' => t('N-gram length'),
      '#description' => t('Set n-gram length to 1 for basic CJK support. See !link', array(
        '!link' => l(t('Sphinx: ngram_len'), 'http://www.sphinxsearch.com/docs/current.html#ngram_len'),
      )),
      '#type' => 'textfield',
      '#default_value' => $this->settings['index']['ngram_len'],
    );
    $form['index']['ngram_chars'] = array(
      '#title' => t('N-gram characters list'),
      '#description' => t('N-gram characters list for basic CJK support. See !link and !charset for CJK support', array(
        '!link' => l(t('Sphinx: ngram_chars'), 'http://www.sphinxsearch.com/docs/current.html#ngram_chars'),
        '!charset' => l(t('CJK n-gram characters'), 'http://sphinxsearch.com/wiki/doku.php?id=charset_tables#cjk_ngram_characters'),
      )),
      '#type' => 'textarea',
      '#default_value' => $this->settings['index']['ngram_chars'],
    );

    // Indexer program configuration options.
    // @see http://sphinxsearch.com/docs/manual-0.9.9.html#confgroup-indexer
    $form['indexer'] = array(
      '#type' => 'fieldset',
      '#title' => t('Indexer program configuration options'),
      '#description' => t('Advanced indexer configuration options for Sphinx.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['indexer']['mem_limit'] = array(
      '#title' => t('Indexer memory limit'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['indexer']['mem_limit'],
      '#description' => t('Enforced memory usage limit that the indexer will not go above. Can be specified in bytes, or kilobytes (using K postfix), or megabytes (using M postfix). Maximum possible limit is 2047M. Too low values can hurt indexing speed, but 256M to 1024M should be enough for most if not all datasets'),
      '#size' => 6,
    );
    $form['indexer']['max_iops'] = array(
      '#title' => t('Maximum I/O operations per second'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['indexer']['max_iops'],
      '#description' => t('It limits maximum count of I/O operations (reads or writes) per any given second. 0 for unlimited.'),
      '#size' => 6,
    );
    $form['indexer']['max_iosize'] = array(
      '#title' => t('Maximum allowed I/O operation size'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['indexer']['max_iosize'],
      '#description' => t('It limits maximum file I/O operation (read or write) size for all operations performed by indexer. In bytes. 0 for unlimited.'),
      '#size' => 6,
    );
    $form['indexer']['write_buffer'] = array(
      '#title' => t('Write buffer size'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['indexer']['write_buffer'],
      '#description' => t('Write buffers are used to write both temporary and final index files when indexing. Larger buffers reduce the number of required disk writes. Can be specified in bytes, or kilobytes (using K postfix), or megabytes (using M postfix).'),
      '#size' => 6,
    );
    $form['indexer']['sql_range_step'] = array(
      '#title' => t('SQL range step'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['indexer']['sql_range_step'],
      '#description' => t('Step for range queries.'),
      '#size' => 6,
    );
    $form['indexer']['sql_ranged_throttle'] = array(
      '#title' => t('SQL ranged throttle'),
      '#type' => 'textfield',
      '#default_value' => $this->settings['indexer']['sql_ranged_throttle'],
      '#description' => t('Delay between range queries.'),
      '#size' => 6,
    );
    return $form;
  }

  /**
   * Override of viewsOptionDefinition().
   */
  function viewsOptionDefinition(&$handler) {
    $this->sphinxIncludeClient();
    $options = parent::viewsOptionDefinition($handler);
    $options['matchMode'] = array('default' => SPH_MATCH_ALL);
    return $options;
  }

  /**
   * Override of viewsOptionsForm().
   */
  function viewsOptionsForm(&$form, &$form_state, &$handler) {
    $this->sphinxIncludeClient();
    parent::viewsOptionsForm($form, $form_state, $handler);
    $form['matchMode'] = array(
      '#title' => t('Search mode'),
      '#type' => 'select',
      '#options' => array(
        SPH_MATCH_ALL => t('Match all query words'),
        SPH_MATCH_ANY => t('Match any of the query words'),
        SPH_MATCH_PHRASE => t('Match the exact phrase'),
        SPH_MATCH_EXTENDED2 => t('Matches a Sphinx extended query'),
      ),
      '#default_value' => $handler->options['matchMode'],
    );
  }

  /**
   * Override of initClient().
   */
  function initClient($datasource) {
    $this->sphinxIncludeClient();
    $client = new SphinxClient();
    $client->SetServer('localhost', (int) $this->settings['searchd']['port']);
    return $client;
  }

  /**
   * Override of executeQuery().
   */
  function executeQuery(&$client, $datasource, $query = '') {
    $result = $client->Query($query, $this->sphinxGetIndex($datasource));
    if (!empty($result['matches'])) {
      return array('result' => array_keys($result['matches']), 'total' => $result['total'], 'raw' => $result);
    }
    return FALSE;
  }

  /**
   * Override of facetBuild().
   */
  function facetBuild(&$client, $datasource, $query = '', $facets) {
    $client = clone $client;
    $array_result = FALSE;
    foreach ($facets as $facet) {
      $field = $datasource->fields[$facet['field']];
      $limit = $facet['limit'];
      switch ($field['datatype']) {
        case 'timestamp':
          $groupby = array('day' => SPH_GROUPBY_DAY, 'month' => SPH_GROUPBY_MONTH, 'year' => SPH_GROUPBY_YEAR);
          $granularity = !empty($facet['granularity']) ? $facet['granularity'] : 'month';
          $client->SetGroupBy($field['name'], $groupby[$granularity], '@group desc');
          break;
        default:
          $client->SetGroupBy($field['name'], SPH_GROUPBY_ATTR, '@count desc');
          break;
      }

      // If there is a multivalue facet then set result as an array
      if ($array_result === FALSE) {
        $array_result = ($field['usage'] === 'multivalue');
      }

      // Set result limit.
      if (!empty($limit)) {
        $client->SetLimits(0, (int) $limit);
      }
      $client->AddQuery($query, $this->sphinxGetIndex($datasource));
    }

    $client->SetArrayResult($array_result);

    // Execute queries.
    $results = $client->RunQueries();

    // Build facet results.
    $built = array();
    foreach (array_values($facets) as $num => $facet) {
      if (!empty($results[$num]['matches'])) {
        $field = $datasource->fields[$facet['field']];
        foreach (array_keys($results[$num]['matches']) as $id) {
          $attr = $results[$num]['matches'][$id]['attrs'];
          if (isset($attr['@groupby'], $attr['@count'])) {
            switch ($field['datatype']) {
              case 'text':
                // If usage is attribute, retrieve the string corresponding to the filter value (crc32).
                if ($field['usage'] === 'attribute') {
                  $query = "SELECT DISTINCT {$field['field']} FROM {{$field['table']}}";
                  $field_values = db_query($query)->fetchCol();
                  foreach ($field_values as $field_value) {
                    if (crc32($field_value) == $attr['@groupby']) {
                      $id = $field_value;
                      break;
                    }
                  }
                }
                else {
                  $id = $this->sphinxGetOrdinal($datasource, $field['name'], $attr['@groupby']);
                }
                break;
              case 'timestamp':
                $id = $this->sphinxGetTimestamp($attr['@groupby'], !empty($facet['granularity']) ? $facet['granularity'] : 'month');
                break;
              default:
                $id = $attr['@groupby'];
                break;
            }
            $built[$facet['field']][$id] = array('id' => $id, 'count' => $attr['@count']);
          }
        }
      }
    }
    return $built;
  }

  /**
   * Override of prepareFilterValue().
   *
   * Return crc32 value for text filters (Sphinx 0.9.9)
   */
  function prepareFilterValue($filter_info, $value) {
    if (isset($filter_info['usage'], $filter_info['datatype']) && $filter_info['datatype'] === 'text' && $filter_info['usage'] === 'attribute') {
      if (is_array($value)) {
        foreach ($value as $k => $v) {
          $value[$k] = sprintf("%u", crc32($v));
        }
      }
      elseif (!empty($value)) {
        $value = array(crc32($value));
      }
    }
    return $value;
  }

  /**
   * Override of invalidateIndex().
   * Since Sphinx indexes can't be fully deleted from within Drupal, we mark
   * all items as deleted instead.
   */
  function invalidateIndex($datasource) {
    variable_del('searchlight_sphinx_last');

    // Update changed variable so that indexing will not be skipped.
    $changes = variable_get('searchlight_search_changes', array());
    unset($changes[$datasource->base_table]);
    variable_set('searchlight_search_changes', $changes);

    $delete = array();
    $result = db_select($datasource->base_table, 'b')
      ->fields('b', array($datasource->base_field))
      ->execute();
    foreach ($result as $row) {
      $delete[$row->{$datasource->base_field}] = array(1);
    }

    $client = $this->initClient($datasource);
    $client->UpdateAttributes($datasource->id . '_main', array('searchlight_deleted'), $delete);
    if (!empty($this->settings['delta_index']['enabled'])) {
      $client->UpdateAttributes($datasource->id . '_delta', array('searchlight_deleted'), $delete);
    }
  }

  /**
   * Override of index().
   */
  function index($jobs, &$context) {
    $indexes = array();
    foreach ($jobs as $job) {
      $datasource = searchlight_get_datasource($job['base_table']);
      if (!empty($datasource)) {
        // Get index ids. Note that order is important.
        foreach ($job['indexes'] as $key => $index) {
          $indexes[] = "{$datasource->id}_{$index}";
        }
      }
    }
    if (!empty($indexes)) {
      // Indexing command.
      $result = drush_op('drush_shell_exec', 'indexer --rotate --config ' . $this->drushGetConfigFile() . ' ' . implode(' ', $indexes));
      $context['results']['result'] = drush_shell_exec_output();
    }
  }

  /**
   * Override of setFilter().
   */
  function setFilter(&$client, $datasource, $search_filters) {
    $filters = array();

    // Hardwired delete filter. See sphinxDatasourceConf() for how this is
    // added to the sphinx index.
    $filters['searchlight_deleted'] = array(
      'field' => 'searchlight_deleted',
      'operator' => '=',
      'args' => array(0),
    );

    // OR groups, use computed select conditions
    if (!empty($search_filters['OR'])) {
      $or_conditions = array();
      foreach ($search_filters['OR'] as $group => $or_filters) {
        $conditions = array();
        foreach ($or_filters as $key => $params) {
          $field    = $params['field'];
          $operator = $params['operator'];
          $args     = (array)$params['args'];
          switch ($operator) {
            case 'IN':
              $conditions[] = "IN({$field}, " . implode(', ', $args) . ')';
              break;
            case 'NOT IN':
              $conditions[] = "NOT IN({$field}, " . implode(', ', $args) . ')';
              break;
            case 'BETWEEN':
              $conditions[] = "({$field} >= {$args[0]} AND {$field} < {$args[1]})";
              break;
            case 'NOT BETWEEN':
              $conditions[] = "({$field} < {$args[0]} OR {$field} >= {$args[1]})";
              break;
            case 'IS NULL':
              $conditions[] = "({$field} = 0)";
              break;
            case 'IS NOT NULL':
              $conditions[] = "({$field} <> 0)";
              break;
            case '>':
            case '>=':
            case '<':
            case '<=':
            case '=':
            case '<>':
              $conditions[] = "({$field} {$operator} {$args[0]})";
              break;
            case '!=':
              $conditions[] = "({$field} <> {$args[0]})";
              break;
          }
        }
        $or_conditions[] = '(' . implode(' OR ', $conditions) . ") AS condition{$group}";
        $filters["condition{$group}"] = array(
          'field' => "condition{$group}",
          'operator' => '=',
          'args' => array(1),
        );
      }
      $client->SetSelect('*, ' . implode(', ', $or_conditions));
    }

    // AND groups
    if (!empty($search_filters['AND'])) {
      foreach ($search_filters['AND'] as $group => $and_filters) {
        $filters = array_merge($filters, $and_filters);
      }
    }

    if (!empty($filters)) {
      // Iterate through once to separate out range filters.
      // Not there's no way to determine if matching docs should be excluded or included at that point.
      // BETWEEN or NOT BETWEEN should be used instead.
      $range_filters = array();
      foreach ($filters as $key => $params) {
        $field    = $params['field'];
        $operator = $params['operator'];
        $args     = $params['args'];
        if (in_array($operator, array('<', '>', '>=', '<='))) {
          unset($filters[$key]);
          switch ($operator) {
            case '>':
            case '>=':
              $range_filters[$field]['field'] = $field;
              $range_filters[$field]['max'] = isset($range_filters[$field]['max']) ? $range_filters[$field]['max'] : SEARCHLIGHT_SPHINX_FILTER_MAX;
              $range_filters[$field]['min'] = isset($range_filters[$field]['min']) ? max($range_filters[$field]['min'], $args[0]) : $args[0];
              break;
            case '<':
            case '<=':
              $range_filters[$field]['field'] = $field;
              $range_filters[$field]['max'] = isset($range_filters[$field]['max']) ? min($range_filters[$field]['max'], $args[0]) : $args[0];
              $range_filters[$field]['min'] = isset($range_filters[$field]['min']) ? $range_filters[$field]['min'] : SEARCHLIGHT_SPHINX_FILTER_MIN;
              break;
            default:
              break;
          }
        }
      }
      // Now set range filters. Make sure $min <= $max.
      foreach ($range_filters as $filter) {
        $client->SetFilterRange($filter['field'], min($filter['min'], $filter['max']), max($filter['min'], $filter['max']), FALSE);
      }
      // Equality & set filters filters.
      foreach ($filters as $params) {
        $field    = $params['field'];
        $operator = $params['operator'];
        $args     = (array)$params['args'];
        switch ($operator) {
          case '=':
            $this->sphinxSetFilter($client, $datasource, $field, $args, FALSE);
            break;
          case '!=':
          case '<>':
            $this->sphinxSetFilter($client, $datasource, $field, $args, TRUE);
            break;
          case 'IN':
            $this->sphinxSetFilter($client, $datasource, $field, $args, FALSE);
            break;
          case 'NOT IN':
            $this->sphinxSetFilter($client, $datasource, $field, $args, TRUE);
            break;
          case 'IS NULL':
            $this->sphinxSetFilter($client, $datasource, $field, array(0), FALSE);
            break;
          case 'IS NOT NULL':
            $this->sphinxSetFilter($client, $datasource, $field, array(0), TRUE);
            break;
          case 'BETWEEN':
            $client->SetFilterRange($field, $args[0], $args[1], FALSE);
            break;
          case 'NOT BETWEEN':
            $client->SetFilterRange($field, $args[0], $args[1], TRUE);
            break;
        }
      }
    }
  }

  /**
   * Override of setOptions().
   */
  function setOptions(&$client, $datasource, $options) {
    if (isset($options['matchMode'])) {
      $client->SetMatchMode($options['matchMode']);
    }
  }

  /**
   * Override of setSort().
   */
  function setSort(&$client, $datasource, $sorts) {
    if (!empty($sorts)) {
      $sphinx_sorts = array();
      foreach ($sorts as $sort) {
        if ($sort['field'] === 'searchlight_weight') {
          $sphinx_sorts[] = "@weight {$sort['direction']}";
        }
        else {
          $sphinx_sorts[] = "{$sort['field']} {$sort['direction']}";
        }
      }
      $client->setSortMode(SPH_SORT_EXTENDED, implode(', ', $sphinx_sorts));
    }
  }

  /**
   * Override of setPager().
   */
  function setPager(&$client, $offset, $limit) {
    $limit = !empty($limit) ? $limit : 2500;
    if (!empty($offset) || !empty($limit)) {
      $client->SetLimits((int) $offset, (int) $limit);
    }
  }

  /**
   * Override of setNodeAccess().
   * For Sphinx API usage of filter ORs, see:
   * - http://www.sphinxsearch.com/faq.html#filter-or
   * - http://www.sphinxsearch.com/forum/view.html?id=3440
   */
  function setNodeAccess(&$client, $grants) {
    if (!empty($grants)) {
      $grants_sql = array();
      foreach ($grants as $realm => $gids) {
        foreach ($gids as $gid) {
          $grants_sql[] = "IF(IN(node_access_gid_{$realm}, {$gid}), 1, 0)";
        }
      }
      if (count($grants_sql)) {
        $grants_sql = implode('+', $grants_sql);
        $client->SetSelect("*, ({$grants_sql}) AS sphinx_node_access");
        $client->SetFilterRange('sphinx_node_access', 1, 2500);
      }
    }
  }

  /**
    * Override of canOrderBy().
    */
  function canOrderBy($field_info) {
    $usage = $field_info['usage'];
    $datatype = $field_info['datatype'];
    return $usage !== 'content' && !($datatype === 'text' && $usage === 'attribute');
  }

  /**
   * Return a directory where the configuration files and indexes are stored.
   *
   * This can be overridden by specifying the '--sl-sphinx-conf-path' command line option to drush.
   */
  function drushGetConfigPath() {
    return drush_get_option('sl-sphinx-conf-path', dirname(drush_locate_root()) . '/sphinx');
  }

  /**
   * Return the file name of the generated configuration file.
   */
  function drushGetConfigFile() {
    return $this->drushGetConfigPath() . '/sphinx.merged.conf';
  }

  /**
   * Generate a merged configuration file.
   */
  function drushGenerateMergedConfig() {
    $conf_path = $this->drushGetConfigPath();
    $conf_file = $this->drushGetConfigFile();

    if (file_prepare_directory($conf_path, TRUE)) {
      $files = array();

      // rerieve list of possible configuration file matches.
      $files[] = $conf_path . '/sphinx.conf';

      $matches = drush_scan_directory($conf_path . '/index.d/', '/^.*\.conf$/', array('.', '..'), 0, false, 'name');

      foreach ($matches as $name => $file) {
        $files[] = $file->filename;
      }

      $string = '';
      if (sizeof($files)) {
        foreach ($files as $filename) {
          if (file_exists($filename) && is_readable($filename)) {
            // concatenate contents of valid configuration file.
            $string .= "\n" . file_get_contents($filename);
          }
        }
      }

      // load the previous file
      $old_config = (file_exists($conf_file)) ? file_get_contents($conf_file) : '';

      if ($old_config != $string) {
        file_put_contents($conf_file, $string);
        return drush_log(dt("Regenerated the Sphinx configuration file"), 'success');
      }
      else {
        drush_log(dt("Sphinx configuration file is up to date"), 'success');
      }
    }
    return false;
  }

  /**
   * Override of drushSearchd().
   */
  function drushSearchd($command = 'start') {
    $file_path = $this->drushGetConfigPath() . '/log';

    $lock_file = "{$file_path}/searchd.lock";
    if (file_prepare_directory($file_path, TRUE)) {
      $lock = file_exists($lock_file) ? file_get_contents($lock_file) : 0;

      if ((int) $lock == 1) {
        return drush_log('Search demon is already being restarted', 'error');
      }

      file_put_contents($lock_file, '1');
      if (file_prepare_directory($file_path, TRUE)) {
        $pid_file = "{$file_path}/searchd.pid";
        $pid = file_exists($pid_file) ? file_get_contents($pid_file) : '';

        if ((int) $pid) {
          // stop the daemon first
          if (drush_op_system('searchd --nodetach --stop -c ' . $this->drushGetConfigFile()) === 0) {
            drush_log('Search daemon stopped.', 'success');
          }
          else {
            drush_log('Search daemon was not stopped properly.', 'error');
          }
        }

        // We wait a bit to make sure daemon is completely stopped.
        // TODO: use --stopwait for sphinx > 1.10
        $timeout = 30;
        while (file_exists($pid_file) && ($timeout > 0)) {
          $timeout--;
          sleep(1);
        }

        if ($command != 'stop') {
          // start the daemon
          if (drush_op_system('searchd -c ' . $this->drushGetConfigFile()) === 0) {
            drush_log('Search daemon started.', 'success');
          }
          // something is wrong
          else {
            drush_log('Impossible to start search daemon.', 'error');
          }
        }
      }
      file_put_contents($lock_file, '0');
      return;
    }
  }

  /**
   * Override of drushIndex().
   */
  function drushIndex($force = TRUE) {
    // Create the sphinx directory if it doesn't exist.
    $file_path = $this->drushGetConfigPath() . '/indexes';
    if (!file_prepare_directory($file_path, TRUE)) {
      drush_log("Sphinx directory doesn't exist.", 'error');
    }

    // Regenerate the configuration file if needed.
    $config_changed = $this->drushGenerateMergedConfig();

    // If config has changed restart searchd.
    if ($config_changed === TRUE) {
      $this->drushSearchd();
    }

    // If forced or config has changed, we reindex everything.
    if ($force || $config_changed) {
      searchlight_index_all();
    }
    // If we use TTL, we add necessary jobs.
    elseif (!empty($this->settings['main_index']['cron'])) {
      drush_log("Searchlight - sphinx: using TTL.", 'ok');
      $indexed = variable_get('searchlight_indexed', array());
      $jobs = array();

      foreach (searchlight_get_datasource() as $datasource) {
        $base_table = $datasource->base_table;
        $indexes = $this->getIndexes();
        if (!$force && !$config_changed) {
          foreach ($indexes as $key => $index) {
            $ttl = $this->settings["{$index}_index"]['ttl'];
            // Make sure we also index delta if main is to be indexed.
            if ($index === 'delta' && isset($indexes['main'])) {
              continue;
            }
            if (isset($indexed[$base_table][$index]) && (($indexed[$base_table][$index] + $ttl) >= REQUEST_TIME)) {
              unset($indexes[$key]);
            }
          }
        }
        if (!empty($indexes)) {
          $jobs[] = array(
            'base_table' => $base_table,
            'indexes' => $indexes,
          );
        }
      }
      searchlight_queue_add($jobs);
    }

    // Proceed with pending jobs.
    $items = searchlight_queue_get();
    if (!empty($items)) {
      $jobs = array();
      foreach ($items as $item) {
        $jobs[] = $item->data;
      }
      searchlight_index($jobs);
    }
    // Nothing to index, we skip.
    else {
      return drush_log('No job to index. Skipping.', 'ok');
    }
  }

  /**
   * Override of drushConf().
   */
  function drushConf() {
    $file_path = $this->drushGetConfigPath();
    $conf_path = $file_path .'/index.d';

    // @TODO: Revisit configuration file generation. Need to handle:
    //
    // 1. If the datasource configuration has changed due to a site-driven
    //    event (eg. edit form), we can use the 'searchlight_config_changed'
    //    variable as a sign that files need rewriting.
    // 2. If the site has been migrated (eg. through Aegir) and the database
    //    name has changed, we need to rewrite config files. This case is NOT
    //    handled by the variable.
    // 3. If the site's code has changed and datasources are in the default
    //    state, we need to rewrite config files. This case is NOT handled by
    //    the variable.
    //
    // if (!variable_get('searchlight_config_changed', TRUE) && file_check_directory($conf_path, TRUE)) {
    //   return drush_log('Sphinx configuration not changed', 'success');
    // }
    // else {
    //   variable_set('searchlight_config_changed', FALSE);
    // }

    if (file_prepare_directory($file_path, TRUE) && drush_get_option('sl-sphinx-base-conf', TRUE)) {
      $this->drushBaseConf();
    }

    if (file_prepare_directory($conf_path, TRUE)) {
      // Collect configuration arrays for each datasource.
      foreach (searchlight_datasource_load(NULL, TRUE) as $datasource) {
        $source = $this->sphinxDatasourceConf($datasource);
        $conf_file = "{$conf_path}/{$datasource->id}.conf";

        // Generate configuration file from datasource.
        $sphinx_conf = theme('searchlight_sphinx_index_conf', array('datasource' => $source));
        $existing = file_exists($conf_file) ? file_get_contents($conf_file) : '';
        if ($sphinx_conf === $existing) {
          drush_log("{$conf_file} is unchanged.", 'success');
        }
        else {
          file_put_contents($conf_file, $sphinx_conf);
          drush_log("{$conf_file} was written successfully.", 'success');
        }
      }
      return drush_log("Sphinx configuration files were written", 'success');
    }
    return drush_log("Sphinx configuration files could not be written.", 'error');
  }

  /**
   * Generate the base configuration for all sphinx instances.
   */
  function drushBaseConf() {
    $file_path = $this->drushGetConfigPath();
    $conf_file = "{$file_path}/sphinx.conf";
    if (file_prepare_directory($file_path, TRUE)) {
      $sphinx_conf = theme('searchlight_sphinx_conf', array('searchd' => $this->sphinxSearchdConf()));
      if ($sphinx_conf) {
        $existing = file_exists($conf_file) ? file_get_contents($conf_file) : '';
        if ($sphinx_conf === $existing) {
          return drush_log("{$conf_file} is unchanged.", 'success');
        }
        else {
          file_put_contents($conf_file, $sphinx_conf);
          return drush_log("{$conf_file} was written successfully.", 'success');
        }
      }
    }
  }

  /**
   * Execute functionality on drush cron run.
   */
  function drushCron() {
    $this->drushConf();
    $this->drushIndex(FALSE);
  }


  /**
   * When a new site is installed via Aegir.
   */
  function drushAegirInstall() {
    $conf_path = drush_set_option('sl-sphinx-conf-path', drush_get_option('config_path', '/var/aegir') . '/sphinx', 'site');

    $datasources = searchlight_datasource_load(NULL, TRUE);
    $this->drushConf();
    $this->drushIndex();

    // Drush backend invoke is not usable before drushrc.php is written.
    // drush_backend_invoke('searchlight-conf', array('sl-sphinx-conf-path' => $conf_path));
    // drush_backend_invoke('searchlight-index', array('sl-sphinx-conf-path' => $conf_path));
  }

  /**
   * When a site is migrated via Aegir.
   */
  function drushAegirDeploy() {
    $this->drushAegirInstall();
  }

  /**
   * Methods specific to the Sphinx backend ===================================
   */

  /**
   * Wrapper of $client->SetFilter().
   * Convert any string values to ordinals before passing through.
   */
  function sphinxSetFilter(&$client, $datasource, $attribute, $values, $exclude = FALSE) {
    $ordinals = array();
    foreach ((array) $values as $arg) {
      $arg = trim($arg);
      if (is_numeric($arg)) {
        $ordinals[] = $arg;
      }
      else {
        $ordinal = $this->sphinxGetOrdinal($datasource, $attribute, $arg);
        if (is_numeric($ordinal)) {
          $ordinals[] = $ordinal;
        }
      }
    }
    return !empty($ordinals) ? $client->SetFilter($attribute, $ordinals, $exclude) : FALSE;
  }

  /**
   * Generate an array representing the conf and index settings for a datasource.
   */
  function sphinxDatasourceConf($datasource) {
    $conf = array(
      'id' => $datasource->id . '_main',
      'conf' => array(),
      'query' => array(),
      'index' => array(),
      'delta' => array(
        'conf' => array(),
        'query' => array(),
        'index' => array(),
      ),
    );

    // Use mysql stored database credentials.
    if ($creds = drush_get_context('DRUSH_DB_CREDENTIALS')) {
      $conf['conf']['type'] = $creds['driver'] === 'mysqli' ? 'mysql' : $creds['driver'];
      $conf['conf']['sql_user'] = $creds['user'];
      $conf['conf']['sql_pass'] = $creds['pass'];
      $conf['conf']['sql_host'] = $creds['host'];
      $conf['conf']['sql_db']   = $creds['name'];
      $conf['conf']['sql_port'] = isset($creds['port']) ? $creds['port'] : '3306';
    }
    // Check for optional sql_sock option.
    $sock = trim($this->settings['datasource']['sql_sock']);
    if (!empty($sock)) {
      $conf['conf']['sql_sock'] = $sock;
    }

    // Index configuration options.
    $conf['index']['path'] = $this->drushGetConfigPath() . '/indexes/' . $conf['id'];
    $conf['index']['docinfo'] = 'extern';
    $conf['index']['mlock'] = 0;

    // Morphology settings.
    if (!empty($this->settings['index']['morphology'])) {
      $conf['index']['morphology'] = $this->settings['index']['morphology'];
    }
    // Charactsets, CJK handling, etc.
    if (!empty($this->settings['index']['charset_table'])) {
      $conf['index']['charset_table'] = $this->settings['index']['charset_table'];
    }
    if (!empty($this->settings['index']['ngram_len'])) {
      $conf['index']['ngram_len'] = $this->settings['index']['ngram_len'];
    }
    if (!empty($this->settings['index']['ngram_chars'])) {
      $conf['index']['ngram_chars'] = $this->settings['index']['ngram_chars'];
    }

    // Assume UTF-8, character stripping for now.
    $conf['index']['charset_type'] = 'utf-8';
    $conf['index']['html_strip'] = 0;

    // Delta index configuration options.
    $delta_index_enabled = !empty($this->settings['delta_index']['enabled']);
    if ($delta_index_enabled) {
      $conf['delta']['id'] = $datasource->id . '_delta';
      $conf['delta']['index']['path'] = $this->drushGetConfigPath() . '/indexes/' . $conf['delta']['id'];
    }

    // Build the query.
    $indent = '  ';
    $datasource->init();
    $datasource->view->build();
    if ($view = $datasource->view) {
      // Force utf8 when indexing.
      $conf['query'][] = "sql_query_pre = SET NAMES utf8";

      $sql_query = clone $view->query;
      $sql_query->add_field(NULL, '0', 'searchlight_deleted');

      // Assume serial ids on the base table and step by 1000.
      $sql_query_range = "SELECT MIN({$view->base_field}), MAX({$view->base_field}) FROM {$view->base_table} WHERE {$view->base_field} > 0";
      $sql_range_step = isset($this->settings['indexer']['sql_range_step']) ? $this->settings['indexer']['sql_range_step'] : 2500;
      $sql_ranged_throttle = isset($this->settings['indexer']['sql_ranged_throttle']) ? $this->settings['indexer']['sql_ranged_throttle'] : 0;
      if ($delta_index_enabled) {
        $sql_query_range_delta = "SELECT IFNULL(MIN(id), 1), IFNULL(MAX(id), 1) FROM searchlight_search WHERE type = '{$view->base_table}' AND status <> -1 AND id > 0";
      }

      // Merge in attributes.
      $sql_attr = array();
      $sql_attr_delta = array();
      $sphinx_type = array(
        'text' => 'sql_attr_str2ordinal',
        'int' => 'sql_attr_uint',
        'float' => 'sql_attr_float',
        'timestamp' => 'sql_attr_timestamp',
      );

      // Hardwired delete flag.
      $sql_attr[] = "{$sphinx_type['int']} = searchlight_deleted";

      // Generate attribute entries.
      $fields = $datasource->fields;
      $fields = array_merge($fields, $datasource->buildNodeaccess());
      foreach ($fields as $field) {
        if ($field['datatype'] === 'text' && $field['usage'] === 'attribute') {
          // Unfortunately in case of main + delta scheme, we can not use text attributes
          // as ordinal values will defer.
          // See http://sphinxsearch.com/docs/manual-0.9.9.html#conf-sql-attr-str2ordinal
          // Should be replaced with sql_field_string for sphinx > 1.10-beta
          // Workaround is to store CRC32 value thus filtering and grouping are possible,
          // sorting though doesn't make sense with this method.
          $field_alias = $field['name'];
          if (isset($sql_query->fields[$field_alias])) {
            $query_field = $sql_query->fields[$field_alias];
            if ($query_field['field'] === $field['field'] && $query_field['table'] === $field['table']) {
              if (isset($sql_query->table_queue[$query_field['table']]['alias'])) {
                $table_alias = $sql_query->table_queue[$query_field['table']]['alias'];
                $sql_query->fields[$field_alias]['field'] = "CRC32({$table_alias}.{$field['field']})";
                $sql_query->fields[$field_alias]['table'] = '';
                $sql_attr[] = "sql_attr_uint = {$field_alias}";
              }
            }
          }
        }
        elseif ($field['usage'] === 'attribute' && isset($sphinx_type[$field['datatype']])) {
          $sql_attr[] = "{$sphinx_type[$field['datatype']]} = {$field['name']}";
        }
        // Generate multivalue queries.
        elseif ($field['usage'] === 'multivalue' && $mva_view = searchlight_build_view($field['view'])) {
          $query = &$mva_view->query;
          // Remove any fields that are not the id field or attribute field.
          foreach ($query->fields as $alias => $query_field) {
            if ($query_field['field'] === $mva_view->base_field && $query_field['table'] === $mva_view->base_table) {
              continue;
            }
            if ($query_field['field'] === $field['field'] && $query_field['table'] === $field['table_alias']) {
              continue;
            }
            unset($query->fields[$alias]);
          }

          if ($delta_index_enabled) {
            $query_delta = clone $query;
            $query_delta->add_where(0, "({$view->base_table}.{$view->base_field} IN (SELECT id FROM searchlight_search WHERE type = '{$view->base_table}' AND status <> -1  AND id BETWEEN " . '$start AND $end))' , array(), 'formula');
            $mva_query_delta = $this->sphinxWriteSQL($query_delta, $indent . $indent);
            $sql_attr_delta[] = "sql_attr_multi = uint {$field['name']} from ranged-query; \\\n{$indent}{$mva_query_delta}; \\\n{$indent}{$sql_query_range_delta}";
          }

          $query->add_where(0, "{$view->base_table}.{$view->base_field}" .  ' BETWEEN $start AND $end ', array(), 'formula');
          $mva_query = $this->sphinxWriteSQL($query, $indent . $indent);
          $sql_attr[] = "sql_attr_multi = uint {$field['name']} from ranged-query; \\\n{$indent}{$mva_query}; \\\n{$indent}{$sql_query_range}";

          // TODO: check build_info.
          $mva_view->destroy();
        }
      }

      if ($delta_index_enabled) {
        $sql_query_delta = clone $sql_query;
        $sql_query_delta->add_where(0, "({$view->base_table}.{$view->base_field} IN (SELECT id FROM searchlight_search WHERE type = '{$view->base_table}' AND status <> -1 AND id BETWEEN " . '$start AND $end))' , array(), 'formula');

        $conf['delta']['query'][] = "sql_query = \\\n" . $indent . $this->sphinxWriteSQL($sql_query_delta, $indent . $indent);
        $conf['delta']['query'][] = 'sql_query_range = ' . $sql_query_range_delta;

        $sql_attr_delta = array_unique($sql_attr_delta);
        $conf['delta']['query'][] = implode(" \n", $sql_attr_delta);

        // TODO: Empty post index query?
        $conf['delta']['query'][] = 'sql_query_post_index = ';

        // Kill-list query to avoid results from main index for deleted and updated docs.
        $conf['delta']['query'][] = "sql_query_killlist = SELECT id FROM searchlight_search WHERE type = '{$view->base_table}'";
      }

      $sql_query->add_where(0, "{$view->base_table}.{$view->base_field}" .  ' BETWEEN $start AND $end ', array(), 'formula');

      $conf['query'][] = "sql_query = \\\n" . $indent . $this->sphinxWriteSQL($sql_query, $indent . $indent);
      $conf['query'][] = 'sql_query_range = ' . $sql_query_range;
      $conf['query'][] = 'sql_range_step = ' . $sql_range_step;
      $conf['query'][] = 'sql_ranged_throttle = ' . $sql_ranged_throttle;

      $sql_attr = array_unique($sql_attr);
      $conf['query'][] = implode(" \n", $sql_attr);

      // Post index query to clean deleted and updated docs.
      $conf['query'][] = "sql_query_post_index = DELETE FROM searchlight_search WHERE type = '{$view->base_table}'";
    }

    return $conf;
  }

  /**
   * Get the Sphinx searchd settings.
   */
  function sphinxSearchdConf() {
    $searchd = array();
    $searchd['mem_limit'] = $this->settings['indexer']['mem_limit'];
    $searchd['max_iops'] = $this->settings['indexer']['max_iops'];
    $searchd['max_iosize'] = $this->settings['indexer']['max_iosize'];
    $searchd['write_buffer'] = $this->settings['indexer']['write_buffer'];
    $searchd['log'] = $this->drushGetConfigPath() . '/log/searchd.log';
    $searchd['query_log'] = $this->drushGetConfigPath() . '/log/query.log';
    $searchd['pid_file'] = $this->drushGetConfigPath() . '/log/searchd.pid';
    return $searchd;
  }

  /**
   * Include the Sphinx PHP API library.
   */
  function sphinxIncludeClient() {
    if ($this->includeLibrary()) {
      return;
    }

    // TODO: remove in 2.x.
    module_load_include('php', 'searchlight', 'libraries/sphinxapi');
  }

  /**
   * Write a SQL query with fully prefixed tables and replaced arguments.
   */
  function sphinxWriteSQL($views_query, $indent = '  ') {
    $query = $views_query->query();
    return searchlight_dump_query($query, $indent);
  }

  /**
   * Get the ordinal integer for a given string, or vice versa.
   */
  function sphinxGetOrdinal($datasource, $attribute_name, $value, $reset = FALSE) {
    $datasource_id = $datasource->id;

    if (!isset($this->ordinals[$datasource_id]) || $reset) {
      $cid = "searchlight_sphinx_ordinals_{$datasource_id}";
      if (!$reset && $cache = cache_get($cid)) {
        $this->ordinals[$datasource_id] = $cache->data;
      }
      if ($reset || !isset($this->ordinals[$datasource_id])) {
        $mapping = $this->sphinxGetOrdinals($datasource);
        if (!empty($mapping)) {
          cache_set($cid, $mapping);
        }
        $this->ordinals[$datasource_id] = $mapping;
      }
    }
    if (is_numeric($value)) {
      return isset($this->ordinals[$datasource_id][$attribute_name]) ? array_search($value, $this->ordinals[$datasource_id][$attribute_name]) : FALSE;
    }
    else {
      return isset($this->ordinals[$datasource_id][$attribute_name][$value]) ? $this->ordinals[$datasource_id][$attribute_name][$value] : FALSE;
    }
  }

  /**
   * Get an ordinal mapping for this datasource.
   * As this is a very expensive operation, its results are cached and
   * used in the ->sphinxGetOrdinal() method. You should only call this method
   * if you know what you are doing.
   */
  function sphinxGetOrdinals($datasource) {
    $datasource->init();

    // Retrieve all ordinal attributes.
    $attributes = array();
    if (!empty($datasource->fields)) {
      foreach ($datasource->fields as $name => $field) {
        if ($field['datatype'] === 'text' && $field['usage'] === 'attribute') {
          $attributes[$name] = $field;
        }
      }
    }

    // If there are attributes with ordinals, generate a mapping.
    // We only handle string ordinals for sets of less than 1000 (for now).
    $ordinals = array();
    if (!empty($attributes)) {
      $this->sphinxIncludeClient();
      $sphinx = new SphinxClient();
      $sphinx->SetLimits(0, 2500);

      foreach ($attributes as $name => $field) {
        // Dispatch a Sphinx query to retrieve the ordinal.
        $sphinx->SetGroupBy($name, SPH_GROUPBY_ATTR, '@count desc');
        $sphinx->SetGroupDistinct($name);
        $result = $sphinx->Query(NULL, $this->sphinxGetIndex($datasource));

        if (!empty($result['matches']) && count($result['matches']) < 2500) {
          // Dispatch a Views query to retrieve the corresponding string.
          $ids = array_keys($result['matches']);
          $view = $datasource->view->copy();
          $view->build();
          $view->set_items_per_page(0);
          $view->query->where = array();
          $view->query->add_where(0, "{$view->base_table}.{$view->base_field}", $ids, 'IN');
          $view->build_info['query'] = $view->query->query();
          $view->execute();
          foreach ($view->result as $row) {
            $id = $row->{$view->base_field};
            if (isset($result['matches'][$id], $row->{$name})) {
              $ordinals[$name][$row->{$name}] = $result['matches'][$id]['attrs'][$name];
            }
          }
        }
      }
    }
    return $ordinals;
  }

  /**
   * Convert a Sphinx datestring into a timestamp. Requires a datestring
   * (e.g. 201010) and a target granularity: day, month, year. We reverse-apply
   * Drupal's timezone offset so that this date can be used with format_date(),
   * etc. cleanly.
   */
  function sphinxGetTimestamp($datestring, $granularity) {
    // Use backend timestamp as the internal id.
    if (isset($this->backend_timezone)) {
      $timezone = date_default_timezone_get();
      date_default_timezone_set($this->backend_timezone);
    }

    switch ($granularity) {
      case 'day':
        $timestamp = mktime(0, 0, 0, substr($datestring, 4, 2), substr($datestring, 6, 2), substr($datestring, 0, 4));
        break;
      case 'month':
        $timestamp = mktime(0, 0, 0, substr($datestring, 4, 2), 1, substr($datestring, 0, 4));
        break;
      case 'year':
        $timestamp = mktime(0, 0, 0, 1, 1, $datestring);
        break;
    }

    // Set back the user time zone.
    if (isset($timezone)) {
      date_default_timezone_set($timezone);
    }

    return $timestamp;
  }

  /**
   * Return the index to query.
   */
  function sphinxGetIndex($datasource) {
    return !empty($this->settings['delta_index']['enabled']) ? "{$datasource->id}_main {$datasource->id}_delta" : $datasource->id . '_main';
  }

}
