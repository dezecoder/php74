--TEST--
phpinfo() CGI
--POST--
dummy=x
--FILE--
<?php
var_dump(phpinfo());

echo "--\n";
var_dump(phpinfo(array()));

echo "--\n";
var_dump(phpinfo(0));

echo "--\n";
var_dump(phpinfo(INFO_LICENSE));

?>
--EXPECTF--
<!doctype html>
%abool(true)
--

Warning: phpinfo() expects parameter 1 to be long, array given in %sphpinfo2.php on line 5
NULL
--
<!doctype html>
%abool(true)
--
<!doctype html>
%abool(true)
