<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation', 'home.php');
?>

<div>
    Welcome to the room reservation tool. Please login above.
</div>

<?
	template_end();
?>
