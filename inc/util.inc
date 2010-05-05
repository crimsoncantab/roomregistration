<?

require_once 'db_init.inc';

$beg=7;
$end=23;

#session stuff
session_start();
function logout() {
    session_unset();
    session_destroy();
}
function is_logged_in() {
    return isset ($_SESSION['uid']);
}
function set_logged_in($uid,$username,$role,$can_edit) {
	$_SESSION['uid'] = $uid;
	$_SESSION['username'] = $username;
	$_SESSION['perm'] = $role;
        $_SESSION['can_edit'] = $can_edit;
}

function get_user_perm() {
    if (is_logged_in()) {
        return $_SESSION['perm'];
    }
    else {
        return $GLOBALS['no_user_perm'];
    }
}

function can_edit_res($res_user) {
    return $_SESSION['can_edit'] == 1 || $res_user == $_SESSION['uid'];
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
//        echo $sql_query.'<br/>';
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
?>
