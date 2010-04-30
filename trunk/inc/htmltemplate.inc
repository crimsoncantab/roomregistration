<?
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
        <title><? echo $title; ?></title>
    </head>
<?


}

function template_start_body($banner) {


?>
    <body>
        <table id="master">
            <thead>
                <tr>
                    <th id="corner" />
                    <th id="banner"><? echo $banner; ?></th>
                </tr>
            </thead>
            <tbody>
                <tr>
                    <td id="nav">
                        <div>Links</div>
                    </td>
                    <td id="content">
<?


}

function template_end() {


?>
                    </td>
                </tr>
            </tbody>
        </table>
    </body>
</html>
 <?


}
?>