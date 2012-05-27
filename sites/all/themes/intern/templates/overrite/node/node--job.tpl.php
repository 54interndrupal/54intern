<?php

/**
 * @file
 * Bartik's theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct url of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type, i.e., "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type, i.e. story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode, e.g. 'full', 'teaser'...
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined, e.g. $node->body becomes $body. When needing to access
 * a field's raw values, developers/themers are strongly encouraged to use these
 * variables. Otherwise they will have to explicitly specify the desired field
 * language, e.g. $node->body['en'], thus overriding any language negotiation
 * rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 */
?>
<?php //print debug($content['links']['flag']); ?>
<?php //print drupal_render($content['links']['flag']); 
 //print flag_create_link('apply', $nid);
?>
<?php $node = node_load($node->nid); ?>
<h1 class="title" id="page-title"><?php print $node->title; ?></h1>
<div id="job-info" class="block">
<h2 class="block-title"><span>职位信息</span></h2>
<div class="block-content">
<div class="column first-column">
		<div class="field field-name-name">
			<label>职位名称：</label>
			<div class="field-items">
			<a href="#"><?php print $node->title; ?></a>
			</div>
		</div> 
		<div class="field field-name-body">
			<label>职位介绍：</label>
			<div class="field-items">
			<?php print $body[0]['safe_value']; ?>
			</div>
		</div>
</div>
<div class="column second-column">
		<div class="field field-name-time">
			<label>更新时间：</label>
			<div class="field-items"><?php print format_date($changed,'custom','Y-m-d'); ?></div>
		</div>
		<div class="field field-name-degree">
			<label>学历要求：</label>
			<div class="field-items"><?php print $field_education_requirement[0]['taxonomy_term']->name; ?></div>
		</div>
		<div class="field field-name-jobnature">
			<label>职业性质：</label>
			<div class="field-items"><?php print $field_job_type[0]['taxonomy_term']->name; ?></div>
		</div>
		<div class="field field-name-joblocation">
			<label>职位地点：</label>
			<div class="field-items"><?php print $field_work_place[0]['taxonomy_term']->name; ?></div>
		</div>
		<div class="field field-name-years">
			<label>学习年限：</label>
			<div class="field-items"><?php print $field_study_years[0]['taxonomy_term']->name; ?></div>
		</div>
		<div class="field field-name-salary">
			<label>每月薪水：</label>
			<div class="field-items"><?php print $field_salary[0]['taxonomy_term']->name; ?></div>
		</div>
		<div class="field field-name-number">
			<label> 招聘人数：</label>
			<div class="field-items"><?php print $field_number[0]['value']; ?></div>
		</div>
</div>
<?php
/* print l(t('申请这个职位'),'flag/flag/apply/'.$nid,
array(
'attributes' => array('class' => array('join')),
'query' => array('token' => flag_get_token($nid),drupal_get_destination())
)); 
*/
?>
<?php //print drupal_render($content['links']['flag']); 
global $user;
//企业用户不能访问
if (in_array(4, array_keys($user->roles))) {
}
else{
 print flag_create_link('apply', $nid);
}
?>
</div>
</div>

<?php print views_embed_view('company_info_in_job','default',$og_group_ref[0]['target_id']); ?>
