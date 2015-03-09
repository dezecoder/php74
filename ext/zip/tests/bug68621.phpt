--TEST--
Bug #68621	Filename appends the base url.
The ZipArchive::open treats the filename not as defined per php manual on valid file wrappers. It appends the filename to the base url. Hence, creating/manipulating a zip file in memory space would be impossible.
--SKIPIF--
<?php
/* $Id$ */
if(!extension_loaded('zip')) die('skip');
?>
--FILE--
<?php
error_reporting(0);
$zip = new \ZipArchive();
if (!($err = $zip->open("php://memory", \ZipArchive::CREATE)))
{
	die(var_dump($err));
}
$zip->addFromString("test.txt", "sample text");

if ($zip->filename == "php://memory") {
	echo "done";
} else {
	echo "failed";
}
die;
?>
--EXPECTF--
done
