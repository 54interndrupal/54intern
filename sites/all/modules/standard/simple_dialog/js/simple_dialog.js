/*
  @file
  Defines the simple modal behavior
*/

(function ($) {
  /*
    Add the class 'simple-dialog' to open links in a dialog
    You also need to specify 'rev="<selector>"' where the <selector>
    is the unique id of the container to load from the linked page.
    Any additional jquery ui dialog options can be passed through
    the rel tag using the format:
       rel="<option_name1>:<value1>;<option_name2>:<value2>;"
    e.g. <a href="financing/purchasing-options" class="simple-dialog" 
          rel="width:900;resizable:false;position:[60,center]" 
          rev="content-area" title="Purchasing Options">Link</a>
    NOTE: This method doesn't not bring javascript files over from
    the target page. You will need to make sure your javascript is
    either inline in the html that's being loaded, or in the head tag
    of the page you are on.
    ALSO: Make sure the jquery ui.dialog library has been added to the page
  */
  Drupal.behaviors.simpleDialog = {
    attach: function (context, settings) {
      // Create a container div for the modal if one isn't there already
      if ($("#simple-dialog-container").length == 0) {
        // Add a container to the end of the body tag to hold the dialog
        $('body').append('<div id="simple-dialog-container" style="display:none;"></div>');
        try {
          // Attempt to invoke the simple dialog
          $( "#simple-dialog-container", context).dialog({
            autoOpen: false,
            modal: true
          });
          Drupal.simpleDialog.applyOptions(settings.simpleDialog.defaults);
        }
        catch (err) {
          // Catch any errors and report
          Drupal.simpleDialog.log('[error] Simple Dialog: ' + err);
        }
      }
      // Add support for automodal class if enabled
      var classes = '';
      if (settings.simpleDialog.classes) {
        classes = ', .' + settings.simpleDialog.classes;
      }
      $('a.simple-dialog' + classes, context).click(function(event) {
        if (!event.metaKey) {
          // prevent the navigation
          event.preventDefault();
          // Set up some variables
          var url = this.href;
          var title = this.title;
          var selector = this.name;
          var options = this.rel;
          var option = null;
          if (url && title && selector) {
            // Set the title of the dialog
            $('#simple-dialog-container').dialog('option', 'title', title);
            // Add a little loader into the dialog while data is loaded
            $('#simple-dialog-container').html('<div class="simple-dialog-ajax-loader"></div>');
            // Save the dialog height before resizing for the loader
            var height = $('#simple-dialog-container').dialog('option', 'height');
            $('#simple-dialog-container').dialog('option', 'height', 200);
            // Use jQuery .load() to load the html from the page
            $('#simple-dialog-container').load(url + ' #' + selector, function() {
              $('#simple-dialog-container').dialog('option', 'height', height);
              Drupal.simpleDialog.applyOptions(options);
              // Attach any behaviors to the loaded content
              Drupal.attachBehaviors($('#simple-dialog-container'));
            });
            // Open the dialog
            $('#simple-dialog-container').dialog('open');
          }
          // Return false for good measure
      		return false;
    		}
      });
    }
  }
  
  // Create a namespace for our simple dialog module
  Drupal.simpleDialog = {};

  // Function to apply the options formatted as they should be
  // in the "rel" tag
  Drupal.simpleDialog.applyOptions = function(opts) {
    var options = opts.split(';');
    for (var i in options) {
      if (options[i]) {
        // Parse and Clean the option
        option = Drupal.simpleDialog.cleanOption(options[i].split(':'));
        // Attempt to apply the option
        try {
          $('#simple-dialog-container').dialog('option', option[0], option[1]);
        } catch (err) {
           Drupal.simpleDialog.log('[error] Simple Dialog: Could not set dialog option: ' + option[0] + ' with value: ' + option[1] + '. Error: ' + err);
        }
      }
    }
  }
  
  // Function to clean up the option.
  Drupal.simpleDialog.cleanOption = function(option) {
    // If it's a position option, we may need to parse an array
    if (option[0] == 'position' && option[1].match(/\[.*,.*\]/)) {
      option[1] = option[1].match(/\[(.*)\]/)[1].split(',');
      // Check if positions need be converted to intern_job
      if (!isNaN(parseInt(option[1][0]))) {
        option[1][0] = parseInt(option[1][0]);
      }
      if (!isNaN(parseInt(option[1][1]))) {
        option[1][1] = parseInt(option[1][1]);
      }
    }
    // Convert text boolean representation to boolean
    if (option[1] === 'true') {
      option[1 ]= true;
    }
    else if (option[1] === 'false') {
      option[1] = false;
    }
    return option;
  }

  Drupal.simpleDialog.log = function(msg) {
    if (console) {
      console.log(msg);
    }
  }
  
})(jQuery);