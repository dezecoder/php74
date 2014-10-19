--TEST--
testing anons inside namespaces
--FILE--
<?php
namespace lone {
   $hello = new class{} ;
}

namespace {
    var_dump ($hello);
}
?>
--EXPECTF--
object(lone\class@%s.%d)#1 (0) {
}

