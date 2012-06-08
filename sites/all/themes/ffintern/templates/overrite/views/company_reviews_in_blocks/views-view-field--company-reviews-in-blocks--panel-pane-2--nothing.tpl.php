<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php
if (drupal_strlen($output) > 120) {
  $body_sub_content = drupal_substr($output, 0, 120);
  $body_sub_content = rtrim(preg_replace('/(?:<(?!.+>)|&(?!.+;)).*$/us', '', $body_sub_content)) . '...';
?>
  <div class="sub-content" style="display: block"><?php print $body_sub_content?></div>
  <div class="full-content" style="display: none"><?php print $output?></div>
  <div class="views-field views-field-nid"> <span class="field-content"><a href="#" class="toggleReviewDetail">查看详细>></a></span>  </div>
<?php
} else{print $output;}
?>