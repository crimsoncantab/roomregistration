<?
# TODO
# login user, set session variables, redirect to dashboard.
	include_once 'inc/util.inc';
	include_once 'inc/db_init.inc';

	# check credentials using POST
	authuser($_POST['uid'], $_POST['pwd']);
	redirect('home.php');

?>

