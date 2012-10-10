/**
 * @file
 *
 * Pagerer jquery scripts.
 *
 */
(function ($) {

Drupal.behaviors.pagerer = {

  attach: function(context, settings) {

    /**
     * 'pagerer-page' input box event binding
     */
    $('.pagerer-page', context)
    .ready().each(function(index) {
      this.pagererState = eval('(' + $(this).attr('name') + ');');
      // Adjust width of the input box.
      $(this).width(String(this.pagererState.total).length + 'em');
    })
    .bind('focus', function(event) {
      this.select();
      $(this).addClass('pagerer-page-has-focus');
    })
    .bind('blur', function(event) {
      $(this).removeClass('pagerer-page-has-focus');
    })
    .bind('keydown', function(event) {
      switch(event.keyCode) {
        case 13:
        case 10:
          // Return key pressed.
          var newPage;
          // Determine destination page.
          if (this.pagererState.display == 'pages') {
            newPage = isNaN($(this).val()) ? 0 : parseInt($(this).val()) - 1;
            if (newPage < 0) {
              newPage = 0;
            } else if (newPage >= this.pagererState.total) {
              newPage = this.pagererState.total - 1;
            }
          } else {
            var item = isNaN($(this).val()) ? 0 : parseInt($(this).val()) - 1;
            if (item < 0) {
              item = 0;
            } else if (item >= this.pagererState.total) {
              item = this.pagererState.total - 1;
            }
            newPage = parseInt(item / parseInt(this.pagererState.interval));
          }
          pagererRelocate(this, this, this.pagererState.root, this.pagererState.path.replace(/pagererpage/, newPage));
          event.stopPropagation();
          event.preventDefault();
          return false;
        case 27:
          // Escape.
           $(this).val(this.pagererState.current);
          return false;
        case 38:
          // Up.
          pagererOffsetWidgetValue(this, -1);
          return false;
        case 40:
          // Down.
          pagererOffsetWidgetValue(this, 1);
          return false;
        case 33:
          // Page up.
          pagererOffsetWidgetValue(this, -5);
          return false;
        case 34:
          // Page down.
          pagererOffsetWidgetValue(this, 5);
          return false;
        case 35:
          // End.
           $(this).val(this.pagererState.total);
          return false;
        case 36:
          // Home.
           $(this).val(1);
          return false;
      }
    });

    /**
     * 'pagerer-slider' jQuery UI slider event binding.
     */
    var actionInterval = 0;
    $('.pagerer-slider', context)
    .ready().each(function(index) {
      this.pagererState = eval('(' + $(this).attr('id') + ');');

      // Create slider.
      var sliderBar = $(this);
      sliderBar.slider({ min : 1, range : 'min', animate: true });
      var sliderHandle = $(this).find('.ui-slider-handle');

      // Adjust slider handle width and current page.
      sliderHandle
        .width((String(this.pagererState.total).length + 2) + 'em')
        .css('height', Math.max(sliderHandle.height(), 16) + 'px')
        .css('line-height', Math.max(sliderHandle.height(), 16) + 'px')
        .css('margin-left', -sliderHandle.width() / 2)
        .text(this.pagererState.current)
        .bind('blur', function(event) {
          if (actionInterval) {
            clearTimeout(actionInterval);
          }
          var sliderBar = $(this).parent();
          if (!sliderBar[0].pagererState.spinning) {
            sliderBar[0].pagererState.spinning = true;
            sliderBar.slider('option', 'value', sliderBar[0].pagererState.current);
            $(this).text(sliderBar[0].pagererState.current);
            sliderBar[0].pagererState.spinning = false;
          }
        });

      // Adjust slider bar options and width.
      sliderBar
        .slider('option', 'max', this.pagererState.total)
        .slider('option', 'value', this.pagererState.current)
        .slider('option', 'step', this.pagererState.interval)
        .width((this.pagererState.quantity * 3) + 'em')
        .css('margin-left', sliderHandle.width() / 2)
        .css('margin-right', sliderHandle.width() / 2);

      var pixelsPerStep = sliderBar.width() / (this.pagererState.total / this.pagererState.interval);
      // If autodetection of navigation action, determine whether to
      // use tickmark or timelapse.
      if (this.pagererState.action == 'auto') {
        if (pixelsPerStep > 3) {
          this.pagererState.action = 'timelapse';
        } else {
          this.pagererState.action = 'tickmark';
        }
      }
      // If autodetection of navigation icons, determine whether to
      // hide icons.
      if (this.pagererState.icons == 'auto' && pixelsPerStep > 3) {
        $(this).parents('.pager').find('.pagerer-slider-control-icon').parent().hide();
      }
      // Add indication to click on the tickmark to start page
      // relocation.
      if (this.pagererState.action == 'tickmark') {
        var title = $(this).attr('title');
        $(this).attr('title',  title + Drupal.t(' Then, click on the tickmark.'));
      }
    })
    .bind('slide', function(event, ui) {
      if (actionInterval) {
        clearTimeout(actionInterval);
      }
      $(this).find('.ui-slider-handle').text(ui.value);
    })
    .bind('slidechange', function(event, ui) {

      var sliderHandle = $(this).find('.ui-slider-handle');
      sliderHandle.text(ui.value);

      // If currently sliding the handle via navigation icons,
      // do nothing.
      if (this.pagererState.spinning) {
        return false;
      }

      // Determine target page.
      var currVal = $(this).slider('option', 'value');
      var newPage;
      if (this.pagererState.display == 'pages') {
        newPage = currVal - 1;
      } else {
        newPage = parseInt(currVal / parseInt(this.pagererState.interval));
      }

      // Relocate immediately to target page if no
      // tickmark/timelapse confirmation required.
      if (this.pagererState.action == 'timelapse' && this.pagererState.timelapse == 0) {
        sliderHandle.append("<div class='pagerer-slider-handle-icon'/>");
        var sliderHandleIcon = sliderHandle.find('.pagerer-slider-handle-icon');
        pagererRelocate(this, sliderHandleIcon, this.pagererState.root, this.pagererState.path.replace(/pagererpage/, newPage));
        return false;
      }

      // Otherwise, add a tickmark or clock icon to the handle text,
      // to be clicked to activate page relocation.
      var sliderBar = $(this);
      sliderHandle.text(ui.value + ' ');
      if (this.pagererState.action == 'timelapse') {
        sliderHandle.append("<div class='pagerer-slider-handle-icon throbber'/>");
      } else {
        sliderHandle.append("<div class='pagerer-slider-handle-icon ui-icon ui-icon-check'/>");
      }

      // Bind page relocation to mouse clicking on the icon.
      var sliderHandleIcon = sliderHandle.find('.pagerer-slider-handle-icon');
      sliderHandleIcon.bind('mousedown', function(event) {
        if (actionInterval) {
          clearTimeout(actionInterval);
        }
        // Remove icon.
        $(sliderBar[0]).find('.pagerer-slider-handle-icon').removeClass('throbber');
        // Relocate.
        pagererRelocate(sliderBar[0], sliderHandleIcon, sliderBar[0].pagererState.root, sliderBar[0].pagererState.path.replace(/pagererpage/, newPage));
        return false;
      });

      // Bind page relocation to timeout of timelapse.
      if (this.pagererState.action == 'timelapse') {
        if (actionInterval) {
          clearTimeout(actionInterval);
        }
        actionInterval = setTimeout(function(){
          // Remove icon.
          $(sliderBar[0]).find('.pagerer-slider-handle-icon').removeClass('ui-icon').removeClass('throbber');
          // Relocate.
          pagererRelocate(sliderBar[0], sliderHandleIcon, sliderBar[0].pagererState.root, sliderBar[0].pagererState.path.replace(/pagererpage/, newPage));
          return false;
        }, this.pagererState.timelapse);
      }

    });

    /**
      * pagerer-slider control icons event binding
      *
      * The navigation icons serve as an helper for the slider positioning,
      * to fine-tune the selection. Once mouse is pressed on an icon, the
      * slider handle is moved +/- one value. If mouse is kept pressed, the
      * slider handle will move continuosly. When mouse is released or moved
      * away from the icon, sliding will stop and the handle status will be
      * processed through slider 'slidechange' event triggered by the
      * pagererOffsetSliderValue() function.
      */
    var spinInterval = 0;
    var spinIdleCycles = 0;
    // Spin events.
    $('.pagerer-slider-control-icon', context)
    .bind('mousedown', function(event) {
      if (actionInterval) {
        clearTimeout(actionInterval);
      }
      var slider = $(this).parents('.pager').find('.pagerer-slider');
      slider[0].pagererState.spinning = true;
      var offset = $(this).hasClass('ui-icon-circle-minus') ? -1 : 1;
      pagererOffsetSliderValue(slider, offset);
      spinInterval = setInterval(function(){
        spinIdleCycles++;
        if (spinIdleCycles > 10) {
          pagererOffsetSliderValue(slider, offset);
        }
      }, 50);
    })
    .bind('mouseup mouseleave', function() {
      var slider = $(this).parents('.pager').find('.pagerer-slider');
      if (slider[0].pagererState.spinning) {
        spinIdleCycles = 0;
        clearInterval(spinInterval);
        slider[0].pagererState.spinning = false;
        pagererOffsetSliderValue(slider, 0);
        slider.find('.ui-slider-handle').focus();
      }
    });


    /**
     * Helper functions
     */

    /**
     * Relocate client browser to target page.
     *
     * Relocation method is decided based on the context of the pager element,
     * being in order of priority:
     *  - a AJAX enabled Views context - AJAX is used
     *  - a Views preview area in a Views settings form - AJAX is used
     *  - a page rendered through the admin overlay - BBQ is used
     *  - a normal page - document.location is used
     */
    function pagererRelocate(element, ajaxAttachElement, root, path) {
      // Check we are not relocating already.
      if (element.pagererState.relocating) {
        return false;
      } else {
        element.pagererState.relocating = true;
      }
      // Check if element is in Views AJAX context.
      var viewsAjaxContext = pagererInViewsAjaxContext(element);
      if (viewsAjaxContext) {
        // Element is in Views AJAX context.
        pagererAttachViewsAjax(ajaxAttachElement, 'doViewsAjax', viewsAjaxContext, root, path);
        $(ajaxAttachElement).trigger('doViewsAjax');
      } else if ($(element).parents('#views-live-preview').length) {
        // Element is in Views preview context.
        var base = $(element).attr('id');
        var element_settings = {
          'event': 'doViewsAjax',
          'progress': { 'type': 'throbber' },
          'url': root + path,
          'method': 'html',
          'wrapper': 'views-live-preview',
        };
        Drupal.ajax[base] = new Drupal.ajax(base, element, element_settings);
        $(element).trigger('doViewsAjax');

      } else if (window.Drupal.overlayChild) {
        // Drupal admin overlay
        window.parent.jQuery.bbq.pushState({'overlay': path});
      } else {
        // Normal page
        document.location = root + path;
      }
    };

    /**
     * Update widget value.
     */
    function pagererOffsetWidgetValue(widget, offset) {
      var widgetValue = isNaN($(widget).val()) ? 1 : parseInt($(widget).val());
      widgetValue += offset * widget.pagererState.interval;
      if (widgetValue < 1) {
        widgetValue = 1;
      } else if (widgetValue > widget.pagererState.total){
        widgetValue = widget.pagererState.total;
      }
      $(widget).val(widgetValue);
    };

    /**
     * Update slider value.
     */
    function pagererOffsetSliderValue(ui, offset) {
      var step = ui.slider('option', 'step');
      var newValue = ui.slider('option', 'value') + (offset * step);
      var maxValue = ui.slider('option', 'max');
      if (newValue > 0 && newValue <= maxValue) {
        ui.slider('option', 'value', newValue);
      }
    }

    /**
     * Views - Check if element is part of an AJAX enabled view.
     */
    function pagererInViewsAjaxContext(element) {
      if (Drupal.settings && Drupal.settings.views && Drupal.settings.views.ajaxViews) {
        // Loop through active Views Ajax elements.
        for (var i in Drupal.settings.views.ajaxViews) {
          var view = '.view-dom-id-' + Drupal.settings.views.ajaxViews[i].view_dom_id;
          var viewDiv = $(element).parents(view);
          if (viewDiv.size()) {
            return {
              target: viewDiv.get(0),
              settings: Drupal.settings.views.ajaxViews[i],
              selector: view
            };
          }
        }
      }
      return false;
    }

    /**
     * Views - Attach Views AJAX behaviour to an element.
     */
    function pagererAttachViewsAjax(element, event, viewContext, root, path) {

      // Link to the element.
      var $link = $(element);

      // Retrieve the path to use for views' ajax.
      var ajax_path = Drupal.settings.views.ajax_path;

      // If there are multiple views this might've ended up showing up multiple times.
      if (ajax_path.constructor.toString().indexOf('Array') != -1) {
        ajax_path = ajax_path[0];
      }

      // Check if there are any GET parameters to send to views.
      var queryString = window.location.search || '';
      if (queryString !== '') {
        // Remove the question mark and Drupal path component if any.
        var queryString = queryString.slice(1).replace(/q=[^&]+&?|&?render=[^&]+/, '');
        if (queryString !== '') {
          // If there is a '?' in ajax_path, clean url are on and & should be used to add parameters.
          queryString = ((/\?/.test(ajax_path)) ? '&' : '?') + queryString;
        }
      }

      // Load view's settings and parse pagerer root/path.
      var viewData = {};
      $.extend(
        viewData,
        viewContext.settings,
        Drupal.Views.parseQueryString(root + path),
        Drupal.Views.parseViewArgs(root + path, viewContext.settings.view_base_path)
      );

      // Load AJAX element_settings object and attach AJAX behaviour.
      var elementAjaxSettings = {
        url: ajax_path + queryString,
        submit: viewData,
        setClick: true,
        event: event,
        selector: viewContext.selector,
        progress: { type: 'throbber' }
      };
      viewContext.pagerAjax = new Drupal.ajax(false, $link, elementAjaxSettings);
    }

  }
};
})(jQuery);
