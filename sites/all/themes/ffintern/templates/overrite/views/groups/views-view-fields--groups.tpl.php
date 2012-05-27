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
 <div class="field field-name-pic">
	<div class="field-items">
	<?php print $fields['field_group_logo']->content ?>
	</div>
</div>        
<div class="field field-name-name">
	<div class="field-items">
	<?php print $fields['title']->content ?>
	</div>
</div> 
<div class="field field-name-grouptype">
	<label><?php print t('社团分类：'); ?></label>
	<div class="field-items"><?php print $fields['field_group_category']->content ?></div>
</div>
<div class="field field-name-location">
	<div class="field-items"><?php print $fields['field_group_city']->content ?> | <?php print $fields['nid_1']->content .t('人') ?></div>
</div>
<div class="field field-name-body">
	<div class="field-items">
	<p><?php print $fields['body']->content ?></p>
	</div>
</div>
<?php
/* print l(t('加入这个社团'),'group/node/'.$fields['nid']->content.'/subscribe',array('attributes' => array('class' => array('join'),),)); 
*/
?>
<?php 
global $user;
//企业用户不能访问
if (in_array(4, array_keys($user->roles))) {
}
else{
print $fields['ops']->content;
}
?>
