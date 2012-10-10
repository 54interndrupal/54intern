<?php

class SearchlightDatasource {
  var $id;
  var $name;
  var $base_table;
  var $base_field;
  var $fields;
  var $filters;
  var $options;

  var $view;

  function construct() {
    $this->name = isset($this->name) ? $this->name : '';
    $this->base_table = isset($this->base_table) ? $this->base_table : '';

    $this->base_field = '';
    if ($views_data = views_fetch_data($this->base_table)) {
      $this->base_field = $views_data['table']['base']['field'];
    }

    $this->fields = !empty($this->fields) ? $this->fields : array();
    $this->filters = !empty($this->filters) ? $this->filters : array();
    $this->options = !empty($this->options) ? $this->options : array();
    $this->options = $this->options + array(
      'node_access' => TRUE,
    );

    $this->setId();
  }

  function setId() {
    global $databases;
    $this->id = $databases['default']['default']['database'] . '_' . $this->name;
    return $this;
  }

  function init() {
    return empty($this->view) ? $this->viewInit()->viewSetHandlers() : $this;
  }

  function viewInit() {
    views_include('view');
    $this->view = new view;
    $this->view->name = 'searchlight_datasource'; // TODO
    $this->view->base_table = $this->base_table;
    $this->view->base_field = $this->base_field;
    $this->view->core = 7;
    $this->view->api_version = '3.0';
    $this->view->new_display('default', 'Master', 'default');
    $this->view->set_display('default');
    return $this;
  }

  function viewSetHandlers() {
    // Fields.
    $fields = array();
    if ($this->base_field) {
      $fields[$this->base_field] = array(
        'id' => $this->base_field,
        'table' => $this->base_table,
        'field' => $this->base_field,
        //'relationship' => 'none',
      );
    }
    foreach ($this->getFields() as $name => $field) {
      $data = views_fetch_data($field['table']);
      if (isset($data[$field['field']]['field'])) {
        $fields[$name] = array(
          'id' => $field['name'],
          'table' => $field['table'],
          'field' => $field['field'],
          //'relationship' => 'none',
        );
      }
    }

    // Handler.
    $handler = &$this->view->display_handler;
    $handler->override_option('pager', array('type' => 'none', 'options' => array('offset' => 0)));
    $handler->override_option('arguments', array());
    $handler->override_option('filters', array());
    $handler->override_option('relationships', array());
    $handler->override_option('sorts', array());
    $handler->override_option('fields', $fields);
    return $this;
  }

  /**
   * Given a Views handler return one of the datasource datatypes based on the
   * database column type and other metadata. May be one of the following
   * datasource attribute types:
   *
   *   `text`:      varchar or text column.
   *   `int`:       serial or int column.
   *   `float`:     float column.
   *   `timestamp`: unix timestamp.
   */
  function getDatatype($handler = NULL, $table, $field) {
    $attribute = array();

    // Ensure that pseudo table names are traced back to their literal tables
    // that actually have a schema definition.
    $data = views_fetch_data();
    if (isset($data[$table]['table']['join'])) {
      foreach ($data[$table]['table']['join'] as $join_info) {
        if (isset($join_info['table']) && $join_info['table'] !== $table) {
          $table = $join_info['table'];
          break;
        }
      }
    }

    $schema = drupal_get_schema($table);
    if ($schema && isset($field, $schema['fields'][$field])) {
      $class = $handler ? get_class($handler) : NULL;
      // Get the datasource attribute type.
      // We use the handler class for special cases like timestamp where DB
      // column type is not enough information to determine the usage of the
      // field.
      $map = array(
        'serial' => 'int',
        'int' => 'int',
        'varchar' => 'text',
        'text' => 'text',
        'float' => 'float',
      );

      if (isset($map[$schema['fields'][$field]['type']])) {
        $column_type = $map[$schema['fields'][$field]['type']];
        // Conditions under which we should consider this field a "timestamp".
        if (
          ($column_type === 'int' && strpos($class, 'date') !== FALSE) ||
          (isset($handler->field_info['type']) && $handler->field_info['type'] === 'datestamp')
        ) {
          return 'timestamp';
        }
        return isset($map[$column_type]) ? $map[$column_type] : FALSE;
      }
    }
    // Handle a list of known function/calculation fields.
    $map = array(
      'node_comment_statistics.last_updated' => 'timestamp',
    );
    return isset($map["{$table}.{$field}"]) ? $map["{$table}.{$field}"] : FALSE;
  }

  /**
   * Given a datatype, return a default usage.
   */
  function getDefaultUsage($datatype) {
    if (empty($datatype)) {
      // TODO
      return '';
    }
    elseif ($datatype === 'text') {
      return 'content';
    }
    else {
      return 'attribute';
    }
  }

  /**
   * Retrieve fields currently enabled for this datasource.
   */
  function getFields() {
    $fields = array();
    foreach ($this->fields as $name => $field) {
      if ($field['usage'] !== 'multivalue') {
        $fields[$name] = $field;
      }
    }
    return $fields;
  }

  /**
   * Retrieve multivalue fields currently enabled for this datasource.
   */
  function getMultivalues() {
    $fields = array();
    foreach ($this->fields as $name => $field) {
      if ($field['usage'] === 'multivalue') {
        $fields[$name] = $field;
      }
    }
    return $fields;
  }

  /**
   * Retrieve all possible multivalue fields for this base table.
   */
  function buildMultivalues() {
    views_invalidate_cache();
    $multivalues = array();

    // Gather all views that have the multivalue display plugin.
    $views = views_get_all_views();
    $usable = array();
    foreach ($views as $view) {
      if ($view->base_table === $this->base_table) {
        foreach ($view->display as $display) {
          if ($display->display_plugin === 'searchlight_multivalue') {
            $usable[$view->name] = $view;
          }
        }
      }
    }
    foreach ($usable as $view) {
      if ($view->name !== 'searchlight_node_access') {
        foreach ($view->display as $display) {
          if ($display->display_plugin === 'searchlight_multivalue') {
            $view = views_get_view($view->name);
            // XXX.
            // $view->set_display($display->id);
            $multivalue = $view->execute_display($display->id);
            $multivalues[$multivalue['name']] = $multivalue;
            $view->destroy();
          }
        }
      }
    }
    return $multivalues;
  }

  /**
   * Build and retrieve node_access multivalue information.
   */
  function buildNodeaccess() {
    views_invalidate_cache();
    $nodeaccess = array();
    if ($this->options['node_access'] && $this->base_table === 'node' && $view = views_get_view('searchlight_node_access')) {
      foreach ($view->display as $display) {
        if ($display->display_plugin === 'searchlight_multivalue') {
          $view = views_get_view($view->name);
          // XXX.
          // $view->set_display($display->id);
          $multivalue = $view->execute_display($display->id);
          $nodeaccess[$multivalue['name']] = $multivalue;
          $view->destroy();
        }
      }
    }
    return $nodeaccess;
  }

  /**
   * Provide the default form for setting options.
   */
  function optionsForm(&$form, &$form_state) {
    views_include('admin');
    views_include('form');

    // Theme function will handle formatting of datasource information.
    $form['#theme'] = 'searchlight_admin_datasource';
    $form['#datasource'] = $this;

    // Calculations of indexing percentage.
    $result = db_query("SELECT count(id) AS count, status FROM {searchlight_search} WHERE type = :type GROUP BY status", array(':type' => $this->base_table));
    $items_indexed = 0;
    $items_total = 0;
    foreach ($result as $row) {
      $items_indexed = $row->status == 1 ? $row->count : $items_indexed;
      $items_total = $items_total + $row->count;
    }
    $form['index']['#tree'] = TRUE;
    $form['index']['percent'] = array(
      '#markup' => !empty($items_total) ? number_format(($items_indexed / $items_total * 100), 1) . '%' : '0%',
    );
    $form['index']['counts'] = array(
      '#markup' => t('@indexed of @total total', array(
        '@indexed' => $items_indexed,
        '@total' => $items_total,
      )),
    );
    $form['index']['invalidate'] = array(
      '#type' => 'submit',
      '#value' => t('Queue for reindexing'),
    );

    $form['help'] = array(
      '#type' => 'item',
      '#markup' => t('Choose a usage type for each field in the search datasource. <strong>Content</strong> fields will be used to perform text searches. <strong>Attributes</strong> can be used to filter, sort or group the search results.' . "<br/><br/>" .
                    '<strong>Sphinx < 1.10-beta</strong>: <strong>Attributes</strong> of type <em>text</em> can only be used to filter or group search results. Sorting is not possible.'),
    );

    $form['fields'] = array(
      '#prefix' => "<div id='datasource-fields'>",
      '#suffix' => "</div>",
      '#tree' => TRUE,
      '#theme' => 'searchlight_admin_datasource_fields',
      '#title' => t('Fields'),
    );

    // Add fields
    $field_options = array();
    // TODO: remove unnecessary fields.
    // TODO: why do we require grouping.
    $fields = views_fetch_fields($this->base_table, 'field', TRUE);
    foreach ($fields as $field_id => $info) {
      $field_options[$info['group']][$field_id] = $info['title'];
    }
    // TODO: relationships - only users for now.
    $relationships = views_fetch_fields($this->base_table, 'relationship');
    foreach ($relationships as $rel_id => $relationship) {
      // TODO
    }
    $form['fields']['new']['#tree'] = TRUE;
    $form['fields']['new']['field'] = array(
      '#type' => 'select',
      '#options' => $field_options,
    );
    $form['fields']['new']['add'] = array(
      '#value' => t('Add field'),
      '#type' => 'submit',
      '#submit' => array('searchlight_admin_datasource_edit_submit'),
      '#limit_validation_errors' => array(array('fields', 'new')),
      // @TODO: Determine why AJAX is failing. Possibly because the element to
      // which the ajax behavior is attached is replaced by the ajax callback.
      // '#ajax' => array(
      //   'callback' => 'searchlight_admin_datasource_ajax_fields_add',
      //   'wrapper' => 'datasource-fields',
      //   'method' => 'replace',
      // ),
    );

    // Remove fields
    if (count($this->getFields())) {
      $form['fields']['remove'] = array(
        '#value' => t('Remove selected fields'),
        '#type' => 'submit',
        '#submit' => array('searchlight_admin_datasource_edit_submit'),
        '#limit_validation_errors' => array(array('fields', 'fields')),
        // '#ajax' => array(
        //   'callback' => 'searchlight_admin_datasource_ajax_fields_remove',
        //   'wrapper' => 'datasource-fields',
        //   'method' => 'replace',
        // ),
      );
    }
    // Adjust existing fields
    $form['fields']['fields'] = array('#tree' => TRUE);
    foreach ($this->getFields() as $name => $info) {
      $form['fields']['fields'][$name] = array();

      // Remove field checkbox.
      $form['fields']['fields'][$name]['remove'] = array(
        '#type' => 'checkbox',
        '#default_value' => FALSE,
      );

      // Field label.
      $form['fields']['fields'][$name]['label'] = array(
        '#markup' => $info['label'],
      );

      // Datatype
      $form['fields']['fields'][$name]['datatype'] = array(
        '#markup' => "<code>{$info['datatype']}</code>",
      );

      // Usage
      if (!empty($this->fields[$name]['usage'])) {
        $form['fields']['fields'][$name]['usage'] = array(
          '#type' => 'select',
          '#options' => array(
            'content' => t('Content'),
            'attribute' => t('Attribute'),
          ),
          '#default_value' => $this->fields[$name]['usage'],
        );
      }
      else {
        $form['fields']['fields'][$name]['usage'] = array(
          '#type' => 'markup',
          '#markup' => t('Meta field'),
        );
      }
    }

    // @TODO: Handle multivalues.
    $form['multivalues'] = array(
      '#tree' => TRUE,
      '#theme' => 'searchlight_admin_datasource_fields',
      '#title' => t('Multivalues'),
      '#prefix' => "<div id='datasource-multivalues'>",
      '#suffix' => "</div>",
    );

    // Add fields
    $multivalue_options = array();
    foreach ($this->buildMultivalues() as $name => $info) {
      if (!array_key_exists($name, $this->getMultivalues())) {
        $multivalue_options[$name] = $info['label'];
      }
    }
    $form['multivalues']['new']['#tree'] = TRUE;
    $form['multivalues']['new']['field'] = array(
      '#type' => 'select',
      '#options' => $multivalue_options,
    );
    $form['multivalues']['new']['add'] = array(
      '#value' => t('Add multivalue'),
      '#type' => 'submit',
      '#submit' => array('searchlight_admin_datasource_edit_submit'),
      '#limit_validation_errors' => array(array('multivalues', 'new')),
      // '#ajax' => array(
      //   'callback' => 'searchlight_admin_datasource_ajax_multivalues_add',
      //   'wrapper' => 'datasource-multivalues',
      //   'method' => 'replace',
      // ),
    );

    // Remove fields
    if (count($this->getMultivalues())) {
      $form['multivalues']['remove'] = array(
        '#value' => t('Remove selected multivalues'),
        '#type' => 'submit',
        '#submit' => array('searchlight_admin_datasource_edit_submit'),
        '#limit_validation_errors' => array(array('multivalues', 'fields')),
        // '#ajax' => array(
        //   'callback' => 'searchlight_admin_datasource_ajax_multivalues_remove',
        //   'wrapper' => 'datasource-multivalues',
        //   'method' => 'replace',
        // ),
      );
    }
    $form['multivalues']['fields'] = array();
    foreach ($this->getMultivalues() as $name => $info) {
      $form['multivalues']['fields'][$name] = array();

      // Remove field checkbox.
      $form['multivalues']['fields'][$name]['remove'] = array(
        '#type' => 'checkbox',
        '#default_value' => FALSE,
      );

      // Field label.
      $form['multivalues']['fields'][$name]['label'] = array(
        '#markup' => $info['label'],
      );

      // Datatype
      $form['multivalues']['fields'][$name]['datatype'] = array(
        '#markup' => "<code>{$info['datatype']}</code>",
      );

      $form['multivalues']['fields'][$name]['usage'] = array(
        '#markup' => t('Multivalue'),
      );
    }

    $form['options']['#tree'] = TRUE;
    // In reality, these are multivalue fields that are generated
    // programmatically.
    if ($this->base_table === 'node') {
      $form['options']['node_access'] = array(
        '#title' => t('Node access'),
        '#description' => t('Include node access information in datasource'),
        '#type' => 'checkbox',
        '#default_value' => $this->options['node_access'],
      );
    }
    return $form;
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data.
   */
  function optionsSubmit($form, &$form_state) {
    switch ($form_state['clicked_button']['#id']) {
      case 'edit-index-invalidate':
        searchlight_datasource_save($this);
        drupal_set_message(t('The index for this datasource needs to be rebuilt.'));
        break;
      case 'edit-fields-new-add':
        list($table, $field) = explode('.', $form_state['values']['fields']['new']['field']);
        $this->addField($table, $field);
        searchlight_datasource_save($this, TRUE);
        break;
      case 'edit-fields-remove':
        foreach ($form_state['values']['fields']['fields'] as $name => $values) {
          if (!empty($values['remove'])) {
            $this->removeField(NULL, NULL, $name);
          }
        }
        searchlight_datasource_save($this, TRUE);
        break;
      case 'edit-multivalues-new-add':
        $this->addMultivalue($form_state['values']['multivalues']['new']['field']);
        searchlight_datasource_save($this, TRUE);
        break;
      case 'edit-multivalues-remove':
        foreach ($form_state['values']['multivalues']['fields'] as $name => $values) {
          if (!empty($values['remove'])) {
            $this->removeMultivalue($name);
          }
        }
        searchlight_datasource_save($this, TRUE);
        break;
      case 'edit-save':
        // Save additional metadata from fields, multivalues.
        foreach (array('fields', 'multivalues') as $key) {
          if (!empty($form_state['values'][$key]['fields'])) {
            foreach ($form_state['values'][$key]['fields'] as $name => $values) {
              $values = array_diff_key($values, array('remove' => NULL));
              if (isset($this->{$key}[$name])) {
                $this->{$key}[$name] = array_merge($this->{$key}[$name], $values);
              }
            }
          }
        }
        // Save options.
        $this->options = isset($form_state['values']['options']) ? $form_state['values']['options'] : array();

        // Save the datasource.
        searchlight_datasource_save($this);
        drupal_set_message(t('Datasource @datasource saved. The index for this datasource needs to be rebuilt.', array('@datasource' => $this->name)));
        break;
    }
  }

  function addField($table, $field) {
    // Add the field to the view and build. This will give us an inited handler
    // with full aliases.
    $this->viewInit()->viewSetHandlers();
    $fields = $this->view->display_handler->get_option('fields');

    // TODO: No point to index the base field.

    // The new field.
    $new_field = array(
      'table' => $table,
      'field' => $field,
      'relationship' => 'none',
    );

    // Find an existing field.
    $id = NULL;
    foreach ($fields as $_id => $_field) {
      foreach ($new_field as $_key => $_value) {
        if (!array_key_exists($_key, $_field) || $_field[$_key] !== $_value) {
          continue 2;
        }
      }
      $id = $_id;
      break;
    }

    // Generate a new id.
    if (empty($id)) {
      $id = $this->view->generate_item_id($table . '_' . $field, $fields);
    }

    // Build.
    $new_field['id'] = $id;
    $fields[$id] = $new_field;
    $this->view->display_handler->override_option('fields', $fields);
    $this->view->build();

    // Retrieve field information for storage with datasource.
    if (empty($this->view->field[$id]) || !($this->view->field[$id] instanceof views_handler_field)) {
      return;
    }
    $handler = $this->view->field[$id];

    $datatype = $this->getDatatype($handler, $handler->table, $handler->field);
    $usage = $this->getDefaultUsage($datatype);

    $this->fields[$id] = array(
      'name' => $id,
      'label' => $handler->ui_name() . " ({$handler->field})",
      'table' => $handler->table,
      'field' => $handler->field,
      'datatype' => $datatype,
      'usage' => $usage,
    );

    if (!empty($handler->additional_fields)) {
      foreach ($handler->additional_fields as $identifier => $info) {
        $table = $handler->table;
        $field = $info;
        // If the additional fields have specified table/field in an array,
        // use these.
        if (is_array($info) && isset($info['field'])) {
          $table = isset($info['table']) ? $info['table'] : $table;
          $field = $info['field'];
        }

        // Skip something.
        if (empty($handler->aliases[$field])) {
          continue;
        }
        if ($field === $handler->view->base_field && $table === $handler->view->base_table) {
          continue;
        }
        if ($field === $handler->field && $table === $handler->table) {
          continue;
        }

        $datatype = $this->getDatatype($handler, $table, $field);
        $usage = $this->getDefaultUsage($datatype);

        // TODO: indicate it is additional and cannot be removed.
        // TODO: indicate the parent and remove it along with the parent.
        $this->fields[$handler->aliases[$field]] = array(
          'label' => $handler->ui_name() . " ({$field})",
          'name' => $handler->aliases[$field],
          'table' => $table,
          'field' => $field,
          'datatype' => $datatype,
          'usage' => $usage,
          'parent' => $id,
        );
      }
    }

    return $this->viewInit()->viewSetHandlers();
  }

  function removeField($table = NULL, $field = NULL, $name = NULL) {
    if (isset($name)) {
      if (array_key_exists($name, $this->fields)) {
        unset($this->fields[$name]);
      }
    }
    else if (isset($table, $field)) {
      foreach ($this->fields as $name => $field) {
        if ($field['table'] === $table && $field['field'] === $field) {
          unset($this->fields[$name]);
        }
      }
    }
    return $this->viewInit()->viewSetHandlers();
  }

  function addMultivalue($name) {
    $multivalues = $this->buildMultivalues();
    if (isset($multivalues[$name])) {
      $this->fields[$name] = $multivalues[$name];
    }
    return $this;
  }

  function removeMultivalue($name) {
    return $this->removeField(NULL, NULL, $name);
  }
}
