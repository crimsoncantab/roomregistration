<?
# TODO
# login user, set session variables, redirect to dashboard.
include_once 'inc/util.inc';
include_once 'inc/db_init.inc';
redir_if_logged_in("logout.php");

# check creditials using POST

# set session
set_logged_in('Test User','5');

# send to dashboard
redirect('home.php');
?>
