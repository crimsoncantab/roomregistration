<?
	require_once 'inc/html_temp.inc';
        template_start(basename(__FILE__), 'HRR', 'Dashboard', '.');
?>
<div>
    Your current reservations.  Click on a reservation to edit it.
<?
	$events=currentUserRes();
        echo '<table border="1">';
        Event::getEventHeaderRow();

        foreach ($events as $event) {
            $event->getHtmlRow();
        }

        echo '</table>';
?>

</div>
<?
	template_end();
?>
