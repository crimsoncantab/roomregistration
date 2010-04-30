<?
$my_sql_svr = "db-courses";
$my_sql_db = "mcginn";
$my_sql_usr = "mcginn";
$my_sql_pwd = "p";

$conn = mysql_connect($my_sql_svr, $my_sql_usr, $my_sql_pwd);
if (!$conn)
    ;//TODO - Error gracefully
if (!mysql_select_db($my_sql_db))
    ;//TODO - Error gracefully
?>