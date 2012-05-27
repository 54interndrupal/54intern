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
<div class="views-field views-field-picture"><?php print $fields['field_logo']->content ?></div>
<div class="views-field views-field-name"><div class="field-content"><?php print $fields['title']->content ?></div>  </div>
<?php $total_jobs = db_select('node','n')
		->condition('n.uid',$fields['uid']->content)
		->condition('n.type','job')
		->fields('n',array('nid'))
    ->countQuery()
		->execute()
		->fetchField();; 
?>
<div class="views-field views-field-job"><div class="field-content"><a href="#">发布职位：<?php print $total_jobs ?>个</a></div>  </div>

<div class="views-field views-field-follow"><div class="field-content"><a href="#">关注我们：<?php $counts = flag_get_counts('node',$fields['nid']->content); print isset($counts['bookmarks']) ? $counts['bookmarks']:0; ?>人</a></div>  </div>

<div class="views-field views-field-message"><div class="field-content"><a href="<?php print url('messages') ?>">我的消息：<?php $account = new stdClass(); $account->uid = $fields['uid']->content;print privatemsg_unread_count($account); ?>个</a></div>  </div>

<div class="views-field views-field-points"><div class="field-content"><a href="#" title="发布职位消耗2点，购买简历消耗1点">企业管理点数：<?php $tid=249; print userpoints_get_current_points($account->uid,$tid); ?>点</a></div>  </div>
<div class="views-field views-field-points"><div class="field-content">发布职位消耗2点，购买简历消耗1点</div>  </div>
<div class="views-field views-field-send"><div class="field-content"><a class="button" href="<?php print url('messages/new') ?>"><span>我要发送消息</span></a></div>  </div>

<div class="views-field views-field-edit"><div class="field-content"><a class="button" href="<?php print url('node/'.$fields['nid']->content.'/edit') ?>"><span>编辑企业信息</span></a></div>  </div>

