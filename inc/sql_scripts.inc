<?
require_once 'util.inc';
require_once 'vars.inc';
require_once 'event.inc';
#This file lists all the queries needed.
#When a query takes parameters, they should be escaped with ?
#The query should be called with the mysql_safe() function in util.inc,
#along with it's arguments
#
#an example query:
#$query='INSERT INTO table(col1, col2) values(?,?)';
#
#a call to execute this query:
#mysql_safe($query, array($var1, $var2));

#authenticates user.  takes username, phash params, returns user info
$query_auth_user='SELECT * FROM users NATURAL JOIN priv WHERE huid=?';

#get user's current events.
$query_curr_user_res='SELECT * FROM events WHERE huid=? ORDER BY start_time';

#get all res
$query_res='SELECT * FROM events ORDER BY start_time';

#check webpage permissions against a user.
$query_auth_page='SELECT * FROM pageperm WHERE page=? AND LOCATE(?, perm) != 0';

#get available links
$query_get_links='SELECT page, display FROM pageperm WHERE LOCATE(?, perm) != 0 AND in_nav=true';

#get campuses
$query_get_campuses='SELECT id,name FROM campus';

#get buildings
$query_get_buildings='SELECT id,name FROM building';

#add reservation.  takes room info, other variables...
#assumes time/location are available, returns event_id
$query_add_res='INSERT INTO events(huid,room,building,date_req,description,start_time,end_time,priority, recurring) VALUES'.
'(?,?,?,NOW(),?,FROM_UNIXTIME(?),FROM_UNIXTIME(?),?,NULL)';

#delete reservation.
$query_remove_res='DELETE FROM events WHERE event_id = ?';

#update reservation
$query_update_res='UPDATE events SET room = ?, building = ?, start_time = FROM_UNIXTIME(?), end_time = FROM_UNIXTIME(?) WHERE event_id = ?';

#find reservation(s) during certain time interval and for certain room
#takes room and time interval
$query_events_date_range_room='SELECT * FROM events WHERE'.
    ' FROM_UNIXTIME(?) < end_time'.
    ' AND FROM_UNIXTIME(?) > start_time'.
    ' AND room=? AND building=? AND event_id != ?';


$query_get_room_res='SELECT start_time,end_time,description FROM events WHERE room=? AND building=? 
AND MONTH(start_time)=? AND DAY(start_time)=?';

#gets information for a particular room
$query_get_rooms='SELECT * FROM room WHERE capacity>=? AND capacity<=?'; #TODO

#gets email of uid
$query_get_email='SELECT email FROM users WHERE huid=?';

#gets every room
$query_get_all_rooms='SELECT * FROM room';

#gets information for a particular room
$query_get_campus_rooms='SELECT room_num,building,projector,capacity 
FROM room,building WHERE id=building AND capacity>=? AND capacity<=? AND region=?';

#gets an event
$query_get_event='SELECT * FROM events WHERE event_id = ?';

#gets intformation for a particular date
$query_get_date=''; #TODO


function getEmailAddr($uid)
{
	$query=$GLOBALS['query_get_email'];
	$result=mysql_safe($query, array($uid));
	return $result;
}

function getAllRooms() {
	$query=$GLOBALS['query_get_all_rooms'];
	$result=mysql_safe($query, array($room,$building,$month,$day));
	return $result;
}

function getRoomRes($room,$building,$month,$day)
{
	$query=$GLOBALS['query_get_room_res'];
	$result=mysql_safe($query, array($room,$building,$month,$day));
	return $result;
}

function authUser($uid,$pwd) {
	$query=$GLOBALS['query_auth_user'];
	$result=mysql_safe($query, array($uid));
	$data=mysql_fetch_array($result);
	if(mysql_num_rows($result)==0)
	{
		$_SESSION['error']="User not in db";
		return false;
	}
	if(strcmp($pwd,$data['pwd']))
	{
		$_SESSION['error']="Invalid password";
		return false;
	}
	else
	{
		set_logged_in($uid,$data['name'], $data['role'], $data['write_events'], $data['reserv_priority']);
		return true;
	}
	
}

function getRooms($capacity,$projector)
{
	$query=$GLOBALS['query_get_rooms'];
	$lbound=$capacity-3;
	$ubound=$capacity+10;
	if($capacity>=50)
		$ubound+=200;
	if(!strcmp($projector,"true"))
	{
		//echo "tasdfasdf";
		//echo $capacity;
		$query .= " AND projector=true";
	}
	$result=mysql_safe($query,array($lbound,$ubound));
	return $result;
}


function getBuildingRooms($building,$capacity,$projector)
{
	$query=$GLOBALS['query_get_rooms'];
	$lbound=$capacity-3;
	$ubound=$capacity+10;
	if($capacity>=50)
		$ubound+=200;
	$query .= " AND building=?";
	if(!strcmp($projector,"true"))
	{
		//echo "tasdfasdf";
		//echo $capacity;
		$query .= " AND projector=true";
	}
	$result=mysql_safe($query,array($lbound,$ubound,$building));
	return $result;
}

function getCampusRooms($campus,$capacity,$projector)
{
	$query=$GLOBALS['query_get_campus_rooms'];
	$lbound=$capacity-3;
	$ubound=$capacity+10;
	if($capacity>=50)
		$ubound+=200;
	if(!strcmp($projector,"true"))
	{
		//echo "tasdfasdf";
		//echo $capacity;
		$query .= " AND projector=true";
	}
	$result=mysql_safe($query,array($lbound,$ubound,$campus));
	return $result;
}

function getBuildings()
{
	$query=$GLOBALS['query_get_buildings'];
	$result=mysql_safe($query,array());
	return $result;
}

function getCampusRegions()
{
	$query=$GLOBALS['query_get_campuses'];
	$result=mysql_safe($query,array());
	return $result;
}

function getEvent($event_id) {
    	$query=$GLOBALS['query_get_event'];
	$result=mysql_safe($query,array($event_id));
        $row = mysql_fetch_array($result);
        return new Event($row);
}

function currentRes() {
    	$query=$GLOBALS['query_res'];
	$result=mysql_safe($query,array());
        while($row = mysql_fetch_array($result)) {
            $events[] = new Event($row);
        }
	return $events;
}

function currentUserRes() 
{
	$query=$GLOBALS['query_curr_user_res'];
	$result=mysql_safe($query, array($_SESSION['uid']));
        $events=array();
        while($row = mysql_fetch_array($result)) {
            $events[] = new Event($row);
        }
	return $events;
}

function delete_res($event_id) {
        $query=$GLOBALS['query_remove_res'];
        mysql_safe($query, array($event_id));
}

function add_res($room, $building, $desc, $start_time, $end_time, $priority=0) {
        $query=$GLOBALS['query_add_res'];
	$event_id=mysql_safe($query, array($_SESSION['uid'], $room, $building, $desc, $start_time, $end_time, $priority));
	return $event_id;
}

function update_res($event_id, $room, $building, $start_time, $end_time) {
        $query=$GLOBALS['query_update_res'];
	mysql_safe($query, array($room, $building, $start_time, $end_time, $event_id));
}

#for finding conflicts.  $ignore_id is for when we update an event,
#it shouldn't conflict with itself
function resDateRangeRoom($start_time, $end_time, $room, $bldg, $ignore_id=-1) {
    $query=$GLOBALS['query_events_date_range_room'];
    $result=mysql_safe($query, array($start_time, $end_time, $room, $bldg, $ignore_id));
    $events=array();
    while($row = mysql_fetch_array($result)) {
        $events[] = new Event($row);
    }
    return $events;
}

function auth_page($filename, $redir) {
    $query=$GLOBALS['query_auth_page'];
    $result=mysql_safe($query, array($filename, get_user_perm()));
    if(mysql_num_rows($result) == 0)
    {
        redirect($redir);
    }
}

function get_links() {
    $query=$GLOBALS['query_get_links'];
    $result=mysql_safe($query, array(get_user_perm()));
    return $result;
}

function begin_transaction() {
    mysql_query('BEGIN');
}

function commit_transaction() {
    mysql_query('COMMIT');
}

function abort_transaction() {
    mysql_query('ROLLBACK');
}

function get_last_id() {
    $row = mysql_fetch_array(mysql_query("SELECT LAST_INSERT_ID() as id"));
    return $row['id'];
}
?>
