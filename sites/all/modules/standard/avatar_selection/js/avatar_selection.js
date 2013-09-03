(function ($) {
  function radio_button_handler() {
    // handle radio buttons
    $('div.user-avatar-select input.form-radio').hide();
    $('div.user-avatar-select img').hover(
      function(){
        $(this).addClass("avatar-hover");
      },
      function(){
        $(this).removeClass("avatar-hover");
      }
    );
  }

  function image_click_handler() {
    $('div.user-avatar-select img').bind("click", function(){
        $("div.user-avatar-select img.avatar-select").removeClass("avatar-select");
        $("div.user-avatar-select .user-avatar-select").attr("checked", "");


      $(this).addClass("avatar-select");
      $(this).parent().parent().children("input").attr("checked", "checked");
    });
  }

  Drupal.behaviors.avatarSelectionRadioHandler = {
    attach: function (context) {
      radio_button_handler();
      image_click_handler();
    }
  }
})(jQuery);

