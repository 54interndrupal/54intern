Core Library
============

This module changes the Drupal core aggregation mecanism process. It greatly
reduces I/O and aggregated number of files, and improves chances of client
cache hit, therefore while it produces bigger aggregated files, it reduces
greatly the bandwidth utilization while users browse. 

This is achieved by bypassing the dynamic CSS and JS inclusion. Instead of
including and aggregating only needed files on a per-page basis, it learns
files being used site-wide while user browse, then is able to produce larger
therefore more revelant files that aggregate all those atomic files whether
or not they are being used on the page.

Over time, the number of aggregated files reduce to achieve a stable state
where all site JS files are being aggregated in one file only, and all site
CSS are being aggretated in only two files (libraries into one side, theme
files into another, can be more if there are browser-specific files).

Once the files are stable, site administrator can then enable the full bypass
mode, which will only uses the actual saved state and won't ever do any more
I/O for CSS and JS inclusion, based on the cached state.

On production sites that do not changes nor update their module often, the
performance boost is significant because no dynamic inclusion is being done
anymore (therefore no I/O are made at all), as the bandwidth consumption is
greatly reduced (because clients will cache these files at first hit and won't
download them on the server after that).

This module produces really a few side-effects, depeing on the theme coding
mainly. We bypass core mecanism, but keep sanefully files weighting which will
avoid most potential conflicts.

Motivation
----------

Drupal 7 does an hard and heavy work about JS and CSS aggregation. It is able
to separate aggregated files into multiple groups. This is a good thing for
lazzy site admins, the first reason is by doing finer groups, those per-group
aggregated files will have greater chances of getting static file hits.

Therefore, there is a main disadvantage: because groups are hardcoded, even on
a site where the files does not change on a per-page basis, the site will ever
aggregate at least 3 JS files, and 3 CSS files, which is not quite elegant.

On larger scale sites, site admin would want to bypass this ugly aggregation
style which would cause something like 4 to even a lot more useless HTTP
requests, on almost each client hit because aggregated files will be differnt
on a per-page basis.

The ideal case would be to have only one sitewide JS file, as only one sitewide
CSS file. This won't happen because:
 - JS are split between libraries and Drupal locale translations.
 - CSS are split between libraries and theme files (we do that, for a good
   reason).
So, our ideal case will be to have only two sitewide files of each.

Original goal and methodology
-----------------------------

This module intend to allow site administrators to manually set which files
among all core libraries and module specific files should be aggregated as
core immutable libraries.

This is not true anymore because of the learning mecanism, which will be
enabled per default. Therefore, the suicidal tendencies of site admins tell
me that some of them will still use the manual UI in order to build their own
aggregation rules. In fact, the module has been built for this, and this is
a totally legal, moreover totally legitimate thing to do.

When using this manual mode, each one of the selected JS file candidate for
sitewide aggregation will be considered as a library and will be forced to
get to the JS_LIBRARY group. by doing this we open the door to file weight
conflict between group, thus, we have an override mecanism that will consider
each group as a weight addition and will pragmatically add an indescent weight
factor to files that core does not expose itself as a library. This will help
keeping things in order.

JS minification HOWTO
---------------------

This module can use the JSMin library PHP port in order to minify JS files.

Right now, we won't use any other contrib module in order to remain dependency
agnostic. This is important because this module has one and only one simple
goal, and it shouldn't rely on any other module that add extensive execution
overhead.

All is about performances, and also leaving the choice for the site admin to
do what he want to do.

So, we don't use any library handling module, sorry, it may change, but right
now the only good way of making it work is by adding the jsmin.php file into
this folder:
  sites/all/libraries/jsmin/

You can download it there:
  https://github.com/rgrove/jsmin-php/

Once you downloaded it, you can enable minification on the Core Library module
configuration page, and the form won't revert the option automatically anymore.

We do not provide this library because its licence may conflict with the GPL
one, sorry about that, but you are on your own for downloading it.

Potential known side effect with CSS
------------------------------------

CSS files are not processed the same way, because administration screens and
frontend pages won't have the same theme, we can't merge groups else we would
totally break the aggregation benefit of having only one large file. Solution
is a bit ugly, but will work on most sites: we pragmatically override the
CSS_DEFAULT group and add module specific CSS into the CSS_SYSTEM group, using
the same weight alteration mecanism as we use for JS.

The side effect of this (there is always one) is that Drupal, per default, will
put CSS_DEFAULT files after CSS_THEME theme specific files. We reverse order
and set the CSS_DEFAULT into the CSS_SYSTEM which break this behavior. This can
lead to CSS directive conflicts for theme that mess up with module specific CSS
files. Because of this statement, the CSS group merge remains optional.

But it seems we are lucky! Because theme CSS files are ordered before the module
specifics, it happens that theme developers are forced to do proper CSS override
using CSS directive specialization instead of relying onto order, which make our
reverse algorithm to almost always work as-is with well coded themes.

Auto-configuration
------------------

This module provide a learning mode. Three different profiles are provided for
this learning mode, they are described in administration section. These modes
all works quite the same:

 1. At JS or CSS alteration time, unknown files that should be displayed
    on page are found.

 2. Once all these files have been found, the manual variable is populated with
    the new files, and saved.

 3. Then, the alteration goes, also using new file found for override, thus
    aggregating them the first time.

 4. When a new page is hit, chances that a new file is found is naturally
    lowered, the more users browse, the faster you'll reach a state where your
    Drupal site naturally aggregates all the files in one and only one file.

Once the configuration actually fits you (you have to do some profiling on your
own for that) you can then switch back to manual or bypass mode in order for
the learning process to stop. The module will still continue to force file
aggregation, using the earlier learnt files.

You can always go back, enable the UI module again and customize the automated
configuration on your own then.

Bypass mode
-----------

When the configuration is OK, site admin should switch to full bypass mode.
This particular mode alter the 'styles' and 'scripts' element types element
info, and forces it to be rendered with our own functions.

When creating CSS aggregated files using the bypass mode, the CSS grouping
mode will gracefully be set to 'dual' mode. This ensures that in case one
or more themes are enabled, there will always be only one included in the
page and will avoid CSS conflicts between themes.

This also ensures that each theme will have its own aggregated CSS file that
won't never be modified anymore until the admin switches back to another mode.

Once the bypass mode is set, aggregated files are generated only once using
the current learnt files state. Those files, once aggregated, won't regenerate
themselves if the files are being manually deleted on the system, so if it
happens, an specific button on the administration page will allow you to force
the module to rebuild these.

Bypass mode and drupal_add_TYPE()
---------------------------------

When using bypass mode, the hook_library_TYPE_alter() hooks will still be used
during page construction, this ensures the files' weights to be the right one,
we don't store the weight and we won't.

These functions may still do some file_exists() I/O that we should definitely
get rid off. This will be a future challenge. 

Because drupal_add_TYPE() function will still be run whatever we do (we can't
take over module's code dynamically), why not use their result anyway?

UI and stat collection systems (Core Library Advanced UI module)
----------------------------------------------------------------

When in manual mode, aggregation rules can be built over administrative file
listings. We can get a list of system known libraries quite easily and expose
it to the site admin.

Nevertheless we have problems with modules' arbitrary set files, that the
system itself can't guess before those files are being processed at least
once.

We put in place a statistics collection system (which has really heavy and
indencent performance impact) that allows developers to play with a development
site and let the system discover files while browsing. Once all files (the only
thing the developer can do is hope that all files have been processed at least
once) have been discovered, another configuration screen is populated with what
we call the 'orphan files'. Those files are displayed side by side with number
of hits for each one of them.

This 'orphan' screen can then help decide which files the site admin would want
to force being processed and aggregated site wide.

Future
------

We intend to add a JS minification mecanism to enfore files to get through more
than aggregation, but also minification. This will save up a bit of bandwidth.

Some badly coded JS files won't pass through the minification and will cause
errors on client side, so we will make this mecanism site wide optional, at
first, then per file optional then.
