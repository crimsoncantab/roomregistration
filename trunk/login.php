<?
	# login user, set session variables, redirect to dashboard.
	require_once 'inc/util.inc';
	require_once 'inc/db_init.inc';

	# check credentials using POST
	authUser($_POST['uid'], $_POST['pwd']);
	redirect('home.php');

?>

