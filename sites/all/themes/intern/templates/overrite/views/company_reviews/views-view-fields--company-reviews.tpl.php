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
<div class="views-field views-field-title"><?php print $fields['title']->content ?></div>

<span class="views-field views-field-name"><span class="field-content"><?php print $fields['name']->content ?></span>  </span> 
<span class="views-field views-field-postdate" style="padding-left:30px"><span class="field-content"><?php print $fields['created']->content ?></span>  </span> 

<div class="views-field views-field-picture"><?php print $fields['picture']->content ?></div>  

<?php print $fields['field_rating']->content ?>
<div class="views-field views-field-advantage">
<label><?php print t('优点：') ?></label>
<div class="field-items"><?php print $fields['field_advantage']->content ?></div>
</div>
<div class="views-field views-field-shortcoming">
<label><?php print t('缺点：') ?></label>
<div class="field-items"><?php print $fields['field_shortcoming']->content ?></div>
</div>
<div class="views-field views-field-body">
<label><?php print t('建议：') ?></label>
<div class="field-items"><?php print $fields['body']->content ?></div>
</div>
