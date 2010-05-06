<?
require_once 'vars.inc';
require_once 'sql_scripts.inc';

$conn = mysql_connect($my_sql_svr, $my_sql_usr, $my_sql_pwd);
//echo $conn;
if (!$conn)
;#TODO - Error gracefully
if (!mysql_select_db($my_sql_db))
;#TODO - Error gracefully
//echo $my_sql_db;
?>
