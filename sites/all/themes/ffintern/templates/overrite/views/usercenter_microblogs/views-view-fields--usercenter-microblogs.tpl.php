<?php
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<div class='author-info c-6'>
  <div class="framed"><?php print $fields['picture']->content ?></div>
  <?php print $fields['name']->content ?>
</div>


  <div class="views-field views-field-body">
    <div class="views-field views-field-body">
      <div class="field-item"><?php print $fields['body']->content ?></div>
    </div>
  </div>

<span class="views-field views-field-postdate"><span
  class="field-content c-5"><?php print $fields['created']->content ?>前</span>  </span>

<div class="views-field field-name-detail">
  <span class="field-content"><a href="#" title="查看详细" class="c-7">查看详细>></a></span>
</div>


		  



