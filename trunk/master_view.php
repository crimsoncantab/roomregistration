<?
	require_once 'inc/html_temp.inc';
        require_once 'inc/sql_scripts.inc';
        template_start(basename(__FILE__), 'HRR', 'Master View', '.');
?>
<div>
All reservations.  Click on row to modify.
<?
        print_r($_SESSION);
	$events=currentRes();
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
