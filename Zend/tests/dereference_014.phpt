--TEST--
Trying to create an object from dereferencing uninitialized variable
--FILE--
<?php

error_reporting(E_ALL);

class foo {
	public $x;
	static public $y;
		
	public function a() {
		return $this->x;
	}
	
	static public function b() {
		return self::$y;
	}
}

$foo = new foo;
$h = $foo->a()[0]->a;
var_dump($h);

$h = foo::b()[1]->b;
var_dump($h);

?>
--EXPECTF--
Notice: Cannot get offset of a non-array variable in %s on line %d

Notice: Trying to get property 'a' of non-object in %s on line %d
NULL

Notice: Cannot get offset of a non-array variable in %s on line %d

Notice: Trying to get property 'b' of non-object in %s on line %d
NULL
