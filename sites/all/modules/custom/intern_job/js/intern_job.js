// Callback function from Ajax request
function _authcache_intern_job_flags(vars) {
//    alert(vars['job_flags']);
    jQuery("#job_ops").html(vars['job_flags']);
    jQuery("#company_info_ops").html(vars['company_info_flags']);
    Drupal.behaviors.flagLink.attach();
}

function authcacheInternJobFlagsInit() {
    ajaxJson = {
        // The name of the function to call, both for ajax_authcache.php and
        // this file (see function above). The cookie value will change if
        // the user updates their block (used for max_age cache invalidation)
        'intern_job_flags[jobId]' : jQuery("#jobId").val(),
        'intern_job_flags[companyId]' : jQuery("#companyId").val(),

        'max_age' : 0

    }
    // Perform independent Authcache ajax request
    Authcache.ajaxRequest(ajaxJson);
}

jQuery(function() {authcacheInternJobFlagsInit(); })

