<?
#session stuff
session_start();
function is_logged_in() {
    return isset ($_SESSION[$UID]);
}
function set_logged_in($username, $uid) {
    $_SESSION[$UID] = $uid;
    $_SESSION[$USERNAME] = $username;
}


#sql_helpers
function mysql_safe($query, $conn, $params=false) {
    if ($params) {
        foreach ($params as &$v) {
            $v = mysql_real_escape_string($v);
        }
        # Escaping parameters
        # str_replace - replacing ? -> %s. %s is ugly in raw sql query
        # vsprintf - replacing all %s to parameters
        $sql_query = vsprintf( str_replace("?","'%s'",$query), $params );
        $sql_query = mysql_query($sql_query. $conn);    # Perfoming escaped query
    } else {
        $sql_query = mysql_query($query, $conn);    # If no params...
    }

    return ($sql_query);
}


#misc
function redirect($page, $die=true) {
    $host  = $_SERVER['HTTP_HOST'];
    $uri   = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');
    header("Location: http://$host$uri/$page");
}
function redir_if_logged_in($redir) {
    if (is_logged_in()) {
        redirect($redir);
    }
}
function redir_if_not_logged_in($redir) {
    if (!is_logged_in()) {
        redirect($redir);
    }
}
?>
