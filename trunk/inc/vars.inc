<?
#session variable constants
$UID = 'uid';
$USERNAME = 'username';

#database variables
#(for sql scripts, see sql.inc)
$my_sql_svr = 'localhost';
$my_sql_db = 'bendeck';
$my_sql_usr = 'root';
$my_sql_pwd = 'chjiop1151';


#list of links to show up in navbar
#this may need to be more sophisticated for certain roles
#(maybe use some OO coding)
$links['register.php'] = 'Register';
$links['index.php'] = 'Home';
$links['about.php'] = 'About';
$usr_links['logout.php'] = 'Logout';
$usr_links['home.php'] = 'Home';
#$usr_links['settings.php'] = 'Settings';
$usr_links['roomreq.php'] = 'Make Request';

?>
