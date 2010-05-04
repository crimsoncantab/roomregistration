<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Dashboard', '.');
?>
<div>
    Your current reservations.  Click on a reservation to edit it.
<?
	$result=currentUserRes();
	dump_results_into_html($result, true);
?>

</div>
<?
	template_end();
?>
