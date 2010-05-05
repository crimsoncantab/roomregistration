<?
	require_once 'inc/html_temp.inc';
        if (!isset($_GET['event_id'])) {
            redirect('home.php');
        }
        //$event = getEvent.sdflkaj
        template_start(basename(__FILE__), 'HRR', 'Modify', 'home.php');
?>
<div>
Use the following form to change the reservation:
<form action="handle_req.php" method="post" id="change_form" />
</div>
<?
	template_end();
?>
