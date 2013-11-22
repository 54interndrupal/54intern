<?php
/**
 * @file
 * feature_core.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function feature_core_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_about_us';
  $page->task = 'page';
  $page->admin_title = 'page about us';
  $page->admin_description = '';
  $page->path = 'siteinfo';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_about_us_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_about_us';
  $handler->handler = 'panel_context';
  $handler->weight = '0';
  $handler->conf = array(
    'title' => 'Panel About Us',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => 'site-info',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'intern_3col_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'main' => NULL,
      'second' => NULL,
      'first' => NULL,
      'highlighted' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'first';
    $pane->type = 'block';
    $pane->subtype = 'shixiquan-aboutInfoBlock';
    $pane->shown = '1';
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = '0';
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['first'][0] = 'new-1';
    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'main';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = '1';
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'siteinfo/about-us',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '关于我们',
      'body' => '<p>实习，是每个在校大学生就业前绕不开的热点话题。</p><p><span style="font-size:20px;">实习圈</span><strong>，</strong>着力构建高校学生实习主题交流平台。在这里，你可以搜索并申请感兴趣的实习机会，阅读实习文章，汲取他人实习经验，交流实习心得体会，并可分享或了解他人在目标企业的实习点评。</p><p>&ldquo;先出发，给未来更多可能&rdquo;，请加入实习圈，与全体圈友同行；在实习就业的路上，你不是一个人在战斗！</p>',
      'format' => 'fitered_html_with_editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = '0';
    $pane->locks = array();
    $display->content['new-2'] = $pane;
    $display->panels['main'][0] = 'new-2';
    $pane = new stdClass();
    $pane->pid = 'new-3';
    $pane->panel = 'main';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = '1';
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'siteinfo/disclaimer',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '免责申明',
      'body' => '<p><strong>版权申明</strong></p><p>实习圈网站文章内容由本站原创、转载组成。</p><p><strong>原创作品</strong></p><p>原创作品版权归本站或著作者本人所有，受中国及国际版权法的保护。任何单位或个人转载、引用本网站内容，必须注明原作者和出处，凡是网页上注明&ldquo;版权所有，不得转载&rdquo;之文章，未取得本站书面许可，其它网站不得摘录转载。</p><p><strong>文章转载</strong></p><p>本网站转载的文章仅供网友交流学习心理，全部免费阅读，无任何商业经验性目的。转载时，凡是原文有清晰的作者和出处，我们会完全注明。对原文中本无作者或不明首发何处的文章，若因文章质量优秀，我们亦会转载，并请原作者尽快联系我们，邮箱：<a href="mailto:54intern@54intern.com">54intern@54intern.com</a> .</p>',
      'format' => 'fitered_html_with_editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = '1';
    $pane->locks = array();
    $display->content['new-3'] = $pane;
    $display->panels['main'][1] = 'new-3';
    $pane = new stdClass();
    $pane->pid = 'new-4';
    $pane->panel = 'main';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = '1';
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'siteinfo/privacy-policy',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '隐私条款',
      'body' => '<p>实习圈重视用户的隐私权，我们也深知您向实习圈提供各种信息是基于对实习圈的完全信任。实习圈的宗旨是以诚信为本，我们一定会以负责的态度对待您提交给我们的信息，实习圈郑重承诺如下：</p><p>1. 实习圈郑重承诺不会出售用户的任何信息，并保护您的电子邮件、手机号码、姓名等个人隐私信息。<br />2. 实习圈采取了有效的措施保护您的个人隐私资料。除非根据法律或政府的强制性规定，否则在未得到用户的许可之前，我们不会把用户的任何个人资料提供给无关的第三方（包括公司或个人）。</p><p>下面具体阐述了本网站如何处理用户的隐私问题。</p><p>&nbsp;</p><h4>一、我们所收集的信息以及如何使用：</h4><p>&nbsp;</p><h4>1. 用户提交资料</h4><p>当您注册实习圈用户时，您需要提供 电子邮件地址，以便我们识别您的身份或必要时与您联络。我们会利用一些有效方法，确认您个人资料的正确性与有效性。</p><h4>2. 用户的个人详细资料（profile）</h4><p>除了注册必填信息之外，我们还有一部分关于您更细致描述的信息，例如姓名、生日、家庭住址、所在学校等等，您可以选择填写与否。但是，您一定知道，您的资料越完整，您提供的信息越丰富，就越有可能获得更多的实习机会和相关服务。</p><h4>3. 联系人的信息</h4><p>当您邀请您的朋友加入实习圈时，您需要填写对方的姓名，手机号或是邮箱地址。这些信息仅会被用来给您的联系人发出邀请或是其他信息之用。您也可以自行为您的联系人填加一些个人信息，但是实习圈保证这些信息仅会被您看到。您为您联系人所填信息也符合此隐私条款。</p><h4>4. 非个人资料辨别</h4><p>我们除了向您收集个人资料以便为您提供服务以外，还可能通过您的IP地址收集一些非个人隐私的统计资料，使我们能够进一步改善实习圈的服务。例如，当您浏览一个网页时，此网址、当时的时间、您所使用的浏览器性质、给您提供接入服务的ISP等，都会被自动记录下来。</p><h4>5. COOKIE</h4><p>Cookie 是指从网络服务器发送到您的浏览器，并储存到电脑硬盘上的少量数据，通常包括一些特殊标识符，是用来记录您的使用者 ID。您以根据自己的喜好，设定接收所有 cookies，拒收所有 cookies ，或在设定 cookie 时得到通知。然而您必须在开启您的 cookies时才能使用实习圈所提供的服务。</p><h4>二、信息公开与共享</h4><p>用户的信息将会被分类分级别的，按照用户个人的意愿展示给其联络人。实习圈不会将您的个人资料提供给任何人。但以下情况除外：</p><p>(1) 已获得用户的明确授权；<br />(2) 根据有关法律法规的要求或按照法院或相关政府部门的要求；<br />(3) 为维护实习圈的合法权益；<br />(4) 为维护实习圈的用户和社会公众的合法权益；<br />(5) 实习圈认为有必要的其他情况。</p><h4>三、信息的更新和删除</h4><p>为了使您能和您的联系人保持长久的联系，在您的个人资料有变动的情况下，您可以更新和修改您的个人资料已使其有效。您在任何时候都能非常容易地使用您的注册名与密码登录本网站以修改或删除您的个人资料及档案。</p><h4>四、保护您的隐私</h4><p>我们将采取严格的措施保护您的隐私，确保您的隐私权不受任何侵犯。只要您提供给我们任何个人信息，我们都会采取有效的手段保护您的信息（法律或政府的强制性规定不在此限）。</p><h4>五、更新隐私条款</h4><p>实习圈可能会对隐私权政策进行修改。如果在使用用户个人信息政策方面有大幅度修改时，我们会通过电子邮件通知您。</p><p>&nbsp;</p><p>如果你对此隐私政策有任何疑问或建议，请通过以下方式联系我们：<a href="mailto:54intern@54intern.com">54intern@54intern.com</a> .</p>',
      'format' => 'fitered_html_with_editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = '2';
    $pane->locks = array();
    $display->content['new-4'] = $pane;
    $display->panels['main'][2] = 'new-4';
    $pane = new stdClass();
    $pane->pid = 'new-5';
    $pane->panel = 'main';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = '1';
    $pane->access = array(
      'plugins' => array(
        0 => array(
          'name' => 'path_visibility',
          'settings' => array(
            'visibility_setting' => '1',
            'paths' => 'siteinfo/service-agreement',
          ),
          'context' => 'empty',
          'not' => FALSE,
        ),
      ),
    );
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '服务协议',
      'body' => '<p>欢迎访问实习圈网站，本协议在您开始使用网站，并成为网站的会员时即产生法律效力。实习圈可能更新协议内容，并通过电子邮件来通知用户。更新结果将在实习圈通知之日起生效。协议包括实习圈的网站内容使用政策、实习圈隐私政策。您在使用实习圈提供的各项服务之前，应仔细阅读本服务公约。如您不同意本服务公约及/或随时对其的修改，您可以主动取消实习圈提供的服务；您一旦使用实习圈服务，即视为您已了解并完全同意本服务公约各项内容，并成为实习圈用户（以下简称&ldquo;用户&rdquo;）。</p><h4>用户的注册和资料管理义务</h4><p>您同意以下事项∶<br />依本服务注册表之提示提供您本人真实的资料（以下简称&ldquo;登记资料&rdquo;）；随时更新登记资料，确保其为真实资料。<br />若您提供任何错误、不实或具误导性的资料；或者实习圈有理由怀疑前述资料为错误、不实或具误导性的，实习圈有权暂停或终止您的帐号，并拒绝您于现在和未来使用本服务之全部或任何部分。</p><h4>密码和帐号：</h4><p>用户帐号、密码及安全完成本服务的登记程序之后，您将选择一个密码及帐号。维持密码及帐号的机密安全，是您的责任。您应对所有用您的密码及帐号的活动负完全的责任。您同意：<br />您的密码或帐号遭到未获授权的使用，或者发生其他任何安全问题时，您将立即通知实习圈；<br />每次使用完毕，用安全退出把您的帐号关掉。如您未能依前述规定行事，对于任何人利用该密码及帐号所进行的任何行为，您应负完全的责任。对于因此而产生的任何损失或损害，实习圈无法也不承担任何责任。</p><h4>用户行为</h4><p>实习圈网站是一个纯粹以高校学生实习交流为主的网站，不适宜发表政治实事评论；<br />您理解并同意实习圈检查并删除任何不恰当、违法、侵害、中伤、胁迫以及违反协议的其它内容、信息、图片或资料；<br />您要对站上公布或展示以及您向其他会员传送的内容负责；<br />网站公共区域发布信息时，您自动同意协议，并表明您有权同意网站拥有不可撤销的、永久性的、非独占许可的、全部付费、世界范围内的使用、复制、处理、展示和传播此类信息与内容的权力。</p><p>用户应同意遵守中华人民共和国各项法律、法规；遵守中国有关互联网络的各项法规、条例。并且不会利用本服务进行任何违法或不正当的活动。</p><p>实习圈保留对此类行为进行调查，并采取包括删除不恰当信息及取消违法本声明会员的资格在内的行动的权利。此类活动包括但不限于下列行为∶</p><p>公然冒犯在线用户，例如宣扬种族歧视、种族偏见、种族仇恨或有对某些用户造成伤害的其它言论。<br />发布激怒或有可能激怒他人的语言。<br />传播垃圾邮件、连锁信件或滥发邮件。<br />宣扬您已知为错误或有可能误导他人的言论，以及侮辱、胁迫、淫秽、诽谤、有损他人名誉的言论。<br />推广非法产品或未经授权公布他人受版权保护的作品，例如提供盗版计算机程序及相关产品，提供窃取受版权保护的产品的信息，或提供盗版音乐及音乐产品。<br />传播受限制、受密码保护以及隐藏的网页（即没有链接到其它网页或无法从其它网页进入的网页）或图片信息。<br />传播任何类型的色情或淫秽内容。</p><p>传播涉及未成年人的色情及暴力内容，或向他人索取任何未成年人的个人信息。<br />提供引导他人从事非法活动，例如制造或购买武器、侵犯他人隐私以及提供或制造计算机病毒的信息。<br />出于商业或非法目的向其他用户索取密码或个人信息，并在未获网站书面许可的情况下出售上述信息或将其用于比赛、搏彩、交易、广告以及传销等商业活动；</p><h4>会员纠纷</h4><p>您只需为您与实习圈其他会员之间的相互行为负责。实习圈保留权利，但没有责任监督您和其他会员之间的纠纷。</p><h4>国际使用之特别警告</h4><p>您已了解国际互联网的无国界性，同意遵守当地所有关于网上行为及内容之法律法规。您特别同意遵守有关从中国或您所在国家或地区输出信息之传输的所有适用法律法规。</p><h4>用户的隐私保护</h4><p>实习圈绝对尊重用户的个人隐私权，实习圈绝不会公开、编辑、透漏用户的任何资料给第三方，除非有法律和政府的强制规定或是用户本人的同意。</p><h4>免责声明与拒绝提供担保</h4><p>您明确了解并同意:</p><p>（1） &ldquo;实习圈&rdquo;不保证以下事项∶<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 本服务符合您的要求，<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 本服务不受干扰、及时提供、安全可靠或不会出错，<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 使用本服务取得之结果正确可靠，<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 您经由本服务购买或取得之任何产品、服务、资讯或其他信息符合您的期望，<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 软件中任何错误都得到更正。</p><p>（2）是否使用本服务下载或取得任何资料应由您自行考量且自负风险，因任何资料之下载而导致的您电脑系统之任何损坏或数据流失等后果，由您自行承担。</p><p>（3）您自实习圈或经由本服务取得的任何建议或信息，无论是书面或口头形式，除非本服务条款有明确规定，将不构成本服务条款以外之任何保证。</p><h4>责任限制</h4><p>除去上述条款所规定的权限，实习圈在任何情况下都不会因任何间接、相应、典型、偶发、特殊或惩罚性的损失赔偿，包括因使用网站或服务引起的经济损失向用户或第三方负责，即使实习圈已经获悉有可能发生类似结果。</p><h4>赔偿</h4><p>由于您通过服务提供、公布或传送的内容及 / 或您违反本服务协议及 / 或您侵害他人任何权利因而衍生或导致任何第三人提出任何索赔或请求，包括合理的律师费时，您同意赔偿实习圈及其员工的损失，并使其免受损害。</p><h4>用户协议及服务之修改</h4><p>实习圈有权在必要时修改用户协议，协议一旦发生变动，将会通过电子邮件或网站内部消息通知用户并提示修改内容。如果不同意所改动的内容，用户有权停止使用网络服务。如果用户继续使用网络服务，则视为接受服务条款的变动。<br />实习圈保留修改或中断服务的权利。对于任何网络服务的修改、中断或终止而造成的任何损失，实习圈无需对用户或第三方承担任何责任。</p><h4>终止服务</h4><p>用户或实习圈可根据实际情况中断服务。实习圈不需对任何个人或第三方负责而中断服务。用户若反对任何服务条款的建议或对后来的条款修改有异议，或对实习圈服务不满，用户只有以下的追索权：<br />（1）不再使用实习圈服务。<br />（2）结束用户使用实习圈服务的资格。</p><p>（3）通告实习圈停止该用户的服务。<br />结束用户服务后，用户使用实习圈服务的权利马上中止。从该时起，实习圈不再对用户承担任何义务。</p><h4>法律依据</h4><p>本服务公约及您与实习圈之关系，均受到中华人民共和国法律管辖。您和实习圈一致同意有关本协议以及使用实习圈的服务产生的争议交由仲裁解决，但是实习圈有权选择采取诉讼方式，并有权选择受理该诉讼的有管辖权的法院。若有任何服务条款与法律相抵触，那这些条款将按尽可能接近的方法重新解析，而其它条款则保持对用户产生法律效力和影响。</p><h4>其它规则</h4><p>您在成为实习圈的会员时即被视为同意并完全接受协议。如果实习圈无法履行或执行本服务条款的权利或规定，不构成实习圈放弃这些权利或规定。如果协议中的任何规定未被正确执行，协议中的其它规定仍然有效。协议中的段落标题只是为了阅读方便，不具有任何法律或契约效果。</p>',
      'format' => 'fitered_html_with_editor',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = '3';
    $pane->locks = array();
    $display->content['new-5'] = $pane;
    $display->panels['main'][3] = 'new-5';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-2';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_about_us'] = $page;

  return $pages;

}
