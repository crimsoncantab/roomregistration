<?
	require_once 'inc/html_temp.inc';
        $update = isset($_GET['event_id']);
        $banner = ($update) ? 'Modify a Reservation':'Request a Room';
        template_start(basename(__FILE__), 'HRR', $banner, 'home.php');
        if ($update) $event = getEvent($_GET['event_id']);
?>
<div>
Use the following form to <? echo ($update) ? 'change the' : 'add a'; ?> reservation:
<?
if ($update) {
?>
    <form action="handle_req.php" method="POST">
        <input type="hidden" name="event_id" value="<?echo $_GET['event_id']?>" />
        <input type="hidden" name="delete" value="true" />
        <input type="submit" value="Delete Event" name="submit_d" />
    </form>
    <table class="visible">
<?
    Event::getEventHeaderRow();
    $event->getHtmlRow(false);
?>
    </table>
<form action="handle_req.php" method="post" id="change_form">
    <input type="hidden" name="event_id" value="<?echo $_GET['event_id']?>" />
<?
}
?>
    Month:
    <select name="month">
            <option selected></option>
<?
            for($i=1;$i<=12;$i++)
            {
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
            for($i=1;$i<=31;$i++)
            {
                    echo '<option value="'.$i.'">';
                    echo $i;
                    echo '</option>';
            }
?>
    </select>
    Priority:
    <select name="priority">
            <option selected></option>
<?
            for($i=1;$i<=$_SESSION['max_priority'];$i++)
            {
                    echo '<option value="'.$i.'">';
                    echo $i;
                    echo '</option>';
            }
?>
    </select>
    <br />
    Room:
    <select name="room">
            <option selected></option>
<?
            $results = getAllRooms();
            while ($row = mysql_fetch_array($results)) {
                echo '<option value="'.$row['room_num'].'">'.$row['building'].' '.$row['room_num'].'</option>';
            }
?>
    </select>
    Building:
    <select name="building">
            <option selected></option>
<?
            $results = getBuildings();
            while ($row = mysql_fetch_array($results)) {
                echo '<option value="'.$row['id'].'">'.$row['name'].'</option>';
            }
?>
    </select>
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
            for($i=$GLOBALS['beg'];$i<=$GLOBALS['end'];$i+=0.5)
            {
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
            for($i=$GLOBALS['beg'];$i<=$GLOBALS['end'];$i+=0.5)
            {
                    echo "<option>";
                    echo $i;
                    echo "</option>";
            }
?>
    </select>
    <br />
    <input type="submit" value="Submit" name="submit" />
</form>
</div>
<?
	template_end();
?>
