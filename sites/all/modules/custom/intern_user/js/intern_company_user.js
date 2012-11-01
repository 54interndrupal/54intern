// Callback function from Ajax request
function _authcache_intern_company_user_info(vars) {
    jQuery(".pane-intern-user-company-user-info .pane-content").html(vars['company_user_info']);
}

function authcacheInternCompanyUserInfoInit() {
    ajaxJson = {
        // The name of the function to call, both for ajax_authcache.php and
        // this file (see function above). The cookie value will change if
        // the user updates their block (used for max_age cache invalidation)
        'intern_company_user_info' : '',

        // Makes browser cache the Ajax response to help reduce server resources
        'max_age' : 0
    }
    // Perform independent Authcache ajax request
    Authcache.ajaxRequest(ajaxJson);
}

jQuery(function() {authcacheInternCompanyUserInfoInit(); })

