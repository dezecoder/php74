--TEST--
Reflection::getModifierNames does not include the immutable modifier on nonimmutable properties.
--FILE--
<?php
class A {
	public $a;
	protected $b;
	private $c;
	var $d;
}
for ($name = 'a'; $name <= 'd'; ++$name) {
	$reflector = new ReflectionProperty(A::class, $name);
	$modifiers = $reflector->getModifiers();
	$names     = Reflection::getModifierNames($modifiers);
	var_dump(in_array('immutable', $names));
}
?>
--EXPECT--

bool(false)
bool(false)
bool(false)
bool(false)
