

// Callback function from Ajax request
function _authcache_zpuser(vars) {
    alert(vars);
    $("#resume-block .resume-status").html(vars);
}

function zpuserInit() {
    ajaxJson = {
        // The name of the function to call, both for ajax_authcache.php and
        // this file (see function above). The cookie value will change if
        // the user updates their block (used for max_age cache invalidation)
        'zpuser' : '',

        // Makes browser cache the Ajax response to help reduce server resources
        'max_age' : 3600
    }

    // Perform independent Authcache ajax request
    Authcache.ajaxRequest(ajaxJson);
}

jQuery(function() { zpuserInit(); alert(2);})

