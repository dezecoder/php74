# The PHP Interpreter

[![Build Status](https://secure.travis-ci.org/php/php-src.svg?branch=master)](http://travis-ci.org/php/php-src)
[![Build status](https://ci.appveyor.com/api/projects/status/meyur6fviaxgdwdy?svg=true)](https://ci.appveyor.com/project/php/php-src)

PHP is a popular general-purpose scripting language that is especially suited to
web development.

Official PHP Git repository is located at https://git.php.net. A repository mirror
is available at https://github.com/php/php-src.

## Installation

For installation of PHP, please refer to the online documentation at
http://php.net/install.

## Guidelines for contributors

PHP accepts pull requests via GitHub. Discussions are done on GitHub, but
depending on the topic can also be relayed to the official PHP developer mailing
list internals@lists.php.net.

New features require an RFC and must be accepted by the developers. See
https://wiki.php.net/rfc and https://wiki.php.net/rfc/voting for more information
on the process.

Bug fixes **do not** require an RFC, but require a bugtracker ticket. Always
open a ticket at https://bugs.php.net and reference the bug id using #NNNNNN.

    Fix #55371: get_magic_quotes_gpc() throws deprecation warning

    After removing magic quotes, the get_magic_quotes_gpc function caused
    a deprecate warning. get_magic_quotes_gpc can be used to detected
    the magic_quotes behavior and therefore should not raise a warning at any
    time. The patch removes this warning

We do not merge pull requests directly on GitHub. All PRs will be pulled and
pushed through https://git.php.net.

See further documents located in the PHP repository for more information about
contributing:

- [CONTRIBUTING.md](/CONTRIBUTING.md)
- [CODING_STANDARDS](/CODING_STANDARDS)
- [README.MAILINGLIST_RULES](/README.MAILINGLIST_RULES)
- [README.RELEASE_PROCESS](/README.RELEASE_PROCESS)
