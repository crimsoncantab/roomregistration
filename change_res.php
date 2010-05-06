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
            $parsed_start = getdate($event->getStart());
            $parsed_end = getdate($event->getEnd());
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
        ?>
        <select name="month">
            <?if (!$update) {?><option selected></option><?}?>
                <?
                for($i=1;$i<=12;$i++) {
                    echo '<option value="'.$i.'"';
                    if ($update && $i==$parsed_start['month']) echo ' selected';
                    echo '>';
                    echo date('M',mktime(0, 0, 0, $i));
                    echo '</option>';
                }
                ?>
        </select>
            Day:
            <select name="day">
            <?if (!$update) {?><option selected></option><?}?>
            <?
            for($i=1;$i<=31;$i++) {
                echo '<option value="'.$i.'"';
                if ($update && $i==$parsed_start['mday']) echo ' selected';
                echo '>';
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
            <?if (!$update) {?><option selected></option><?}?>
            <?
            for($i=1;$i<=$_SESSION['max_priority'];$i++) {
                echo '<option value="'.$i.'"';
                if ($update && $i == $event->getPriority()) echo ' selected';
                echo '>';
                echo $i;
                echo '</option>';
            }
            ?>
        </select>
        <br />
        Room:
        <select name="roomselect" onchange="javascript:set_vals(this);">
            <?if (!$update) {?><option selected></option><?}?>
            <?
            $results = getAllRooms();
            while ($row = mysql_fetch_array($results)) {
                echo '<option value="'.$row['room_num'].'$'.$row['building'].'"';
                if ($update && $row['room_num'] == $event->getRoom() &&$row['building'] == $event->getBldg()) echo ' selected';
                echo '>'.$row['building'].' '.$row['room_num'].'</option>';
            }
            ?>
        </select>
        <input type="hidden" name="room" value="<?if ($update) echo $event->getRoom();?>" />
        <input type="hidden" name="building" value="<?if ($update) echo $event->getBldg();?>" />
        <br />
        Description:
        <input type="text" name="description" value="<?if ($update) echo $event->getDesc();?>" />
        <br />
        Start time:
        <select name="start_time">
            <?if (!$update) {?><option selected></option><?}?>
            <?
            for($i=$GLOBALS['beg'];$i<=$GLOBALS['end'];$i+=0.5) {
                echo '<option value="'.$i.'"';
                if ($update && (((int)$i)==$parsed_start['hours'])&& (($i - (int)$i)*60==$parsed_start['minutes'])) echo ' selected';
                echo '>';
                echo $i;
                echo "</option>";
            }
            ?>
        </select>
        End time:
        <select name="end_time">
            <?if (!$update) {?><option selected></option><?}?>
            <?
            for($i=$GLOBALS['beg'];$i<=$GLOBALS['end'];$i+=0.5) {
                echo '<option value="'.$i.'"';
                if ($update && (((int)$i)==$parsed_end['hours'])&& (($i - (int)$i)*60==$parsed_end['minutes'])) echo ' selected';
                echo '>';
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
