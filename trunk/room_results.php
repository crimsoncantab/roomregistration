<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Room Results', '.');
?>
<div>
	<? print_r($_SESSION) ?>
	<? print_r($_GET) ?>
</div>

<?
	template_end();
?>
