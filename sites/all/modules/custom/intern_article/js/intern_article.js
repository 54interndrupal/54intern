// Callback function from Ajax request
function _authcache_intern_article_flags(vars) {
//    alert(vars['article_flags']);
    jQuery("#article_ops").html(vars['article_flags']);
    Drupal.behaviors.flagLink.attach();
}

function authcacheInternArticleFlagsInit() {
    ajaxJson = {
        'intern_article_flags[articleId]' : jQuery("#articleId").val(),

        'max_age' : 0

    }
    // Perform independent Authcache ajax request
    Authcache.ajaxRequest(ajaxJson);
}

jQuery(function() {authcacheInternArticleFlagsInit(); })

