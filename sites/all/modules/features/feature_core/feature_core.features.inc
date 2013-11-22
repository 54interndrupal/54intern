<?php
/**
 * @file
 * feature_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_core_ctools_plugin_api() {
  return array("version" => "1");
}

/**
 * Implements hook_flag_default_flags().
 */
function feature_core_flag_default_flags() {
  $flags = array();
  // Exported flag: "申请职位".
  $flags['apply'] = array(
    'content_type' => 'node',
    'title' => '申请职位',
    'global' => '0',
    'types' => array(
      0 => 'job',
    ),
    'flag_short' => '申请职位',
    'flag_long' => '',
    'flag_message' => '您已成功申请该职位!',
    'unflag_short' => '取消申请',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '您已成功申请该职位。',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "关注".
  $flags['bookmarks'] = array(
    'content_type' => 'node',
    'title' => '关注',
    'global' => '0',
    'types' => array(
      0 => 'job',
      1 => 'company',
    ),
    'flag_short' => '关注',
    'flag_long' => '',
    'flag_message' => '关注成功',
    'unflag_short' => '取消关注',
    'unflag_long' => '',
    'unflag_message' => '已取消关注',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => 'others',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "购买简历".
  $flags['buy'] = array(
    'content_type' => 'node',
    'title' => '购买简历',
    'global' => '0',
    'types' => array(
      0 => 'resume',
    ),
    'flag_short' => '购买简历',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '取消购买',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '已购买',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '3',
      ),
      'unflag' => array(
        0 => '3',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "收藏".
  $flags['collect'] = array(
    'content_type' => 'node',
    'title' => '收藏',
    'global' => '0',
    'types' => array(
      0 => 'job',
      1 => 'article',
      2 => 'review',
    ),
    'flag_short' => '收藏',
    'flag_long' => '',
    'flag_message' => '收藏成功',
    'unflag_short' => '取消收藏',
    'unflag_long' => '',
    'unflag_message' => '已取消收藏',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Follow".
  $flags['follow'] = array(
    'content_type' => 'user',
    'title' => 'Follow',
    'global' => '0',
    'types' => array(
      0 => '-',
    ),
    'flag_short' => 'Follow',
    'flag_long' => '',
    'flag_message' => 'Following',
    'unflag_short' => 'Unfollow',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_profile' => 'true',
    'access_uid' => '',
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "加入社团".
  $flags['join'] = array(
    'content_type' => 'node',
    'title' => '加入社团',
    'global' => '0',
    'types' => array(),
    'flag_short' => '加入社团',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '退出社团',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "喜欢".
  $flags['like'] = array(
    'content_type' => 'node',
    'title' => '喜欢',
    'global' => '1',
    'types' => array(
      0 => 'article',
    ),
    'flag_short' => '[node:flag-like-count]',
    'flag_long' => '喜欢',
    'flag_message' => '',
    'unflag_short' => '[node:flag-like-count]',
    'unflag_long' => '不喜欢',
    'unflag_message' => '',
    'unflag_denied_text' => '不允许重复操作',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => 'others',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Like".
  $flags['like_comments'] = array(
    'content_type' => 'fbss_comment',
    'title' => 'Like',
    'global' => '0',
    'types' => array(
      0 => 'page',
    ),
    'flag_short' => 'Like',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Un-like',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "报告".
  $flags['report'] = array(
    'content_type' => 'node',
    'title' => '报告',
    'global' => '0',
    'types' => array(
      0 => 'review',
    ),
    'flag_short' => '不当内容',
    'flag_long' => '',
    'flag_message' => '上报不当内容成功',
    'unflag_short' => '取消上报',
    'unflag_long' => '',
    'unflag_message' => '取消上报不当内容',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "企业用户审核".
  $flags['shenhe'] = array(
    'content_type' => 'node',
    'title' => '企业用户审核',
    'global' => '1',
    'types' => array(
      0 => 'company',
    ),
    'flag_short' => '批准',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '取消批准',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '3',
      ),
      'unflag' => array(
        0 => '3',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "赞".
  $flags['zan'] = array(
    'content_type' => 'node',
    'title' => '赞',
    'global' => '1',
    'types' => array(
      0 => 'review',
    ),
    'flag_short' => '赞([node:flag-zan-count])',
    'flag_long' => '',
    'flag_message' => '赞',
    'unflag_short' => '踩([node:flag-zan-count])',
    'unflag_long' => '',
    'unflag_message' => '踩',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'feature_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;
}
