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
<div class="column first-column">
		<div class="field field-name-name">
			<label><?php print t('企业名称：') ?></label>
			<div class="field-items">
			<?php print $fields['title']->content ?>
			</div>
		</div> 
		<div class="field field-name-body">
			<label><?php print t('企业介绍：') ?></label>
			<div class="field-items">
<?php print $fields['body']->content ?>
			</div>
		</div>
</div>
<div class="column second-column">
		<div class="field field-name-logo">
			<div class="field-items">
			<?php print $fields['field_logo']->content ?>
			</div>
		</div>        
		<div class="field field-name-industry">
			<label><?php print t('所属行业：') ?></label>
			<div class="field-items"><?php print $fields['field_industry']->content ?></div>
		</div>
		<div class="field field-name-size">
			<label><?php print t('企业规模：') ?></label>
			<div class="field-items"><?php print $fields['field_company_size']->content ?></div>
		</div>
		<div class="field field-name-nature">
			<label><?php print t('企业性质：') ?></label>
			<div class="field-items"><?php print $fields['field_company_type']->content ?></div>
		</div>
</div>
<?php
/*
 print l(t('关注这个企业'),'flag/flag/bookmarks/'.$fields['nid']->content,
array(
'attributes' => array('class' => array('join')),
'query' => array('token' => flag_get_token($fields['nid']->content))
));
*/
 ?>

<?php //print drupal_render($content['links']['flag']); 
 print flag_create_link('bookmarks', $fields['nid']->content);
?>


