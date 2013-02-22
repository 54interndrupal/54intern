
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Example
 * Usage


INTRODUCTION
------------

Current Maintainer: PDNagilum <pdnagilum@gmail.com>

Allows for passing an array to the watchdog command.

This module introduces an alternative to the watchdog command with an extra
argument for passing an array that will be included in the message-text.


EXAMPLE
-------

watchdog_array(
  $type,
  $message = '',
  $array = array(),
  $variables = array(),
  $severity = WATCHDOG_NOTICE,
  $link = NULL);

The third argument is now an array() which will be added to the message-text
using the print_r function.


USAGE
-----

watchdog_array(
  'Test',
  'This is a test',
  array(
    'Var1' => 1,
    'Var2' => 'Yeah',
  )
);

The above example will result in the following log-entry:

  This is a test
  Array
  (
    [Var1] => 1
    [Var2] => Yeah
  )
