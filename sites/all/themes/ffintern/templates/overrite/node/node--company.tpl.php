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
<?php //print debug($field_company_images); ?>
<div class="content">

  <input type="hidden" id="companyId" name="companyId" value="<?php print $nid?>"/>

  <div class="block" id="company-info">

    <div class="block-content">
      <div class="field field-name-pic">
        <div class="field-items">
          <?php print render($content['field_logo']); ?>
        </div>
      </div>

      <div class="company-brief-info c-1">
        <div class="field field-name-name">
          <div class="field-items c-9"><?php print $title; ?></div>
        </div>

        <div id="company_info_ops">
          <?php if (!user_is_anonymous() && !intern_user_is_company_user()) {
          drupal_add_js(drupal_get_path('module', 'intern_company') . '/js/intern_company.js');
        }
          ?>

        </div>
        <div class="field field-name-industry">
          <label> 行业：</label>

          <div class="field-items"><?php print $field_industry[0]['taxonomy_term']->name; ?></div>
        </div>
        <div class="field field-name-size">
          <label>企业规模：</label>

          <div class="field-items"><?php print $field_company_size[0]['taxonomy_term']->name; ?></div>
        </div>
        <div class="field field-name-nature">
          <label>企业性质：</label>

          <div class="field-items"><?php print $field_company_type[0]['taxonomy_term']->name; ?></div>
        </div>
        <div class="field field-name-contact">
          <label>联系人：</label>

          <div class="field-items"><?php print $field_contact[0]['safe_value']; ?></div>
        </div>
        <div class="field field-name-website">
          <label>企业网址：</label>

          <div class="field-items"><?php print $field_website[0]['safe_value']; ?></div>
        </div>
        <div class="field field-name-body">
          <label class='c-9'>企业简介：</label>


          <?php
          $body_content = $body[0]['safe_value'];
          if (drupal_strlen($body_content) > 150) {
            print '<span id=\'show-detail\' class="c-9">' . '展开>>' . '</span>';
            $body_sub_content = drupal_substr($body_content, 0, 150);
            $body_sub_content = rtrim(preg_replace('/(?:<(?!.+>)|&(?!.+;)).*$/us', '', $body_sub_content)) . '...';
            print '<div class="field-items" id="body-sub-content">' . $body_sub_content . '</div>';
            print '<div class="field-items" style="display:none" id="body-content">' . $body_content . '</div>';
          }
          else {
            print $body[0]['safe_value'];
          }

          ?>
        </div>
      </div>
    </div>
  </div>
</div>
<?php if (count($field_company_images) > 0) { ?>
<div class="block" id="company-photos"><!-- 需要载入 jquery.jcarousel.min.js -->
  <div class="block-content">
    <ul>
      <?php
      if (count($field_company_images) > 0) {
        $field_company_image_output = '';
        foreach ($field_company_images as $field_company_image) {

          $uri = $field_company_image["uri"];
          $url = file_create_url($uri);
          //$newsimage_title = $newsimage["title"];
          //$newsimage_url= file_create_url($newsimage["uri"]);
          $field_company_image_url = image_style_url('138_102', $uri);
          $field_company_image_pic = '<img src="' . $field_company_image_url . '"/>';

          $field_company_image_output .= '<li>';
          $field_company_image_output .= '<a href="' . $url . '" class="company-photos-photo-link">';
          $field_company_image_output .= $field_company_image_pic;
          $field_company_image_output .= '</a></li>';

        }
        print  $field_company_image_output;

      }
      else {

      }
      ?>
    </ul>
  </div>
</div>
<?php } ?>

</div><!-- /.content -->
<script type="text/javascript">
  (function ($) {
    $(document).ready(function () {
      $('#show-detail').click(function () {
        if ($("#body-content:visible").size() == 0) {
          $('#show-detail').text('收起>>');
        } else {
          $('#show-detail').text('展开>>');
        }
        $("#body-content").toggle();
        $("#body-sub-content").toggle();
        return false;
      });

      $("#quicktabs-tab-node_company_tab-0").click(function(){
        $(".pane-intern-company-company-node-add-review").show();
      })
      $("#quicktabs-tab-node_company_tab-1").click(function(){
        $(".pane-intern-company-company-node-add-review").hide();
      })


    });
  })(jQuery);


  function resetReviewNodeForm(){
    jQuery("#edit-body-und-0-value").val("");
    Authcache.resetFormToken();
  }
</script>



