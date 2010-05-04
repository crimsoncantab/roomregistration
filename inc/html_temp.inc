<?
require_once 'vars.inc';
require_once 'util.inc';
require_once 'inc/db_init.inc';
require_once 'inc/sql_scripts.inc';

function template_start_html() {


?>
<<??>?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<?


}

function template_head($title) {
?>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <link rel="stylesheet" type="text/css" href="css/style.css" />
        <title><? echo $title; ?></title>
    </head>
<?
}

function template_links($role) {
    $links = get_links($role);
    while ($link = mysql_fetch_array($links)) {
?>
        <div><a href="<?echo $link['page']; ?>"><?echo $link['display']; ?></a></div>
<?
    }
}

function template_start_body($title, $role) {


?>
    <body>
        <table id="master">
                <tr>
                    <th id="corner" />
                    <th id="banner" class="trim">
                        <div id="login">
<?
if (isset($_SESSION['error'])){
?>
				<div class="error"><?echo $_SESSION['error']; ?></div>

<?
	unset($_SESSION['error']);
}


    if (is_logged_in()) { #show login status
?>
                            <div>Logged in as <? echo $_SESSION['username']; ?>.</div>
                            <div>
                                <a href="logout.php">Logout</a>
                            </div>
<?
    }
    else { #make login form
?>
                            <form action="login.php" method="post" id="login_form">
                                <table>
                                    <tr>
                                        <td>
                                            <span>HUID</span>
                                            <input type="text" name="uid" value="" size="12"/>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td>
                                            <span>Pass</span>
                                            <input type="password" name="pwd" value="" size="12"/>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td>
                                            <input type="submit" value="Login" name="sub"/>
                                        </td>
                                    </tr>
                                </table>
                            </form>
<?
    }
?>
                        </div>
                        <div id="title"><? echo $title; ?></div>
                    </th>
                </tr>
                <tr>
                    <td id="nav" class="trim">
<?
    template_links($role);
?>
                    </td>
                    <td id="content">
<?


}

function template_end() {


?>
                    </td>
                </tr>
        </table>
    </body>
</html>
 <?


}

function template_start($filename, $title, $banner, $redir) {
	$role = get_user_perm();
        auth_page($filename, $role, $redir);
	template_start_html();
	template_head($title);
	template_start_body($banner, $role);
}
?>
