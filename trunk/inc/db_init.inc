<?
require_once 'sql_scripts.inc';
require_once 'vars.inc';

$conn = mysql_connect($my_sql_svr, $my_sql_usr, $my_sql_pwd);
if (!$conn)
    ;#TODO - Error gracefully
if (!mysql_select_db($my_sql_db))
    ;#TODO - Error gracefully
?>