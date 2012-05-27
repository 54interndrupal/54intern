//54intern.com javascript file 
jQuery.noConflict();
(function($) { 
$(function() {

    //advanced search
    $('div.advanced-search .adv-option a').toggle(function(){
      $(this).html('减少搜索条件');
      $(this).parents('div.advanced-search').find('#adv-option').slideDown();
      $(this).addClass('show');
      return false;
    }, function(){
      $(this).html('更多搜索条件');
      $(this).parents('div.advanced-search').find('#adv-option').slideUp();
       $(this).removeClass('show');
      return false;
    });
    
    
     /*===========3月2日 新增的在这下面==========*/
    
  function mycarousel_initCallback(carousel){
    carousel.clip.hover(function() {
        carousel.stopAuto();
    }, function() {
        carousel.startAuto();
    });
  };
  
  if ($('#company-photos').length > 0){
    $('#company-photos .block-content ul ').jcarousel({
      //auto:3,
      //initCallback:mycarousel_initCallback
    });
  };
 
  $(".company-photos-photo-link").colorbox({
	rel:'company-photos-photo-link', 
	speed:10,
	opacity : 0.5,
	slideshow:true
	});

    
  /*===========3月5日 新增的在这下面==========*/
    //admin-list checkbox
    $('.admin-list input:checkbox').removeAttr('checked');
    $('.admin-list .views-row .widget input:checkbox').click(function(){
      if ( $(this).is(':checked') == true ) {
        $(this).parents('.views-row').addClass('selected');
      } else {
        $(this).parents('.views-row').removeClass('selected');
      };
      if ($(this).parents('.admin-list').find('.views-row .widget input:checkbox:not([checked])').length == 0){
        $(this).parents('.admin-list').find('.operation input:checkbox').attr('checked','checked');
      } else {
        $(this).parents('.admin-list').find('.operation input:checkbox').removeAttr('checked');
      };
    });
    $('.admin-list .operation input:checkbox').click(function(){
      if ( $(this).is(':checked') == true ) {
        $(this).parents('.admin-list').find('.views-row').addClass('selected');
        $(this).parents('.admin-list').find('.views-row .widget input:checkbox').attr('checked','checked');
      } else {
         $(this).parents('.admin-list').find('.views-row').removeClass('selected');
        $(this).parents('.admin-list').find('.views-row .widget input:checkbox').removeAttr('checked');
     };
    });
       
   /*===========3月29日 新增的在这下面==========*/

    
    
});
})(jQuery);