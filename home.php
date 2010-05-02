<?
	require_once 'inc/util.inc';
	require_once 'inc/db_init.inc';
	redir_if_not_logged_in('.');
	require_once 'inc/html_temp.inc';
	template_start_html();
	template_head('HRR');
	template_start_body('Harvard Room Reservation - Dashboard');
?>
<div>
	<? print_r($_SESSION) ?><br/>
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
