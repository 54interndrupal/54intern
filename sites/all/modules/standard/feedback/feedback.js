(function ($) {

    /**
     * Attach auto-submit to admin view form.
     */
    Drupal.behaviors.feedbackAdminForm = {
        attach:function (context) {
            $('#feedback-admin-view-form', context).once('feedback', function () {
                $(this).find('fieldset.feedback-messages :input[type="checkbox"]').click(function () {
                    this.form.submit();
                });
            });
        }
    };

    /**
     * Attach collapse behavior to the feedback form block.
     */
    Drupal.behaviors.feedbackForm = {
        attach:function (context) {
            $('#block-feedback-form', context).once('feedback', function () {
                var $block = $(this);
                $block.find('span.feedback-link')
                    .toggle(function () {
                        Drupal.feedbackFormToggle($block, false);
                    },
                    function () {
                        Drupal.feedbackFormToggle($block, true);
                    }
                );
                $block.find('form').hide();
                $block.show();
            });


        }
    };

    /**
     * Re-collapse the feedback form after every successful form submission.
     */
    Drupal.behaviors.feedbackFormSubmit = {
        attach:function (context) {
            var $context = $(context);
            if (!$context.is('#feedback-status-message')) {
                return;
            }
            // Collapse the form.
            $('#block-feedback-form .feedback-link').click();

            $context.fadeOut('fast', function () {
                    $context.remove();
            });

        }
    };

    /**
     * Collapse or uncollapse the feedback form block.
     */
    Drupal.feedbackFormToggle = function ($block, enable) {
        if (!enable) {
            $block.find("span.feedback-link").toggleClass("closed");
            $block.find('form').slideToggle(20);
        } else {
            $block.find('form').slideToggle(20, function () {
                $block.find("span.feedback-link").toggleClass("closed");
            });
        }
        if (enable) {
            $('#feedback-form-toggle', $block).html('');
        }
        else {
            $('#feedback-form-toggle', $block).html('[ X ] 网站反馈');
        }
    };
})(jQuery);
