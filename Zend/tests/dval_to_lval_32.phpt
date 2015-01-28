--TEST--
zend_dval_to_lval preserves low bits  (32 bit long)
--FILE--
<?php
	/* test doubles around -4e21 */
	$values = [
		-4000000000000001048576.,
		-4000000000000000524288.,
		-4000000000000000000000.,
		-3999999999999999475712.,
		-3999999999999998951424.,
	];
	/* see if we're rounding negative numbers right */
	$values[] = -2147483649.8;

	foreach ($values as $v) {
		var_dump((int)$v);
	}

?>
--EXPECT--
int(-4000000000000001048576)
int(-4000000000000000524288)
int(-4000000000000000000000)
int(-3999999999999999475712)
int(-3999999999999998951424)
int(-2147483649)
