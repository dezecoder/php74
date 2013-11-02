--TEST--
test overloaded __toString on custom exception
--INI--
zend.expectations=1
--FILE--
<?php
class MyExpectations extends ExpectationException {
    public function __toString() {
        return sprintf(
            "[Message]: %s", __CLASS__);
    }
}

class One {
    public function __construct() {
        expect false : (string) new MyExpectations();
    }
}
class Two extends One {}

new Two();
?>
--EXPECTF--	
Fatal error: Uncaught exception 'ExpectationException' with message '[Message]: MyExpectations' in %sexpect_011.php:%d
Stack trace:
#0 %sexpect_011.php(%d): One->__construct()
#1 {main}
  thrown in %sexpect_011.php on line %d
