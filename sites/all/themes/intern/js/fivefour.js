//54intern.com javascript file 
jQuery.noConflict();
(function($) { 
$(function() {
    
    //search select
    $('#search .block-content form').prepend('<ul class="option"></ul>');
    $('#search select option').each(function(){
      $('#search ul.option').append('<li>' + $(this).html() +'</li>');
    });
    $('#search ul.option li').each(function(){
      if ($(this).html() == $('#search select option:selected').html()) {
        $(this).addClass('selected');
      }
      $(this).click(function(){
        $(this).parents('ul').toggleClass('active');
        $(this).siblings('li').removeAttr('class');
        $(this).addClass('selected');
        
        $('#search select option').each(function(){
          if ($(this).html() == $('#search ul.option li.selected').html()) {
            $(this).siblings('option').removeAttr('selected');
            $(this).attr('selected','selected');
          }        
        });
      });
    });
    $('#search ul.option').hover(function(){
    },function(){
      $(this).removeClass('active');
    });
    
    //font-page tabs
    $('body.node-type-group #forum-block').before('<div class="tabs"><div class="tabs-title"></div></div>');
    $('body.node-type-group #forum-block').appendTo('div.tabs');
    $('body.node-type-group #events-block').appendTo('div.tabs');
    $('div.tabs h2.block-title').appendTo('div.tabs div.tabs-title');
    $('div.tabs h2.block-title:first').addClass('active');
    $('div.tabs div.block:first').addClass('active');
    $('div.tabs .tabs-title h2').each(function(index){
      //$(this).hover(function(){
	  $(this).click(function(){
        $(this).siblings('h2').removeClass('active');
        $(this).addClass('active');
        $(this).parents('div.tabs').find('div.block').removeClass('active');
        $(this).parents('div.tabs').find('div.block').eq(index).addClass('active');
      },function(){});
    });
	
    //user center common tabs
    $('.page-user div.tabs').each(function(){
      $(this).prepend('<div class="tabs-title"></div>');
      $(this).find('h2.block-title').appendTo($(this).find('div.tabs-title'));
      $(this).find('div.tabs-title h2').each(function(index){
        //$(this).hover(function(){
		$(this).click(function(){
          $(this).siblings('h2').removeClass('active');
          $(this).addClass('active');
          $(this).parents('div.tabs').find('div.block').removeClass('active');
          $(this).parents('div.tabs').find('div.block').eq(index).addClass('active');
        },function(){});
      });
    });  
	
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
    	/* 
 	$(".company-photos-photo-link").click(function(event) {

		
		//var bl_c = $(".bl_c").offset();
   // event.preventDefault();
    $.colorbox({
		  rel:'company-photos-photo-link',
			slideshow:true,
		  href:$(this).attr('href'),
			speed:10,
			//slideshow:true,
			opacity : 0.5,
     // iframe: true,
			close: 'close'
     // overlayClose: false
    });  
	
    return false;		
  });     
    
  */
    
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