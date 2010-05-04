<?

$beg=7;
$end=23;



#session stuff
session_start();
function is_logged_in() {
    return isset ($_SESSION['uid']);
}
function set_logged_in($uid,$username) {
	$_SESSION['uid'] = $uid;
	$_SESSION['username'] = $username;
}


#sql_helpers
function mysql_safe($query, $params=false) {
    if ($params) {
        foreach ($params as &$v) {
            $v = mysql_real_escape_string($v);
        }
        # Escaping parameters
        # str_replace - replacing ? -> %s. %s is ugly in raw sql query
        # vsprintf - replacing all %s to parameters
        $sql_query = vsprintf( str_replace("?","'%s'",$query), $params );
		//echo $sql_query;
        $sql_query = mysql_query($sql_query, $GLOBALS['conn']);    # Perfoming escaped query
    } else {
        $sql_query = mysql_query($query, $GLOBALS['conn']);    # If no params...
    }

    return $sql_query;
}


#redirects
function redirect($page, $die=true) {
    $host  = $_SERVER['HTTP_HOST'];
    $uri   = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');
    header("Location: http://$host$uri/$page");
    if ($die) die();
}
//function redir_if_logged_in($redir) {
//    if (is_logged_in()) {
//        redirect($redir);
//    }
//}
//function redir_if_not_logged_in($redir) {
//    if (!is_logged_in()) {
//        redirect($redir);
//    }
//}
?>
