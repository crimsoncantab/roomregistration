<?
	#logout user
	require_once 'inc/util.inc';
	//unset($_SESSION['uid']);
	session_destroy();
	redirect(".");
?>
