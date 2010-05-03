<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Room Results', '.');
?>
<div>
	<? print_r($_SESSION) ?>
	<? print_r($_GET) ?>
<?
	if($_GET['campus']=="")
		echo "no campus";
	else
		echo "campus selected";

?>
</div>

<?
	template_end();
?>
