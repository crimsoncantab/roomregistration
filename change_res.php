<?
require_once 'inc/html_temp.inc';
$update = isset($_GET['event_id']);
$banner = ($update) ? 'Modify a Reservation':'Request a Room';
template_start(basename(__FILE__), 'HRR', $banner, 'home.php', true);
if ($update) $event = getEvent($_GET['event_id']);
?>
<div>
    <div>Use the following form to <? echo ($update) ? 'change the' : 'add a'; ?> reservation:</div>
    <?
    if ($update) {
        ?>
    <form action="handle_req.php" method="post" id="delete_form">
        <input type="hidden" name="event_id" value="<?echo $_GET['event_id']?>" />
        <input type="submit" value="Delete Event" name="delete" />
    </form>
    <table class="visible">
            <?
            Event::getEventHeaderRow();
            $event->getHtmlRow(false);
            ?>
    </table>
        <?
    }
    ?>
    <form action="handle_req.php" method="post" id="change_form">
<?
if ($update) echo '<input type="hidden" name="event_id" value="'.$_GET['event_id'].'" />';
if (!($update && $event->isRecurring())) {
?>
        Month:
        <select name="month">
            <option selected></option>
            <?
            for($i=1;$i<=12;$i++) {
                echo '<option value="'.$i.'">';
                echo $i;
                echo '</option>';
            }
            ?>
        </select>
        Day:
        <select name="day">
            <option selected></option>
            <?
            for($i=1;$i<=31;$i++) {
                echo '<option value="'.$i.'">';
                echo $i;
                echo '</option>';
            }
            ?>
        </select>
<?
}
?>
        Priority:
        <select name="priority">
            <option selected></option>
            <?
            for($i=1;$i<=$_SESSION['max_priority'];$i++) {
                echo '<option value="'.$i.'">';
                echo $i;
                echo '</option>';
            }
            ?>
        </select>
        <br />
        Room:
        <select name="roomselect" onchange="javascript:set_vals(this);">
            <option selected></option>
            <?
            $results = getAllRooms();
            while ($row = mysql_fetch_array($results)) {
                echo '<option value="'.$row['room_num'].'$'.$row['building'].'">'.$row['building'].' '.$row['room_num'].'</option>';
            }
            ?>
        </select>
        <input type="hidden" name="room" value="" />
        <input type="hidden" name="building" value="" />
        <br />
        <?
        if (!$update) {
            ?>
        Description:
        <input type="text" name="description" value="" />
        <br />
            <?
        }
        ?>
        Start time:
        <select name="start_time">
            <option selected></option>
            <?
            for($i=$GLOBALS['beg'];$i<=$GLOBALS['end'];$i+=0.5) {
                echo "<option>";
                echo $i;
                echo "</option>";
            }
            ?>
        </select>
        End time:
        <select name="end_time">
            <option selected></option>
            <?
            for($i=$GLOBALS['beg'];$i<=$GLOBALS['end'];$i+=0.5) {
                echo "<option>";
                echo $i;
                echo "</option>";
            }
            ?>
        </select>
        <br />
<?
if (!$update) {
?>
        Recurrence:
        S<input type="checkbox" name="recurring[]" value="1" />
        |M<input type="checkbox" name="recurring[]" value="2" />
        |T<input type="checkbox" name="recurring[]" value="3" />
        |W<input type="checkbox" name="recurring[]" value="4" />
        |Th<input type="checkbox" name="recurring[]" value="5" />
        |F<input type="checkbox" name="recurring[]" value="6" />
        |Sa<input type="checkbox" name="recurring[]" value="7" />
<?
}
?>
        <br />
        <input type="submit" value="Submit" name="submit" />
    </form>
</div>
<?
template_end();
?>
