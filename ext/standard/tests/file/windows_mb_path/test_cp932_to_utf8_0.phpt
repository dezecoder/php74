--TEST--
Test fopen() for reading eucjp to UTF-8 path 
--SKIPIF--
<?php
include dirname(__FILE__) . DIRECTORY_SEPARATOR . "util.inc";

skip_if_not_win();
if (getenv("SKIP_SLOW_TESTS")) die("skip slow test");
skip_if_no_required_exts();

?>
--FILE--
<?php
/*
#vim: set fileencoding=cp932
#vim: set encoding=cp932
*/

include dirname(__FILE__) . DIRECTORY_SEPARATOR . "util.inc";

$prefix = create_data("file_eucjp");
$fn = $prefix . DIRECTORY_SEPARATOR . "\�e�X�g�}���`�o�C�g�E�p�X"; // EUCJP string
$fnw = iconv('cp932', 'utf-8', $fn);

$f = fopen($fnw, 'r');
if ($f) {
	var_dump($f, fread($f, 42));
	var_dump(fclose($f));
} else {
	echo "open utf8 failed\n";
} 

remove_data("file_eucjp");

?>
===DONE===
--EXPECTF--	
resource(%d) of type (stream)
string(33) "reading file wihh eucjp filename
"
bool(true)
===DONE===
