--TEST--
Basic return hints callable and closures errors
--FILE--
<?php
class foo {
	public function bar() : callable {
		$test = "one";
		return function() use($test) : array {
			return null;
		};
	}
}

$baz = new foo();
var_dump($func=$baz->bar(), $func());
?>
--EXPECTF--
Catchable fatal error: the function %s was expected to return an array and returned null in %s on line %d

