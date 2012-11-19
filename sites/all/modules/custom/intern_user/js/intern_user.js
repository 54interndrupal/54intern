

// Callback function from Ajax request
function _authcache_intern_user_resume_status(vars) {
    jQuery("#resume-block .resume-status").html(vars);
}

function authcacheInternUserResumeStatusInit() {
//    alert(3);
    ajaxJson = {
        // The name of the function to call, both for ajax_authcache.php and
        // this file (see function above). The cookie value will change if
        // the user updates their block (used for max_age cache invalidation)
        'intern_user_resume_status' : '',

        // Makes browser cache the Ajax response to help reduce server resources
        'max_age' : 0
    }
    // Perform independent Authcache ajax request
    Authcache.ajaxRequest(ajaxJson);
}

jQuery(function() {authcacheInternUserResumeStatusInit(); })

