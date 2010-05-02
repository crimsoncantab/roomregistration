<?
	require_once 'inc/util.inc';
	redir_if_logged_in('home.php');

	require_once 'inc/html_temp.inc';
	template_start_html();
	template_head('HRR');
	template_start_body('Harvard Room Reservation');
?>

<div>
	<? print_r($_SESSION) ?>
    Welcome to the room reservation tool. Please login above.
</div>

<?
	template_end();
?>
