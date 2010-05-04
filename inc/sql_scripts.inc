<?
require_once 'util.inc';
require_once 'vars.inc';
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
$query_auth_user='SELECT * FROM users WHERE huid=?';

#get user's current events.
$query_curr_user_res='SELECT * FROM events WHERE huid=?';

#check webpage permissions against a user.
$query_auth_page='SELECT * FROM pageperm WHERE page=? AND LOCATE(?, perm) != 0';

#get available links
$query_get_links='SELECT page, display FROM pageperm WHERE LOCATE(?, perm) != 0 AND in_nav=true';

#get campuses
$query_get_campuses='SELECT id,name FROM campus';

#get buildings
$query_get_buildings='SELECT id,name FROM building';

#add reservation.  takes room info, other variables...
#assumes time/location are available
$query_add_res=''; #TODO

#find reservation(s) during certain time interval and for certain room
#takes room and time interval
#hmm, we might need a little transaction to help us out here.  we have to check
#for availability, then add a reservation if possible, all in one swoop.
$query_curr_res=''; #TODO
$query_get_room_res='SELECT start_time,end_time FROM events WHERE room=? AND building=?';

#gets information for a particular room
$query_get_rooms='SELECT * FROM room WHERE capacity>=? AND capacity<=?'; #TODO

#gets information for a particular room
$query_get_campus_rooms='SELECT room_num,building,projector,capacity 
FROM room,building WHERE id=building AND capacity>=? AND capacity<=? AND region=?';

#gets intformation for a particular date
$query_get_date=''; #TODO


function getRoomRes($room,$building)
{
	$query=$GLOBALS['query_get_room_res'];
	$result=mysql_safe($query, array($room,$building));
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
		set_logged_in($uid,$data['name']);
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

function get_user_perm() {
    if (is_logged_in()) {
        $query=$GLOBALS['query_auth_user'];
        $result=mysql_safe($query, array($_SESSION['uid']));
        if(mysql_num_rows($result)==0) #shouldn't happen
	{
		$_SESSION['error']="Current session not found in database.";
		return $GLOBALS['no_user_perm'];
	}
	else
	{
		$data = mysql_fetch_array($result);
                return $data['role'];
	}
    }
    else {
        return $GLOBALS['no_user_perm'];
    }
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

function currentUserRes($uid) 
{
	$query=$GLOBALS['query_curr_user_res'];
	$result=mysql_safe($query, array($uid));
	return $result;	
}

function auth_page($filename, $role, $redir) {
    $query=$GLOBALS['query_auth_page'];
    $result=mysql_safe($query, array($filename, $role));
    if(mysql_num_rows($result) == 0)
    {
        redirect($redir);
    }
}

function get_links($role) {
    $query=$GLOBALS['query_get_links'];
    $result=mysql_safe($query, array($role));
    return $result;
}
?>
