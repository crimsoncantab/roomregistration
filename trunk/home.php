<?
require_once 'inc/html_temp.inc';
template_start(basename(__FILE__), 'HRR', 'Dashboard', '.');
?>
<div>
    Your current reservations.  Click on a reservation to edit it.
    <table class="visible">
    <?
    $events=currentUserRes();
    Event::getEventHeaderRow();

    foreach ($events as $event) {
        $event->getHtmlRow();
    }

    ?>
    </table>

</div>
<?
template_end();
?>
