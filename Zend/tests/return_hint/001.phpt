--TEST--
Basic return hints at compilation
--FILE--
<?php
function test1() : array {

}

test1();
?>
--EXPECTF--
Catchable fatal error: the function test1 was expected to return an array and returned null in %s on line %d
