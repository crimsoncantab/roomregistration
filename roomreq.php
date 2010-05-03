<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Request Room', '.');
?>
<div>
	<? print_r($_SESSION) ?><br/>
    Enter search criteria (* required):
    <form action="room_results.php" method="get" id="login_form">
        <table>
            <tr>
                <td>
                    <span>*Capacity</span>
                    <input type="text" name="uid" value="" size="12"/>
                </td>
            </tr>
			<tr>
				<td>*Time:
					<select name="time">
						<option selected></option>
<?
						for($i=$GLOBALS['beg_time']; $i<=$GLOBALS['end_time']; $i++)
						{
							echo "<option>";
							echo $i;
							echo "</option>";
						}
?>
					</select>
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
						while($row = mysql_fetch_array($result))
						{
							echo "<option>";
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
						while($row = mysql_fetch_array($result))
						{
							echo "<option>";
							echo $row['name'];
							echo "</option>";
						}
?>
					</select>
				</td>
			</tr>
            <tr>
                <td>
                    <input type="submit" value="Submit" name="sub"/>
                </td>
            </tr>
        </table>
    </form>
</div>

<?
	template_end();
?>
