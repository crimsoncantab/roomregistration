<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Modify A Reservation', 'home.php');
?>
<div>
<?
print_r($_GET);
?>
</div>
<?
	template_end();
?>
