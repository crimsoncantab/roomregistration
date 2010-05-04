<?
	#logout user
	require_once 'inc/util.inc';
	//unset($_SESSION['uid']);
        session_unset();
	session_destroy();
	redirect(".");
?>
