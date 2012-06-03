/**
 *  Export document
 *  Update: 2012/02/09
 */

 
Summary
-------
This module simply export nodes into word file (by formatted html) 
using VBO to bulk export. This module also borrow some function of 
print module, so which field would like to export can adjust at 
cck print display page.


Basic Functionality
-------------------
Here is feature list of this module:

 * Integrate with Views
 * Export node to Word


Requirements and Dependencies
-----------------------------
 * Views Bulk Operations (VBO)       --- http://drupal.org/project/views_bulk_operations
 * Printer, e-mail and PDF versions  --- http://drupal.org/project/print


Installation and Settings
-------------------------
According to the following steps:

1) Take or create your views (/admin/build/views) and view type must be "Node".

2) Set the Fields in your views (/admin/build/views/edit/"your views name").

3) In category "Basic settings" choose "Style" to "Bulk Operations" option.

4) Setting this "Bulk Operations" and look at fieldset of "Selected operations", 
   you can find and select "Export node to Word (export_doc_export_action)" option.


Author
------
Jimmy Huang (jimmy@jimmyhub.net, http://drupaltaiwan.org, user name jimmy)
If you use this module, find it useful, and want to send the author a thank 
or you note, feel free to contact me.

The author can also be contacted for paid customizations of this and other modules.