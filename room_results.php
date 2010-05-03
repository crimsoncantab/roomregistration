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

	echo "<table border='1'><tr>";
	for($i = 0; $i < mysql_num_fields($result); $i++)
	{
		echo "<th>".mysql_field_name($result, $i)."</th>";
	}
	echo "</tr>";
	
	while($row = mysql_fetch_array($result))
	{
		echo "<tr>";
		for($i = 0; $i < mysql_num_fields($result); $i++)
		{
			echo "<td>". $row[$i] ."</td>";
		}
		echo "</tr>";
	}

	echo "</table>";
?>
</div>

<?
	template_end();
?>
