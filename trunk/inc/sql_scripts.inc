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

#USER QUERIES
#authenticates user.  takes username, phash params, returns user info
$query_auth_user='SELECT * FROM users NATURAL JOIN priv WHERE huid=?';

#gets email of uid
$query_get_email='SELECT email FROM users WHERE huid=?';

#check webpage permissions against a user.
$query_auth_page='SELECT * FROM pageperm WHERE page=? AND LOCATE(?, perm) != 0';

#get available links
$query_get_links='SELECT page, display FROM pageperm WHERE LOCATE(?, perm) != 0 AND in_nav=true';

#LOCATION QUERIES
#get campuses
$query_get_campuses='SELECT id,name FROM campus';

#get buildings
$query_get_buildings='SELECT id,name FROM building';

#gets information for a particular room
$query_get_rooms='SELECT * FROM room WHERE capacity>=? AND capacity<=?'; #TODO

#gets every room
$query_get_all_rooms='SELECT room_num,building FROM room';

#gets information for a particular room
$query_get_campus_rooms='SELECT room_num,building,projector,capacity 
FROM room,building WHERE id=building AND capacity>=? AND capacity<=? AND region=?';

#EVENT QUERIES A - READS
#get all res
$query_res='SELECT * FROM events ORDER BY start_time';

#get user's current events.
$query_curr_user_res='SELECT * FROM events WHERE huid=? ORDER BY start_time';

#gets reservations for a room based on month and day
$query_get_room_res='SELECT start_time,end_time,description FROM events WHERE room=? AND building=? 
AND MONTH(start_time)=? AND DAY(start_time)=?';

#gets reservations for a room based on day of week
$query_get_room_res_recur='SELECT start_time,end_time,description FROM events WHERE room=? AND building=?
AND (recurring=? OR (recurring=0 AND DAYOFWEEK(start_time)=?))';

#gets an event
$query_get_event='SELECT * FROM events WHERE event_id = ?';

#find reservation(s) during certain time interval and for certain room
#takes room and time interval
$query_events_date_range_room='SELECT * FROM events WHERE'.
        ' FROM_UNIXTIME(?) < end_time'.
        ' AND FROM_UNIXTIME(?) > start_time'.
        ' AND room=? AND building=? AND event_id != ?'.
        ' AND recurring=0';

#gets all recurring events that fall in a time range
#based on day of week, hour, and minute
$query_get_recur_on_date='SELECT * FROM events WHERE '.
        ' TIME(FROM_UNIXTIME(?)) < TIME(end_time)'.
        ' AND TIME(FROM_UNIXTIME(?)) > TIME(start_time)'.
        ' AND room=? AND building=? AND event_id != ?'.
        ' AND recurring=DAYOFWEEK(FROM_UNIXTIME(?))';

#gets all events that fall in a recurrence pattern
#based on day of week, hour, and minute
$query_get_recur_on_pattern='SELECT * FROM events WHERE '.
        ' TIME(FROM_UNIXTIME(?)) < TIME(end_time)'.
        ' AND TIME(FROM_UNIXTIME(?)) > TIME(start_time)'.
        ' AND room=? AND building=? AND event_id != ?'.
        ' AND (recurring=? OR (recurring=0 AND DAYOFWEEK(start_time)=?))';

#moved into above query
//#gets all nonrecurring events that fall in a recurrence pattern
//$query_get_non_recur_in_pattern='SELECT * FROM events WHERE '.
//        ' TIME(FROM_UNIXTIME(?)) < TIME(end_time)'.
//        ' AND TIME(FROM_UNIXTIME(?)) > TIME(start_time)'.
//        ' AND room=? AND building=? AND event_id != ?'.
//        ' AND recurring=0 AND DAYOFWEEK(start_time)=?';


#EVENT QUERIES B - WRITES
#add reservation.  takes room info, other variables...
#assumes time/location are available, returns event_id
$query_add_res='INSERT INTO events(huid,room,building,date_req,description,start_time,end_time,priority, recurring) VALUES'.
        '(?,?,?,NOW(),?,FROM_UNIXTIME(?),FROM_UNIXTIME(?),?,?)';

#delete reservation.
$query_remove_res='DELETE FROM events WHERE event_id = ?';

#update reservation
$query_update_res='UPDATE events SET room = ?, building = ?, start_time = FROM_UNIXTIME(?), end_time = FROM_UNIXTIME(?), description = ?, priority = ? WHERE event_id = ?';


#for finding conflicts.  $ignore_id is for when we update an event,
#it shouldn't conflict with itself
function resDateRangeRoom($start_time, $end_time, $room, $bldg, $ignore_id=-1) {
    $query=$GLOBALS['query_events_date_range_room'].' UNION '.$GLOBALS['query_get_recur_on_date'];
    $params = array($start_time, $end_time, $room, $bldg, $ignore_id, $start_time, $end_time,$room, $bldg, $ignore_id,$start_time);
    $result=mysql_safe($query, $params);
    $events=array();
    while($row = mysql_fetch_array($result)) {
        $events[] = new Event($row);
    }
    return $events;
}

function resDatePatternRoom($start_time, $end_time, $room, $bldg, $day_of_week, $ignore_id=-1) {
    $query=$GLOBALS['query_get_recur_on_pattern'];//.' UNION '.$GLOBALS['query_get_non_recur_in_pattern'];
    $params = array($start_time, $end_time, $room, $bldg, $ignore_id, $day_of_week, $day_of_week);
    $result=mysql_safe($query, $params);
    $events=array();
    while($row = mysql_fetch_array($result)) {
        $events[] = new Event($row);
    }
    return $events;
}

function getEmailAddr($uid) {
    $query=$GLOBALS['query_get_email'];
    $result=mysql_safe($query, array($uid));
    return $result;
}

function getAllRooms() {
    $query=$GLOBALS['query_get_all_rooms'];
    $result=mysql_safe($query);
    return $result;
}

function getRoomRes($room,$building,$month,$day) {
    $query=$GLOBALS['query_get_room_res'];
    $result=mysql_safe($query, array($room,$building,$month,$day));
    return $result;
}
function getRoomResPattern($room,$building,$day_of_week) {
    $query=$GLOBALS['query_get_room_res_recur'];
    $result=mysql_safe($query, array($room,$building,$day_of_week,$day_of_week));
    return $result;
}

function authUser($uid,$pwd) {
    $query=$GLOBALS['query_auth_user'];
    $result=mysql_safe($query, array($uid));
    $data=mysql_fetch_array($result);
    if(mysql_num_rows($result)==0) {
        $_SESSION['error']="User not in db";
        return false;
    }
    if(strcmp($pwd,$data['pwd'])) {
        $_SESSION['error']="Invalid password";
        return false;
    }
    else {
        set_logged_in($uid,$data['name'], $data['role'], $data['write_events'], $data['reserv_priority']);
        return true;
    }

}

function getRooms($capacity,$projector) {
    $query=$GLOBALS['query_get_rooms'];
    $lbound=$capacity-3;
    $ubound=$capacity+10;
    if($capacity>=50)
        $ubound+=200;
    if(!strcmp($projector,"true")) {
        $query .= " AND projector=true";
    }
    $result=mysql_safe($query,array($lbound,$ubound));
    return $result;
}


function getBuildingRooms($building,$capacity,$projector) {
    $query=$GLOBALS['query_get_rooms'];
    $lbound=$capacity-3;
    $ubound=$capacity+10;
    if($capacity>=50)
        $ubound+=200;
    $query .= " AND building=?";
    if(!strcmp($projector,"true")) {
        $query .= " AND projector=true";
    }
    $result=mysql_safe($query,array($lbound,$ubound,$building));
    return $result;
}

function getCampusRooms($campus,$capacity,$projector) {
    $query=$GLOBALS['query_get_campus_rooms'];
    $lbound=$capacity-3;
    $ubound=$capacity+10;
    if($capacity>=50)
        $ubound+=200;
    if(!strcmp($projector,"true")) {
        $query .= " AND projector=true";
    }
    $result=mysql_safe($query,array($lbound,$ubound,$campus));
    return $result;
}

function getBuildings() {
    $query=$GLOBALS['query_get_buildings'];
    $result=mysql_safe($query);
    return $result;
}

function getCampusRegions() {
    $query=$GLOBALS['query_get_campuses'];
    $result=mysql_safe($query);
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
    $result=mysql_safe($query);
    while($row = mysql_fetch_array($result)) {
        $events[] = new Event($row);
    }
    return $events;
}

function currentUserRes() {
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

function add_res($event) {
    $query=$GLOBALS['query_add_res'];
    $params = array($_SESSION['uid'],
            $event->getRoom(), $event->getBldg(), $event->getDesc(),
            $event->getStart(), $event->getEnd(), $event->getPriority());
    if ($event->isRecurring()) {
        foreach ($event->getRec() as $day_of_week) {
            $params[7] = $day_of_week;
            mysql_safe($query, $params);
        }
    }
    else {
        $params[] = $event->getRec();
        mysql_safe($query, $params);
    }
    return get_last_id();
}

function update_res($event) {
    $query=$GLOBALS['query_update_res'];
    $params = array($event->getRoom(), $event->getBldg(),
            $event->getStart(), $event->getEnd(), $event->getDesc(), $event->getPriority(), $event->getId());
    mysql_safe($query, $params);
}

function auth_page($filename, $redir) {
    $query=$GLOBALS['query_auth_page'];
    $result=mysql_safe($query, array($filename, get_user_perm()));
    if(mysql_num_rows($result) == 0) {
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
