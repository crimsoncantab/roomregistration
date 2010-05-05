<?
require_once 'inc/util.inc';
if (isset ($_POST['redir'])) {
    $redir = $_POST['redir'];
} else {
    $redir = 'home.php';
}
auth_page(basename(__FILE__), $redir);

try {
    $is_update = isset($_POST['event_id']);
    if ($is_update) {
        $event_id = $_POST['event_id'];
        $old_event = getEvent($event_id);
        if (!can_edit_res($old_event->getUser())) {
            $_SESSION['error'] = 'Modification not allowed.';
            redirect($redir);
        }
    } else {
        $event_id = -1;
    }

    #need to check that start < end

    $month= $_POST['month'];
    $day = $_POST['day'];
    $room = $_POST['room'];
    $building = $_POST['building'];
    $desc = $_POST['description'];
    $start = $_POST['start_time'];
    $end = $_POST['end_time'];
    $priority = $_POST['priority'];
    $start_time = mktime((int)$start, (int)(($start-floor($start)) * 60), 0, $month, $day);
    $end_time = mktime((int)$end, (int)(($end-floor($end)) * 60), 0, $month, $day);
} catch (Exception $e) {
    $_SESSION['error']='Bad arguments: '.$e->getMessage();
    redirect($redir);
}

begin_transaction();
try {
    $events = resDateRangeRoom($start_time, $end_time, $room, $building, $event_id);
    if (count($events) != 0) {
        abort_transaction();
        $_SESSION['error']='Time not available.';
    } else {
        if ($is_update) {
            update_res($event_id, $room, $building, $start_time, $end_time);
        } else {
            add_res($room, $building, $desc, $start_time, $end_time);
            $event_id=get_last_id();
        }
        $_SESSION['error']='Event '.$event_id.' added!';
        commit_transaction();
    }
} catch (Exception $e) {
    abort_transaction();
    $_SESSION['error']='Error while handling reservation request: '.$e->getMessage();
}
redirect($redir);

?>
