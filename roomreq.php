<?
require_once 'inc/html_temp.inc';
template_start(basename(__FILE__), 'HRR', 'Request a Room', '.');
?>
<div>
    <br/>
    Enter search criteria (* required):
    <form action="room_results.php" method="get" id="room_form">
        <table>
            <tr>
                <td>
                    <span>*Capacity</span>
                    <input type="text" name="capacity" value="" size="12"/>
                </td>
            </tr>
            <tr>
                <td>*Duration:
                    <select name="duration">
                        <option selected></option>
                        <?
                        for($i=30; $i<=120; $i+=30) {
                            echo "<option>";
                            echo $i;
                            echo "</option>";
                        }
                        ?>
                    </select>
                </td>
            </tr>
            <tr>
                <td>*Day: 
                    <?template_month_dropdown();?>
                    <select name="day">
                        <option selected></option>
                        <?
                        for($i=1;$i<=31;$i++) {
                            echo "<option>";
                            echo $i;
                            echo "</option>";
                        }
                        ?>
                    </select>
                </td>
            </tr>
            <tr>
                <td>
                    <?
                    if (!$update) {
                        ?>
                    Recurrence (if checked, ignores Day):
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
                </td>
            </tr>
            <tr>
                <td>Projector: 
                    <input type="radio" name="projector" value="false" checked>Don't Care
                    <input type="radio" name="projector" value="true">Yes
                </td>
            </tr>
            <tr>
                <td>Campus
                    <select name="campus">
                        <option selected></option>
                        <?
                        $result=getCampusRegions();
                        while($row = mysql_fetch_array($result)) {
                            echo "<option value='".$row['id']."'>";
                            echo $row['name'];
                            echo "</option>";
                        }
                        ?>
                    </select>
                </td>
            </tr>
            <tr>
                <td>Building
                    <select name="building">
                        <option selected></option>
                        <?
                        $result=getBuildings();
                        while($row = mysql_fetch_array($result)) {
                            echo "<option value='".$row['id']."'>";
                            echo $row['name'];
                            echo "</option>";
                        }
                        ?>
                    </select>
                </td>
            </tr>
            <tr>
                <td>
                    <input type="submit" value="Submit" name="submit"/>
                </td>
            </tr>
        </table>
    </form>
</div>

<?
template_end();
?>
