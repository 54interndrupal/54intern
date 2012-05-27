jQuery(document).ready(function() {
	jQuery('#search ul.option li.selected').append(' ▼');
});

// 企业用户登录区块
jQuery(document).ready(function() {
	jQuery('#shixiquan-companylogin-form a:eq(0)').addClass('qiye-denglu-wangjimima').after('<br/>');
	jQuery('#shixiquan-companylogin-form input#edit-submit--3').after('<br/>');
	jQuery('#shixiquan-companylogin-form a:eq(1)').addClass('qiyeyonghuzhuce');
});

// 个人用户注册对话框

jQuery(document).ready(function(){
	jQuery('span#geren-zhuce a').click(function(){
		jQuery('.my-ui-dialog').load('user/userregister #userreg-user-register-form').dialog({
			title:'个人用户注册',
			width:340,
			position:['center',60],
			resizable: false
			});
	});
});

// 消息对话框
/*
jQuery(document).ready(function(){
	jQuery('div#messages').dialog({
		title:'您有新消息',
		position:['center',60],
		resizable: false
		});
})
*/
//热门社团view定制

jQuery(document).ready(function() {
	jQuery('div.field-name-industry label').text('行业：');
});

// 企业活动管理tab

jQuery(document).ready(function() {
	jQuery('form#views-form-company-events-panel-pane-2 th.views-field-title').text('全选');
})

// 企业详细页面  企业首页 active 补丁

jQuery(document).ready(function() {
	jQuery('body.node-type-company ul#company-center-tabs a:eq(0)').attr('class','active');
})
