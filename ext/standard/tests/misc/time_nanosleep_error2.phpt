--TEST--
time_nanosleep — Delay for a number of seconds and nanoseconds
--SKIPIF--
<?php if (!function_exists('time_nanosleep')) die("skip"); ?>
--CREDITS--
Àlex Corretgé - alex@corretge.cat
--FILE--
<?php

$nano = time_nanosleep(2, 'B');

?>
--EXPECTF--
Warning: time_nanosleep() expects parameter 2 to be integer (or convertible float, convertible string or boolean), non-numeric string given in %s.php on line %d
