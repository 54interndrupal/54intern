(function ($) {
    $(document).ready(function () {
        $("#user-basic-info-tab").click(function () {
            $("#user-basic-info-tab").addClass("active");
            $("#user-basic-info").show();
            $("#user-attached-resume-tab").removeClass("active");
            $("#user-attached-resume").hide();
            $("#user-apply-letter-tab").removeClass("active");
            $("#user-apply-letter").hide();
        });
        $("#user-attached-resume-tab").click(function () {
            $("#user-attached-resume-tab").addClass("active");
            $("#user-attached-resume").show();
            $("#user-basic-info-tab").removeClass("active");
            $("#user-basic-info").hide();
            $("#user-apply-letter-tab").removeClass("active");
            $("#user-apply-letter").hide();
        });
        $("#user-apply-letter-tab").click(function () {
            $("#user-apply-letter-tab").addClass("active");
            $("#user-apply-letter").show();
            $("#user-attached-resume-tab").removeClass("active");
            $("#user-attached-resume").hide();
            $("#user-basic-info-tab").removeClass("active");
            $("#user-basic-info").hide();
        });

        $("#resume-check").modal('hide');
        $("#resume-node-form .form-submit").click(function(){
            if($(".file-icon",$(".file")).size()==0){
                $("#resume-check .modal-body").html('<p>您还没有上传简历，任然无法申请职位， <a href="javascript:continueUploadResume()">立刻上传</a> ? <a href="javascript:continueSave()">稍后再说</a>。</p>');
                $("#resume-check").modal('show');
                return false;
            }
            if($("#edit-field-apply-letters-und-0-field-letter-body-und-0-value").val()==''){
                $("#resume-check .modal-body").html('<p>您还没有填写求职信，可能影响您的申请职位，<a href="javascript:continueWriteMail()">马上填写</a> ? <a href="javascript:continueSave()">稍后再说</a>。</p>');
                $("#resume-check").modal('show');
                return false;
            }
        })


    });
})(jQuery);

function continueUploadResume(){
    jQuery("#user-attached-resume-tab").click();
    jQuery('#resume-check').modal('hide');
}

function continueWriteMail(){
    jQuery("#user-apply-letter-tab").click();
    jQuery('#resume-check').modal('hide');
}

function continueSave(){
    jQuery('#resume-node-form').submit();
}