<?php

/**
 * Override or insert variables into the maintenance page template.
 */
function seven_preprocess_maintenance_page(&$vars) {
  // While markup for normal pages is split into page.tpl.php and html.tpl.php,
  // the markup for the maintenance page is all in the single
  // maintenance-page.tpl.php template. So, to have what's done in
  // seven_preprocess_html() also happen on the maintenance page, it has to be
  // called here.
  seven_preprocess_html($vars);
}

/**
 * Override or insert variables into the html template.
 */
function seven_preprocess_html(&$vars) {
  // Add conditional CSS for IE8 and below.
  drupal_add_css(path_to_theme() . '/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 8', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
  // Add conditional CSS for IE7 and below.
  drupal_add_css(path_to_theme() . '/ie7.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
  // Add conditional CSS for IE6.
  drupal_add_css(path_to_theme() . '/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 6', '!IE' => FALSE), 'weight' => 999, 'preprocess' => FALSE));
}

/**
 * Override or insert variables into the page template.
 */
function seven_preprocess_page(&$vars) {
  $vars['primary_local_tasks'] = $vars['tabs'];
  unset($vars['primary_local_tasks']['#secondary']);
  $vars['secondary_local_tasks'] = array(
    '#theme' => 'menu_local_tasks',
    '#secondary' => $vars['tabs']['#secondary'],
  );
}

/**
 * Display the list of available node types for node creation.
 */
function seven_node_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="clearfix">';
      $output .= '<span class="label">' . l($item['title'], $item['href'], $item['localized_options']) . '</span>';
      $output .= '<div class="description">' . filter_xss_admin($item['description']) . '</div>';
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  else {
    $output = '<p>' . t('You have not created any content types yet. Go to the <a href="@create-content">content type creation page</a> to add a new content type.', array('@create-content' => url('admin/structure/types/add'))) . '</p>';
  }
  return $output;
}

/**
 * Overrides theme_admin_block_content().
 *
 * Use unordered list markup in both compact and extended mode.
 */
function seven_admin_block_content($variables) {
  $content = $variables['content'];
  $output = '';
  if (!empty($content)) {
    $output = system_admin_compact_mode() ? '<ul class="admin-list compact">' : '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="leaf">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      if (isset($item['description']) && !system_admin_compact_mode()) {
        $output .= '<div class="description">' . filter_xss_admin($item['description']) . '</div>';
      }
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme_tablesort_indicator().
 *
 * Use our own image versions, so they show up as black and not gray on gray.
 */
function seven_tablesort_indicator($variables) {
  $style = $variables['style'];
  $theme_path = drupal_get_path('theme', 'seven');
  if ($style == 'asc') {
    return theme('image', array('path' => $theme_path . '/images/arrow-asc.png', 'alt' => t('sort ascending'), 'width' => 13, 'height' => 13, 'title' => t('sort ascending')));
  }
  else {
    return theme('image', array('path' => $theme_path . '/images/arrow-desc.png', 'alt' => t('sort descending'), 'width' => 13, 'height' => 13, 'title' => t('sort descending')));
  }
}

/**
 * Implements hook_css_alter().
 */
function seven_css_alter(&$css) {
  // Use Seven's vertical tabs style instead of the default one.
  if (isset($css['misc/vertical-tabs.css'])) {
    $css['misc/vertical-tabs.css']['data'] = drupal_get_path('theme', 'seven') . '/vertical-tabs.css';
  }
  if (isset($css['misc/vertical-tabs-rtl.css'])) {
    $css['misc/vertical-tabs-rtl.css']['data'] = drupal_get_path('theme', 'seven') . '/vertical-tabs-rtl.css';
  }
  // Use Seven's jQuery UI theme style instead of the default one.
  if (isset($css['misc/ui/jquery.ui.theme.css'])) {
    $css['misc/ui/jquery.ui.theme.css']['data'] = drupal_get_path('theme', 'seven') . '/jquery.ui.theme.css';
  }
}

function seven_select($variables) {
  $element = $variables['element'];
//  print_r($element);

  if ($element['#parents'][0] == 'field_location_tid' || $element['#parents'][0] == 'job_category'
    || $element['#parents'][0] == 'field_location' || $element['#parents'][0] == 'field_job_category'
    || $element['#parents'][0] == 'field_industry_tid' || $element['#parents'][0] == 'field_industry'
  ) {
    $selectValue = $element['#value'];
    if (is_array($selectValue)) {
      $selectValue = $selectValue[0];
    }


    $selectOption = '不限';
    foreach ($element['#options'] as $index => $choice) {
      if ($index == $selectValue) {
        $selectOption = $choice;
        break;
      }

      if (is_array($choice)) {
      }
      elseif (is_object($choice)) {
        if (isset($choice->option[$selectValue])) {
          $selectOption = $choice->option[$selectValue];
          break;
        }

      }
    }
    $error_class = '';
    if (isset($element['#parents']) && form_get_error($element)) {
      $error_class = 'error';
    }

    drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/drag.js");
    drupal_add_css(drupal_get_path('theme', "ffintern") . "/popups/alpha.css");
    drupal_add_css(drupal_get_path('theme', "ffintern") . "/popups/css.css");
    $output = '<input type="hidden" name="' . $element['#name'] . '" id="' . $element['#id'] . '" value="' . $selectValue . '">';
    if ($element['#parents'][0] == 'field_location_tid' || $element['#parents'][0] == 'field_location') {
      drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/city_func.js");
      drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/city_arr.js");
      $output .= '<div><input type="text" name="citySelect" onclick="residencySelect(\'' . $element['#id'] . '\');" id="sel-' . $element['#id'] . '" class="form-text search '.$error_class.'" value="' . $selectOption . '"></div>';
    }
    else {
      if ($element['#parents'][0] == 'job_category' || $element['#parents'][0] == 'field_job_category') {
        drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/funtype_func.js");
        drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/funtype_arr.js");
        $output .= '<div><input type="text" name="jobCategorySelect"  onclick="funtypeSelect_2(\'' . $element['#id'] . '\');" id="sel-' . $element['#id'] . '" class="form-text search '.$error_class.'" value="' . $selectOption . '"></div>';
      }
      else {
        if ($element['#parents'][0] == 'field_industry_tid' || $element['#parents'][0] == 'field_industry') {
          drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/industry_func.js");
          drupal_add_js(drupal_get_path('theme', "ffintern") . "/popups/industry_arr.js");
          $output .= '<div><input type="text" name="industrySelect"  onclick="IndustrySelect_2(\'' . $element['#id'] . '\');" id="sel-' . $element['#id'] . '" class="form-text search '.$error_class.'" value="' . $selectOption . '"></div>';
        }
      }
    }
    return $output;
  }
  else {
    element_set_attributes($element, array('id', 'name', 'size'));
    _form_set_class($element, array('form-select'));
    return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
  }

}
