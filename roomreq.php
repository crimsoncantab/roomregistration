<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Request Room', '.');
?>
<div>
	<? print_r($_SESSION) ?><br/>
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
						for($i=30; $i<=120; $i+=30)
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
                <td>*Day: 
					<select name="month">
						<option selected></option>
<?
						for($i=1;$i<=12;$i++)
						{
							echo "<option>";
							echo $i;
							echo "</option>";
						}
?>
					</select>
					<select name="day">
						<option selected></option>
<?
						for($i=1;$i<=31;$i++)
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
                <td>*Recurring: 
					<input type="radio" name="recurring" value="false" checked>No
					<input type="radio" name="recurring" value="true">Yes
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
						while($row = mysql_fetch_array($result))
						{
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
                    <input type="submit" value="Submit" name="sub"/>
                </td>
            </tr>
        </table>
    </form>
</div>

<?
	template_end();
?>
