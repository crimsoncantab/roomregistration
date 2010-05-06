<?
require_once 'vars.inc';
require_once 'util.inc';
require_once 'db_init.inc';
require_once 'sql_scripts.inc';
require_once 'inc/event.inc';
function template_month_dropdown() {
    ?>
<select name="month">
    <option selected></option>
        <?
        for($i=1;$i<=12;$i++) {
            echo '<option value="'.$i.'">';
            echo date('M',mktime(0, 0, 0, $i));
            echo '</option>';
        }
        ?>
</select>
    <?
}
function template_start_html() {


    ?>
<<??>?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

    <!--So it's a bad idea to leave these here in the future, but good debugging technique
    without making pages look crappy:
        <?
        print_r($_SESSION);
        print_r($_PUT);
        print_r($_GET) ?>
    -->
        <?


    }

    function template_head($title, $include_js, $filename) {
        ?>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <link rel="shortcut icon" href="favicon.ico" type="image/x-icon" />
        <link rel="icon" href="favicon.ico" type="image/x-icon" />
        <link rel="stylesheet" type="text/css" href="css/style.css" />
            <?
            if ($include_js) echo '<script src="js/'.basename($filename,'.php').'.js"></script>';
            ?>
        <title><? echo $title; ?></title>
    </head>
        <?
    }

    function template_links() {
        $links = get_links();
        while ($link = mysql_fetch_array($links)) {
            //&loz;  &diams; &raquo; &rsaquo; &rang; &#9002;
            ?>
    <div>&loz;<a href="<?echo $link['page']; ?>"><?echo $link['display']; ?></a></div>
            <?
        }
    }

    function template_start_body($subtitle) {


        ?>
    <body>
        <table id="master">
            <tr>
                <th id="corner"></th>
                <th id="banner" class="trim">
                    <div id="login">
                            <?
                            if (isset($_SESSION['error'])) {
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
                    <div id="title">
                        <div>Harvard Room Reservation</div>
                        <div><? echo $subtitle; ?></div>
                    </div>
                </th>
            </tr>
            <tr>
                <td id="nav" class="trim">
                        <?
                        template_links();
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

function template_start($filename, $title, $banner, $redir, $include_js=false) {
    auth_page($filename, $redir);
    template_start_html();
    template_head($title, $include_js, $filename);
    template_start_body($banner);
}
?>
