<?
require_once 'vars.inc';
require_once 'sql_scripts.inc';

$conn = mysql_connect($my_sql_svr, $my_sql_usr, $my_sql_pwd);
if (!$conn) {
    echo "The website is experiencing technical difficulties\nPlease standby";
}
if (!mysql_select_db($my_sql_db)) {
    echo "The website is experiencing technical difficulties\nPlease standby";
}
?>
