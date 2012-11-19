<?php

/**
 * @file
 * Core Library bypass mode specific functions.
 */

/**
 * Rebuild files for the given CSS group.
 * 
 * This function is mainly a proxy to drupal_build_css_cache() which does its
 * job quite well.
 * 
 * Because this function will name files using an ugly hash and does heavy I/O,
 * ours will call it only if really necessary, and will use non-randomized file
 * names for HTML inclusion, therefore will proceed to a file copy right after
 * each aggregated file has been created.
 * 
 * @param array $map
 *   Mapped filename.
 * @param array $medias
 *   Key value pairs, keys are CSS media property, values are Drupal core CSS
 *   description array, weight ordered, suitable for building the aggregated
 *   file.
 * 
 * @return mixed
 *   Suitable value for stored status array. If there was any during aggregated
 *   file creation or copy, this will break any remaining files to aggregate
 *   return NULL, this will force a new attempt on next page hits.
 * 
 * @see core_library_element_style_pre_render()
 * @see drupal_build_css_cache()
 */
function _core_library_element_style_rebuild_group($map, $css) {
  // Best case scenario, we have no files.
  if (empty($css)) {
    return -1;
  }

  // Build the file using core function.
  if ($file_uri = drupal_build_css_cache($css)) {
    if (file_unmanaged_copy($file_uri, 'public://static/' . $map . '.css', FILE_EXISTS_REPLACE)) {
      // Mark the file as built.
      watchdog('core_library', "CSS file for mapping " . $map . " has been sucessfully built", NULL, WATCHDOG_NOTICE);
      return TRUE;
    }
    else {
      watchdog('core_library', "CSS file for mapping " . $map . " could not be copied after being built", NULL, WATCHDOG_ERROR);
      return NULL;
    }
  }
  else {
    // Built has failed, therefore we cannot continue.
    watchdog('core_library', "CSS file for mapping " . $map . " could not be built", NULL, WATCHDOG_ERROR);
    return NULL;
  }
}

/**
 * drupal_pre_render_styles() replacement.
 * 
 * This function pass through multiple steps:
 *  1. Fetch the current aggregated files status in the $status array.
 *  2. Fetch the user set groups configuration in the $groups array.
 *  3. Check we have files matching in the status array for each group, mark
 *     each missing file for rebuild in the $rebuild array.
 *  4. Iterate over the $rebuild array, and rebuild missing files (if they are
 *     files matching the group).
 *  5. If any modification has been done to $status, save it for next hits.
 *  6. Build the drupal_render() final result using the current $status array
 *     which has been modified or not.
 *  7. Remove items we consumed from the final list, and let external files
 *     being processed by core.
 * 
 * During the whole process, we use a $mapping array. This array contain, for
 * each group, an alphanumerical filename prefix for future aggregated files.
 * 
 * Filenames are being built using this mapping array and this convention:
 *   - <group_prefix>-<media>.css
 * 
 * This function aggregates all theme files in their own group, whatever is the
 * user configuration, to ensure no theme conflicts if the site as more than
 * one themes (most sites will have at least two, frontend and backend themes).
 * 
 * Ideal case is, all files have already been built, therefore $status and
 * $groups array matches each other. In this particular case, no I/O at all is
 * being done and only the drupal_render() array is built pragmatically using
 * the $status array content.
 */
function core_library_element_style_pre_render($elements) {
  global $theme_key;

  // Status array contains filename as keys, and numeric keys as values which
  // can be any of those:
  //   - -1 : No files, no need to rebuild.
  //   - TRUE : File already built.
  //   - empty : Nothing done, or built failed, need rebuild.
  $status = variable_get('core_library_css_status');

  // Group to filename mapping. Each group can have one or more medias, we will
  // distinguish this later in the algorithm.
  $mapping = array(
    CSS_SYSTEM => 'system',
    CSS_THEME => 'theme-' . str_replace('_', '-', $theme_key),
    CSS_DEFAULT => 'default',
  );

  // What do we need to rebuild, this array will contain groups as keys, and
  // $css sub-array for each of those groups. 
  $rebuild = array();

  // Determine how to build groups. This depends on the user configuration.
  // User configuration has been taken into account by hook_library_css_alter()
  // earlier during the normal execution flow. We only have to regroup those
  // using the core grouping algorithm to ensure we have different groups for
  // browser specific files.
  foreach (drupal_group_css($elements['#items']) as $core_group) {
    $map = NULL;

    // Scan for external file, we won't handle ourselves.
    if ($core_group['type'] == 'external') {
      // FIXME: Do something!
    }
    // Scan for browser specific rules. Remember that 
    else if (!$core_group['browsers']['!IE']) {
      $map = $mapping[$core_group['group']] . '-' . str_replace(' ', '', $core_group['browsers']['IE']) . '-' . $core_group['media'];
    }
    // Normal processing (all browsers).
    else {
      $map = $mapping[$core_group['group']] . '-' . $core_group['media'];
    }

    if ($map) {
      // Populate our group array, using core given groups. Those groups reflect
      // what we aggregated before at hook_library_css_alter() time, adding
      // browser information we omitted or let live with defaults.
      $groups[$map] = $core_group;

      // Also mark the current for rebuild if needed.
      if (!isset($status[$map]) || !$status[$map]) {
        $rebuild[] = $map;
      }
    }
  }

  // Rebuild files we have to.
  if (!empty($rebuild)) {
    // Iterate over files, and rebuild the one we need.
    foreach ($rebuild as $map) {
      $status[$map] = _core_library_element_style_rebuild_group($map, $groups[$map]['items']);
    }

    // Save our status (do not rebuild CSS later).
    variable_set('core_library_css_status', $status);
  }

  // Build the final result for drupal_render().
  foreach ($groups as $map => $data) {
    // Do not include empty or non existing files. All files should be empty
    // or built when we get in this part of the algorithm.
    if ($status[$map] == TRUE) {
      // Compute the real filename using the same convention than the
      // _core_library_element_style_rebuild_group() function.
      $file = $map . '.css';

      // Add the real element for drupal_render() function to include the tag.
      $elements[] = array(
        '#type' => 'html_tag',
        '#tag' => 'link',
        '#attributes' => array(
          'type' => 'text/css',
          'rel' => 'stylesheet',
          'href' => file_create_url('public://static/' . $file),
          'media' => $data['media'],
        ),
        '#browsers' => $data['browsers'],
      );
    }
  }

  // All ok.
  return $elements;
}
