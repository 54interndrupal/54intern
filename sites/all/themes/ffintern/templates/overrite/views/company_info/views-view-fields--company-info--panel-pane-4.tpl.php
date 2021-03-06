<?php

/**
 * @file
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
<?php global $is_page_authcache;?>
<?php print $fields['field_logo']->content ?>
<div class="d-1">
  <span class="title"><?php print $fields['title']->content ?></span>
  <div id="company_info_ops">
  </div>
</div>
<div class="d-2 c-10">
  <span><span class='c-15' style=‘text-decoration: underline’><?php print $fields['count']->content ?></span> 关注&nbsp;  <span class='c-15' style=‘text-decoration: underline’><?php print $fields['nid']->content ?></span> 点评
  <span>所属行业：<?php print $fields['field_industry']->content ?></span>
  <span>公司性质：<?php print $fields['field_company_type']->content ?></span>
  <span>公司规模：<?php print $fields['field_company_size']->content ?></span>
</div>
<div class="d-3 c-10">
  <span><?php print $fields['body']->content ?></span>
  <span class="c-14 more "><?php print $fields['view_node']->content ?></span>
</div>