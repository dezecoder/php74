--TEST--
Test typed properties disallow incorrect type initial value (scalar)
--FILE--
<?php
class Foo {
	public int $bar = "string";
}
?>
--EXPECTF--
Fatal error: Default value for properties with integer type can only be integer in %s on line 3




