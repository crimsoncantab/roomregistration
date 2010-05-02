<?
	#logout user
	require_once 'inc/util.inc';
	//unset($_SESSION['uid']);
	$_SESSION=array();
	redirect(".");
?>
