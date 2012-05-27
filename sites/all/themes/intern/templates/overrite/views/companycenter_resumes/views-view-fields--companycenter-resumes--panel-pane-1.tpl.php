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

<div class="views-row">
	<div class="widget">
	<?php print $fields['views_bulk_operations']->content ?>
	</div>
	<div class="content">
	
			<div class="field field-name-name">
				<div class="field-items">
				<?php print $fields['field_real_name']->content ?>
				</div>
			</div> 
			<div class="field field-name-time">
				<label><?php print t('投递时间：') ?></label>
				<div class="field-items"><?php print $fields['created']->content ?></div>
			</div>
			<div class="field field-name-city">
				<label><?php print t('所在城市：') ?></label>
				<div class="field-items"><?php print $fields['field_expectation_workplace']->content ?></div>
			</div>
			<div class="field field-name-salary">
				<label><?php print t('期望待遇：') ?></label>
				<div class="field-items"><?php print $fields['field_expectation_salary']->content ?></div>
			</div>
			<div class="field field-name-degree">
				<label><?php print t('个人学历：') ?></label>
				<div class="field-items"><?php print $fields['field_education']->content ?></div>
			</div>
			<div class="field field-name-years">
				<label><?php print t('当前状态：') ?></label>
				<div class="field-items"><?php print $fields['field_status']->content ?></div>
			</div>
			<div class="field field-name-type">
				<label><?php print t('职位类别：') ?></label>
				<div class="field-items"><?php print $fields['field_expectation_industry']->content ?></div>
			</div>
			<div class="field field-name-jobnature">
				<label><?php print t('期望职位：') ?></label>
				<div class="field-items"><?php print $fields['field_expectation_occupation']->content ?></div>
			</div>

	</div>
</div><!--/.views-row -->


