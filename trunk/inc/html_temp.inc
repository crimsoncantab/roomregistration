<?
require_once 'util.inc';
require_once 'vars.inc';

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

function template_start_body($title) {


?>
    <body>
        <table id="master">
                <tr>
                    <th id="corner" />
                    <th id="banner" class="trim">
                        <div id="login">
<?
    if (is_logged_in()) { //show login status
?>
                            <div>Logged in as <?$_SESSION[$USERNAME] ?>.</div>
                            <div>
                                <a href="logout.php">Logout</a>
                            </div>
<?
    }
    else { //make login form
?>
                            <form action="login.php" method="post" id="login_form">
                                <table>
                                    <tr>
                                        <td>
                                            <span>User</span>
                                            <input type="text" name="username" value="" size="12"/>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td>
                                            <span>Pass</span>
                                            <input type="password" name="password" value="" size="12"/>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td>
                                            <table style="width: 100%; border: 0; margin: 0px; padding: 0px; border-collapse: collapse">
                                                <tr>
                                                    <td style="text-align: left">
                                                        <a href="register.php">Register</a>
                                                    </td>
                                                    <td style="text-align: right">
                                                        <input type="submit" value="Login" name="sub"/>
                                                    </td>
                                                </tr>
                                            </table>
                                            
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
                        <div>Links</div>
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
?>