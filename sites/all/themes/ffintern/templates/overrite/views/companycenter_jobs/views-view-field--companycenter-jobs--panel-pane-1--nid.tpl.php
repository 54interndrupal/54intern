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
// print($output);
$str = explode('^', trim($output));
$nid = $str[1];
$sub_status = $str[0];
$destination = drupal_get_destination();
$output ='';
if ($sub_status == JOB_SUB_STATUS_PUBLISHED) {
//  $output.= '<a href="' . url('job/actions/' . JOB_ACTION_REFRESH . '/' . $nid) . '?'.$_SERVER["QUERY_STRING"].'">刷新</a>  ';
     print l("刷新 ",'job/actions/'.JOB_ACTION_REFRESH.'/'.$nid,array('query' => drupal_get_destination()));
}
if ($sub_status == JOB_SUB_STATUS_PUBLISHED) {
  print l("暂停 ",'job/actions/'.JOB_ACTION_STOP.'/'.$nid,array('query' => drupal_get_destination()));
}
if ($sub_status == JOB_SUB_STATUS_STOPPED || $sub_status == JOB_SUB_STATUS_EXPIRED) {
  print l("再发布 ",'job/actions/'.JOB_ACTION_REPUBLISH.'/'.$nid,array('query' => drupal_get_destination()));
}
print $output;
?>