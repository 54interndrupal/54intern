// Callback function from Ajax request
function _authcache_intern_company_flags(vars) {
//    alert(vars['company_info_flags']);
    jQuery("#company_info_ops").html(vars['company_info_flags']);
    Drupal.behaviors.flagLink.attach();
}

function authcacheInternCompanyFlagsInit() {
//    alert(1);
    ajaxJson = {
        'intern_company_flags[companyId]' : jQuery("#companyId").val(),
        'max_age' : null
    }
    // Perform independent Authcache ajax request
    Authcache.ajaxRequest(ajaxJson);
}

jQuery(function() {
    authcacheInternCompanyFlagsInit();

})

