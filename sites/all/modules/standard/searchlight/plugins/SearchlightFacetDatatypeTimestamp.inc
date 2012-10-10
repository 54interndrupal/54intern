<?php

/**
 * Facet plugin class for timestamps.
 */
class SearchlightFacetDatatypeTimestamp extends SearchlightFacet {
  /**
   * Override of query().
   */
  function query(&$query) {
    if (isset($this->value)) {
      $range = $query->backend->dateRange($this->value, $this->options['granularity']);

      $query->add_search_filter(NULL, $this->name, array($range['from'], $range['to']), 'BETWEEN');
    }

    // Add this facet to be built by the backend.
    $limit = isset($this->options['items']) ? $this->options['items'] : 5;
    $query->add_search_facet($this->name, $limit, array('granularity' => $this->options['granularity']));
  }

  /**
   * Render all items of a facet.
   */
  function render($query, $delta) {
    // We init the view solely for the generation of labels via the field handler.
    $this->viewInit($query);

    switch ($delta) {
      case 'active':
        if (isset($this->value)) {
          $items = array($this->value => array('id' => $this->value));
        }
        break;
      case 'facets':
        if (!isset($this->value)) {
          $items = $query->get_search_facet($this->name);
        }
        break;
    }
    if (!empty($items)) {
      // The timestamp is in the backend timezone.
      $timezone = isset($query->backend->backend_timezone) ? $query->backend->backend_timezone : date_default_timezone_get();
      if (isset($this->options['hide_before'])) {
        $hide_before = new DateObject($this->options['hide_before'], $timezone);
        $hide_before = date_format_date($hide_before, 'custom', 'U');
      }
      $null_date = new DateObject('1970-01-01 00:00:00', $timezone);
      $null_date = date_format_date($null_date, 'custom', 'U');
      foreach ($items as $k => $item) {
        $timestamp = is_numeric($item['id']) ? $item['id'] : strtotime($item['id']);
        if ($timestamp == $null_date) {
          $items[$k]['title'] = $this->options['null_value_label'];
          continue;
        }
        if ($timestamp <= $hide_before) {
          unset($items[$k]);
          continue;
        }
        $format = $this->options['date_format'];
        $items[$k]['title'] = format_date($timestamp, 'custom', $format, $timezone);
      }
      return $items;
    }
    return array();
  }

  /**
   * Provide default values for options.
   */
  function optionsDefault() {
    $options = parent::optionsDefault();
    $options['granularity'] = 'month';
    $options['date_format'] = 'Y F';
    // TODO: hide after?
    $options['hide_before'] = '1970-01-01 00:00:00';
    $options['sort'] = 'date';
    return $options;
  }

  /**
   * Provide an options form to be exposed in the Environment editor.
   */
  function optionsForm(&$form, $form_state) {
    parent::optionsForm($form, $form_state);
    $form['sort']['#type'] = 'hidden';
    $form['sort']['#value'] = 'date';
  }

  /**
   * Provide an options form to be exposed in the Environment editor.
   */
  function extendedForm(&$form, $form_state) {
    parent::extendedForm($form, $form_state);
    $form['granularity'] = array(
      '#title' => t('Granularity'),
      '#type' => 'select',
      '#options' => array(
        'year' => t('By year'),
        'month' => t('By month'),
        'day' => t('By day'),
      ),
      '#default_value' => $this->options['granularity'],
    );
    $form['date_format'] = array(
      '#title' => t('Date format'),
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $this->options['date_format'],
    );
    $form['hide_before'] = array(
      '#title' => t('Hide date before'),
      '#description' => t('Hide facet options before a date'),
      '#type' => 'textfield',
      '#size' => 20,
      '#default_value' => $this->options['hide_before'],
    );
  }
}
