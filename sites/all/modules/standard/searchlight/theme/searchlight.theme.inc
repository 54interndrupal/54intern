<?php

/**
 * Preprocessor for theme('searchlight_sphinx_conf').
 */
function template_preprocess_searchlight_sphinx_conf(&$vars) {
  foreach ($vars['searchd'] as $key => $value) {
    $vars['searchd'][$key] = "$value\n";
  }
}
/**
* Preprocessor for theme('searchlight_sphinx_index_conf').
*/
function template_preprocess_searchlight_sphinx_index_conf(&$vars) {
  foreach (array('conf', 'query', 'index') as $key) {
    foreach ($vars['datasource'][$key] as $_key => $_value) {
      $vars['datasource'][$key][$_key] = "$_value\n";
    }
    foreach ($vars['datasource']['delta'][$key] as $_key => $_value) {
      $vars['datasource']['delta'][$key][$_key] = "$_value\n";
    }
  }
}

/**
 * Preprocessor for theme('searchlight_solr_schema').
 */
function template_preprocess_searchlight_solr_schema(&$vars) {
  $defaults = array(
    'indexed' => 'true',
    'stored' => 'true',
    'multiValued' => 'false',
  );
  foreach ($vars['datasource']['schema'] as $id => $field) {
    // Populate defaults.
    foreach ($defaults as $k => $v) {
      if (!isset($field[$k])) {
        $vars['datasource']['schema'][$id][$k] = $v;
      }
    }
    // Normalize boolean values
    foreach ($field as $attribute => $value) {
      if (is_bool($value)) {
        $vars['datasource']['schema'][$id][$attribute] = ($value === TRUE ? 'true' : 'false');
      }
    }
  }
}

/**
 * Theme function for searchlight global search form.
 * As this is a GET form, FormAPI related data can be excluded.
 */
function theme_searchlight_search_form() {
  $output = '';
  foreach (element_children($form) as $key) {
    if (!in_array($key, array('form_build_id', 'form_token', 'form_id'))) {
      $output .= drupal_render($form[$key]);
    }
  }
  return $output;
}

/**
 * Theme function for searchlight datasource display form.
 */
function theme_searchlight_plugin_display_datasource($variables) {
  $variables = $variables['form'];
  $form = $variables['form'];
  $output = '';
  $rows = array();
  foreach (element_children($form) as $key) {
    $row = array();
    $row[] = $form[$key]['#title'];
    foreach (element_children($form[$key]) as $cell) {
      if (isset($form[$key][$cell]['#type']) && !in_array($form[$key][$cell]['#type'], array('hidden', 'value'))) {
        $row[] = drupal_render_children($form[$key][$cell]);
      }
    }
    $rows[] = $row;
  }
  $output = theme('table', array('header' => array(t('Field'), t('Datatype'), t('Usage'), t('Show facet'), ''),
      'rows' => $rows,
    ));
  $output .= drupal_render_children($form);
  return $output;
}

/*
 * Theme function for facet inner list (see @item_list)
 */
function theme_facet_list($variables) {
  $items = $variables['items'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  $output = '';

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 0) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items - 1) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  return $output;
}

/**
 * Theme function for a facet.
 */
function theme_searchlight_facet($variables) {
  $facet = $variables['facet'];

  if (isset($facet['active']['label'])) {
    $title = $facet['active']['label'];
  }
  elseif (isset($facet['facets']['label'])) {
    $title = $facet['facets']['label'];
  }

  $output = '<div class="item-list">';
  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  foreach ($facet as $delta => $elements) {
    if (isset($facet[$delta]['items'])) {
      $output .= theme_facet_list(array(
        'items' => $facet[$delta]['items'],
        'type' => 'ul',
        'attributes' => array('class' => array('searchlight-facet-' . $delta)),
      ));
    }
  }

  $output .= '</div>';
  return $output;
}

/**
 * Theme function for an individual (inactive) facet link.
 */
function theme_searchlight_facet_link($variables) {
  $item = $variables['item'];
  $class = isset($item['class']) ? $item['class'] : '';
  $link = theme('link', $item['link']);
  return "<div class='searchlight-facet {$class}'>{$link} <span class='count'>{$item['count']}</span></div>";
}

/**
 * Theme function for an individual (active) facet link.
 */
function theme_searchlight_facet_active($variables) {
  $item = $variables['item'];
  $class = isset($item['class']) ? $item['class'] : '';
  $title = check_plain($item['title']);
  $link = theme('link', $item['link']);
  return "<div class='searchlight-facet {$class}'>{$title} <span class='remove'>{$link}</span></div>";
}

/**
 * Generates the main datasource admin page.
 */
function theme_searchlight_admin_list($variables) {
  $form = $variables['form'];
  drupal_add_css(drupal_get_path("module", "searchlight") . "/searchlight.admin.css");

  $rows = array();

  // Generate listing of existing objects
  foreach ($form['#objects'] as $group => $objects) {
    if (!empty($group)) {
      $rows[] = array(array(
          'data' => check_plain($group),
          'colspan' => 4,
          'header' => TRUE,
        ));
    }
    foreach ($objects as $object) {
      if ($object instanceof SearchlightDatasource) {
        $extra = $object->base_table;
        $type = 'datasource';
        $path = 'datasource';
        $name_label = t('Active datasource');
        $extra_label = t('Base table');
      }
      else if ($object instanceof SearchlightEnvironment) {
        $extra = $object->view_display;
        $type = 'environment';
        $path = 'environment';
        $name_label = t('Environment');
        $extra_label = t('View');
      }

      $row = array();

      // Info
      $storage = t('Default');
      if ($object->export_type & EXPORT_IN_DATABASE) {
        $storage = $object->export_type & EXPORT_IN_CODE ? t('Overridden') : t('Normal');
      }

      if ($type === 'datasource') {
        $row[] = array(
          'data' => drupal_render($form['active'][$object->base_table][$object->name]),
          'class' => array('object-name'),
        );
      }
      else {
        $row[] = array(
          'data' => $object->name,
          'class' => array('object-name'),
        );
      }
      $row[] = array(
        'data' => $extra,
        'class' => array('object-extra'),
      );
      $row[] = array(
        'data' => $storage,
        'class' => array('object-storage'),
      );

      // Actions
      $links = array(
        'edit' => l(t('Edit'), "admin/config/search/settings/{$path}/{$object->name}"),
        'delete' => l(t('Delete'), "admin/config/search/settings/{$path}/{$object->name}/delete"),
        'revert' => l(t('Revert'), "admin/config/search/settings/{$path}/{$object->name}/revert"),
      );
      foreach (array_keys($links) as $key) {
        if (!searchlight_task_access($object, $key)) {
          unset($links[$key]);
        }
      }
      $row[] = array(
        'data' => implode(' | ', $links),
        'class' => array('object-links'),
      );
      $rows[] = $row;
    }
  }
  $row = array();
  foreach (element_children($form['new']) as $key) {
    if ($form['new'][$key]['#type'] === 'submit') {
      $row[] = array(
        'data' => drupal_render($form['new'][$key]),
        'colspan' => 2,
      );
    }
    else {
      $row[] = drupal_render($form['new'][$key]);
    }
  }
  $rows[] = $row;
  $output = theme('table', array(
    'header' => isset($name_label) ? array($name_label, $extra_label, t('Storage'), t('Operations')) : array(),
    'rows' => $rows,
    'attributes' => array(
      'class' => array('object-admin')
    ),
  ));
  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Theme function for searchlight datasource display form.
 */
function theme_searchlight_admin_datasource_fields($variables) {
//  $variables = $variables['form'];
  $form = $variables['form'];
  $output = '';
  $rows = array();
  drupal_add_js('misc/tableselect.js');

  // New fields header.
  if (!empty($form['new'])) {
    $rows[] = array(array(
        'data' => t('Add field'),
        'colspan' => 4,
        'header' => TRUE,
      ));
    $rows[] = array(
      array(
        'data' => drupal_render($form['new']['field']),
        'colspan' => 3,
      ),
      array('data' => drupal_render($form['new']['add'])),
    );
  }
  // Existing fields.
  // TODO Please change this theme call to use an associative array for the $variables parameter.
  $rows[] = array(
    array(
      'class' => array('select-all'),
      'header' => TRUE,
    ),
    array(
      'data' => t('Field'),
      'header' => TRUE,
    ),
    array(
      'data' => t('Datatype'),
      'header' => TRUE,
    ),
    array(
      'data' => t('Usage'),
      'header' => TRUE,
    ),
  );
  foreach (element_children($form['fields']) as $key) {
    if ($key !== 'new') {
      $row = array();
      foreach (element_children($form['fields'][$key]) as $cell) {
        if (isset($form['fields'][$key][$cell]['#markup']) ||
          (isset($form['fields'][$key][$cell]['#type']) &&
          !in_array($form['fields'][$key][$cell]['#type'], array('hidden', 'value')))) {

          $row[] = drupal_render($form['fields'][$key][$cell]);
        }
      }
      $rows[] = $row;
    }
  }
  if (!element_children($form['fields'])) {
    $rows[] = array(array(
        'data' => t('No fields found.'),
        'colspan' => 4,
      ));
  }
  // Remove fields footer.
  if (!empty($form['remove'])) {
    $rows[] = array(array(
        'data' => drupal_render($form['remove']),
        'colspan' => 4,
        'header' => TRUE,
      ));
  }

  $output = theme('table', array(
      'header' => array(),
      'rows' => $rows,
      'attributes' => array(),
      'caption' => $form['#title'],
    ));

  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Preprocessor for theme('searchlight_admin_environment').
 */
function template_preprocess_searchlight_admin_environment(&$vars) {
  drupal_add_tabledrag('searchlight-environment', 'order', 'sibling', 'searchlight-environment-weight', NULL, NULL, TRUE);

  // Basic environment info.
  $environment = $vars['form']['#environment'];
  $vars['name'] = check_plain($environment->name);

  // View switcher.
  $settings = '';
  $facets = '';
  $rows = array();
  $rows[] = array(
    array(
      'data' => drupal_render($vars['form']['view_display']['view_display']),
      'colspan' => 3,
    ),
    array(
      'data' => drupal_render($vars['form']['view_display']['update']),
      'colspan' => 3,
    ),
  );

  // Build facets table.
  if (!empty($vars['form']['facets'])) {
    uasort($vars['form']['facets'], 'element_sort');
  }
  $header_row = array();
  $facet_rows = array();
  foreach (element_children($vars['form']['facets']) as $key) {
    $row = array();
    foreach (element_children($vars['form']['facets'][$key]) as $cell) {
      // Handle element title as table header.
      if (empty($header_row[$cell])) {
        $header_cell = !empty($vars['form']['facets'][$key][$cell]['#title']) ? check_plain($vars['form']['facets'][$key][$cell]['#title']) : '';
        $header_row[$cell] = array(
          'data' => $header_cell,
          'header' => TRUE,
        );
      }
      if (isset($vars['form']['facets'][$key][$cell]['#title'])) {
        unset($vars['form']['facets'][$key][$cell]['#title']);
      }
      // Handling for specific elements.
      switch ($cell) {
        case 'weight':
          $vars['form']['facets'][$key][$cell]['#attributes']['class'] = array('searchlight-environment-weight');
          $row[] = drupal_render($vars['form']['facets'][$key][$cell]);
          break;
        case 'settings':
          $element_settings = drupal_render($vars['form']['facets'][$key][$cell]);
          $element_settings_id = "searchlight-facet-{$key}";
          if (!empty($element_settings)) {
            $element_settings_form = "<div class='environment-settings'>";
            $element_settings_form .= l(t('Edit'), $_GET['q'], array( 'attributes' => array('class' => array('environment-settings-link')),'fragment' => $element_settings_id));
            $element_settings_form .= "<div class='environment-settings-form' id='{$element_settings_id}'>{$element_settings}</div>";
            $element_settings_form .= "</div>";
            $row[] = $element_settings_form;
          }
          else {
            $row[] = '';
          }
          break;
        default:
          $row[] = drupal_render($vars['form']['facets'][$key][$cell]);
          break;
      }
    }
    $facet_rows[] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }

  $rows[] = $header_row;
  $rows = array_merge($rows, $facet_rows);
  // Facet table.
  $facets .= theme('table', array(
      'header' => array(),
      'rows' => $rows,
      'attributes' => array('id' => 'searchlight-environment'),
    ));
  $vars['facets'] = $facets;

  // Per-facet settings.
  $vars['settings'] = $settings;
}

/**
 * Preprocessor for theme('searchlight_admin_datasource').
 */
function template_preprocess_searchlight_admin_datasource(&$vars) {
  drupal_add_css(drupal_get_path("module", "searchlight") . "/searchlight.admin.css");

  $datasource = $vars['form']['#datasource'];
  $base_tables = views_fetch_base_tables();

  $vars['name'] = check_plain($datasource->name);
  $vars['base_table'] = isset($base_tables[$datasource->base_table]['title']) ? check_plain($base_tables[$datasource->base_table]['title']) : check_plain($datasource->base_table);
}
