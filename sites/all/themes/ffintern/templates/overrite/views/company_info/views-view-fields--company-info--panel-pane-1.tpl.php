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
<?php //print debug($fields['field_company_type']) ?>
<p><span><?php print t('企业名称：') ?></span> <?php print $fields['title']->content ?></p>
<p><span><?php print t('主营行业：') ?></span> <?php print $fields['field_industry']->content ?></p>
<p><span><?php print t('公司性质：') ?></span> <?php print $fields['field_company_type']->content ?></p>
<p><span><?php print t('公司规模：') ?></span> <?php print $fields['field_company_size']->content ?></p>
<p><span><?php print t('联系电话：') ?></span> <?php print $fields['field_phone']->content ?></p>
<p><span><?php print t('公司网址：') ?></span> <?php print $fields['field_website']->content ?></p>
<p><span><?php print t('公司简介：') ?></span> <?php print $fields['body']->content ?></p>
