<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Dashboard', '.');
?>
<div>
    Your current reservations:
<?
 	# this code inspired by http://www.tizag.com/mysqlTutorial/mysql-date.php
	$result=currentUserRes($_SESSION['uid']); 
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
