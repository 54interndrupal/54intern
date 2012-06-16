/**
 * Created with JetBrains PhpStorm.
 * User: Edison
 * Date: 12-5-25
 * Time: 下午3:03
 * To change this template use File | Settings | File Templates.
 */
(function ($) {
    Drupal.behaviors.userLogin = {
        attach:function (context) {
            if ($("#user-login-header").size() > 0) {
                if ($("div.modal-header .user-login-header").size() == 0) {
                    $("div.modal-header").addClass("colored").append($('#user-login-header'));
                } else {
                    $("#user-login-header").hide();
                }
            }
        }
    }

})(jQuery);

