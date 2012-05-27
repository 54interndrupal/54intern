if (Drupal.jsEnabled) {
	$(document).ready(function(){
			
		$('#edit-mail-check-button').click(function () {
			//alert(window.location.host);
			var mailField = $("#edit-mail");
			var requestUrl = 'http://'+window.location.host+'/user/reg/isunique';
			//alert(requestUrl);
			$.ajax({
				url:requestUrl,
				dataType: 'json',
				data: {mail: mailField.val()},
				beforeSend: function() {
          $("#mail-check-message")
            .removeClass('mail-check-message-accepted')
            .removeClass('mail-check-message-rejected')
            .addClass('mail-check-message-progress')
            .html('请等待，正在检查邮箱地址的有效性')
            .show();
        },
				success: function(ret){
          if(ret['allowed']){
            $("#mail-check-message")
              .removeClass('mail-check-message-progress')
              .addClass('mail-check-message-accepted');
            
            mailField
              .removeClass('error');
          }
          else {
            $("#mail-check-message")
              .removeClass('mail-check-message-progress')
              .addClass('mail-check-message-rejected');
          }
          $("#mail-check-message")
            .removeClass('mail-check-message-progress')
            .html(ret['msg']);
        }
			});
			
			return false;
			
		});
		$('#edit-image-submit').click(function () {
			//alert($('#edit-pass').val());
			//alert($('#edit-pass-conf').val());
			//return false;
			if($('#edit-legal-agreement').attr("checked")==false){
				alert('您必须同意《嘉特在线交易条款》和《嘉特在线用户使用条款》');
				//alert($('#edit-legal-agreement').attr("checked"));
				$('#edit-legal-agreement').focus();
				
				return false;
			}
			if($('#edit-pass').val() != $('#edit-pass-conf').val()){
				alert('确认密码必须与输入密码一致');
				//alert($('#edit-legal-agreement').attr("checked"));
				$('#edit-pass-conf').focus();
				$('#edit-pass').focus();
				
				
				return false;
			}
			
		});
	
	});
}