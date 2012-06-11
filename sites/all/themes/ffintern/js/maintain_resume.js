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

    });
})(jQuery);