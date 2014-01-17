// Callback function from Ajax request
function _authcache_intern_review_flags(vars) {
//    alert(vars['review_info_flags']);
      var reviewId = vars['review_id'];
    jQuery("#review_info_ops_"+reviewId).append(vars['review_info_flags']);
    Drupal.behaviors.flagLink.attach();
}

function authcacheInternreviewFlagsInit() {

     jQuery("input[name='reviewId']").each(function(){
        var reviewId = jQuery(this).val();
        ajaxJson = {
            'intern_review_flags[reviewId]' : reviewId,
            'max_age' : null

        }
        // Perform independent Authcache ajax request
        Authcache.ajaxRequest(ajaxJson);
    })
}

jQuery(function() {authcacheInternreviewFlagsInit(); })

