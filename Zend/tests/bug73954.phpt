--TEST--
Bug #73954 (NAN check fails on Alpine Linux with musl)
--FILE--
<?php

var_dump(NAN);
var_dump(is_nan(NAN));

function takes_int(int $int) {
}

takes_int(log(tan(3.14)));

?>
--EXPECTF--
float(NAN)
bool(true)

Fatal error: Uncaught TypeError: Argument 1 passed to takes_int() must be an integer (or convertible float, convertible string or boolean), non-convertible (NAN) float given, called in %s on line 9 and defined in %s:6
Stack trace:
#0 %s(9): takes_int(NAN)
#1 {main}
  thrown in %s on line 6
