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
<div class="user-info">
<div class="views-field views-field-picture user-picture"><?php print $fields['picture']->content ?></a></div>
<div class="views-field user-badge c-10">
  <span>等级：<span class="c-12">1</span></span>
</div>
<div class="views-field views-field-follow">
  <div class="field-content c-10"><a
    href="#">关注：<span class="c-12"><?php $counts = flag_get_counts('user', $fields['uid']->content); print isset($counts['guanzhu']) ? $counts['guanzhu'] : 0; ?></span>
    人</a></div>
</div>
<div class="views-field views-field-point">
  <div class="field-content c-10"><a
    href="<?php print url('user/' . $fields['uid']->content . '/points') ?>">积分：<span class="c-12"><?php print userpoints_get_current_points($fields['uid']->content) ?></span></a>
  </div>
</div>
<div class="views-field views-field-edit">
  <div class="field-content"><a
    href="<?php print url('user/' . $fields['uid']->content . '/edit') ?>"><span>帐号编辑</span></a>
  </div>
</div>
</div>
<div class="views-field-name">
  <div class="field-content"><?php print $fields['name']->content ?></div>
</div>
<?php $block = module_invoke('zpuser', 'block_view','resume');?>
<div class="block" id="resume-block">
  <h2 class="block-title"><span><?php print( $block['subject']);?></span></h2>
  <div class="block-content"><?php print( $block['content']);?></div>
</div>

<?php //print drupal_render($content['links']['flag']); 
print flag_create_link('guanzhu', $fields['uid']->content);
?>




<!--
<div class="views-field views-field-message">
  <div class="field-content"><a
    href="<?php print url('messages') ?>">我的消息：<?php $account = new stdClass(); $account->uid = $fields['uid']->content;print privatemsg_unread_count($account); ?>
    个</a></div>
</div>

<div class="views-field views-field-send">
  <div class="field-content"><a class="button" href="<?php print url('messages/new') ?>"><span>我要发送消息</span></a></div>
</div> -->


