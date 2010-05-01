<?
$my_sql_svr = "db-courses";
$my_sql_db = "bendeck";
$my_sql_usr = "bendeck";
$my_sql_pwd = "colochas";

$conn = mysql_connect($my_sql_svr, $my_sql_usr, $my_sql_pwd);
if (!$conn)
    ;//TODO - Error gracefully
if (!mysql_select_db($my_sql_db))
    ;//TODO - Error gracefully
?>
