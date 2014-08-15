--TEST--
Int is not a valid type declaration
--FILE--
<?php
function answer(): int {
    return 42;
}

answer();
--EXPECTF--
Catchable fatal error: the function answer was expected to return an object of class int and returned an integer in %s on line %d


