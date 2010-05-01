#!/usr/local/bin/php
<?
# TODO
#logout user
include_once 'inc/util.inc';
unset($_SESSION[$UID]);
redirect(".");
?>