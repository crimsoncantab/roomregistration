<?
require_once 'inc/html_temp.inc';
template_start(basename(__FILE__), 'HRR', 'Available Rooms', '.', true);
?>
<div>
    <?
//    if($_GET['campus']=="")
//        echo 'no campus';
//    else
//        echo 'campus selected';
    $recurring = isset ($_GET['recurring']);
    if($_GET['campus']==''&&$_GET['building']=='')
        $result=getRooms($_GET['capacity'],$_GET['projector']);
    else {
        if($_GET['building']!='')
            $result=getBuildingRooms($_GET['building'],$_GET['capacity'],$_GET['projector']);
        else if($_GET['campus']!='')
            $result=getCampusRooms($_GET['campus'],$_GET['capacity'],$_GET['projector']);
    }
    ?>
    <form action="handle_req.php" method="post" name="handle_req" id="handle_req">
        <? if ($recurring) {
            foreach ($_GET['recurring'] as $rec) {
                ?>
        <input type="hidden" name="recurring[]" value="<?echo $rec;?>" />
                <?
            }
        } else {?>
        <input type="hidden" name="month" value="<?echo $_GET['month'];?>" />
        <input type="hidden" name="day" value="<?echo $_GET['day'];?>" />
            <?}?>
        <input type="hidden" name="room" value="" />
        <input type="hidden" name="building" value="" />
        <input type="hidden" name="start_time" value="" />
        <input type="hidden" name="end_time" value="" />
        <span>Description:</span>
        <input type="text" name="description" value="" />
        <span>Priority:</span>
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
    </form>
    <table class="visible">
        <tr>
            <?
            for($i = 0; $i < mysql_num_fields($result); $i++) {
                echo '<th>'.mysql_field_name($result, $i).'</th>';
            }
            ?>
            <th>unavailable times</th>
            <th>select time</th>
        </tr>
        <?
        $row_i = 0;
        while($row = mysql_fetch_array($result)) {
            ?>

        <tr>
                <?
                for($i = 0; $i < mysql_num_fields($result); $i++) {
                    echo '<td>'. $row[$i] .'</td>';
                }
                ?>
            <td>
                    <?
                    if ($recurring) {
                        for ($j = 0; $j < count($_GET['recurring']); $j++) {
                            $result2 = getRoomResPattern($room, $building, $_GET['recurring'][$j]);
                            while($row2 = mysql_fetch_array($result2)) {
                                for($i = 0; $i < mysql_num_fields($result2); $i++) {
                                    echo $row2[$i].'<br />';
                                }
                            }
                        }
                    }
                    else {
                        $result2=getRoomRes($row['room_num'], $row['building'], $_GET['month'], $_GET['day']);
                        while($row2 = mysql_fetch_array($result2)) {
                            for($i = 0; $i < mysql_num_fields($result2); $i++) {
                                echo $row2[$i].'<br />';
                            }
                        }
                    }
                    ?>
            </td>
            <td>
                <select id="time<?echo $row_i;?>">
                    <option selected></option>
                        <?
                        $hrs=$_GET['duration']/60;
                        for($i=$GLOBALS['beg'];$i+$hrs<=$GLOBALS['end'];$i+=0.5) {
                            $s = $i;
                            $e = $i+$hrs;
                            echo '<option value="'.$s.'$'.$e.'">';
                            echo $s;
                            echo ' - ';
                            echo $e;
                            echo '</option>';
                        }
                        ?>
                </select>
            </td>
            <td>
                <input type="button" value="Submit" name="submit"
                       onclick="pop_sub_form('<?echo $row_i;?>', '<?echo $row['room_num'];?>', '<?echo $row['building'];?>')"/>
            </td>
        </tr>
                <?
                $row_i++;
            }
            ?>
    </table>
</div>

    <?
    template_end();
?>
