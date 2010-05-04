<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Room Results', '.');
?>
<div>
	<? print_r($_SESSION) ?>
	<? print_r($_GET) ?>
<?
	if($_GET['campus']=="")
		echo "no campus";
	else
		echo "campus selected";
	if($_GET['campus']==""&&$_GET['building']=="")
		$result=getRooms($_GET['capacity'],$_GET['projector']);
	else
	{
		if($_GET['building']!="")
			$result=getBuildingRooms($_GET['building'],$_GET['capacity'],$_GET['projector']);		
		else if($_GET['campus']!="")
			$result=getCampusRooms($_GET['campus'],$_GET['capacity'],$_GET['projector']);
	}
?>
		<table border='1'><tr>
<?
	for($i = 0; $i < mysql_num_fields($result); $i++)
	{
		echo "<th>".mysql_field_name($result, $i)."</th>";
	}
?>
			<th>unavailable times</th>
			<th>select time</th>
<?
	echo "</tr>";
	
	while($row = mysql_fetch_array($result))
	{
?>
	    <form action="room_submit.php" method="post" id="room_submit">
<?
		echo "<tr>";
		for($i = 0; $i < mysql_num_fields($result); $i++)
		{
			echo "<td>". $row[$i] ."</td>";
		}
?>
			<td>
<?
//			print_r($row);
			$result2=getRoomRes($row['room_num'], $row['building'], $_GET['month'], $_GET['day']);
			//print_r($result2);
			while($row2 = mysql_fetch_array($result2))
			{
				for($i = 0; $i < mysql_num_fields($result2); $i++)
				{
					echo $row2[$i]."<br />";
				}				
			}
?>
			</td>
			<td>
				<select name="building">
					<option selected></option>
<?
					$hrs=$_GET['duration']/60;
					for($i=$GLOBALS['beg'];$i+$hrs<=$GLOBALS['end'];$i+=0.5)
					{
						echo "<option>";
						echo $i;
						echo "--";
						echo $i+$hrs;
						echo "</option>";						
					}
?>					
                                </select>
            </td>
			<td>
				<input type="submit" value="Submit" name="submit"/>
			</td>
		</tr>
	</form>
<?
	}
?>
		</table>
</div>

<?
	template_end();
?>
