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
$gid = (int)(trim($output));
$sql = "select count(etid) as count from {og_membership} og_ms,{node} nd where og_ms.gid = :gid and og_ms.etid=nd.nid and nd.type='review'";
$count = db_query($sql,array(':gid' => $gid))->fetchField();
print '<input type="hidden" id="companyId" name="companyId" value="'.$gid.'"/>';
print $count; ?>