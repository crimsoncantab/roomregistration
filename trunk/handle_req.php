<?
require_once 'util.inc';
require_once 'sql_scripts.inc';
if (isset ($_POST['redir'])) {
    $redir = $_POST['redir'];
} else {
    $redir = 'home.php';
}
auth_page(basename(__FILE__), $redir);

try {
    echo (234.34 % 1);
    $month= $_POST['month'];
    $day = $_POST['day'];
    $room = $_POST['room'];
    $building = $_POST['building'];
    $desc = $_POST['description'];
    $start = $_POST['start_time'];
    $end = $_POST['end_time'];
    $start_time = mktime((int)$start, ($start % 1) * 60, 0, $month, $day);
    $end_time = mktime((int)$end, ($end % 1) * 60, 0, $month, $day);
} catch (Exception $e) {
    $_SESSION['error']='Bad arguments: '.$e->getMessage();
    redirect($redir);
}

begin_transaction();
try {
    $events = resDateRangeRoom($start_time, $end_time, $room, $building);
    if (count($events) != 0) {
        abort_transaction();
        $_SESSION['error']='Time not available.';
    } else {
        $event_id = add_res($room, $building, $desc, $start_time, $end_time);
        $_SESSION['error']='Event '.$event_id.' added!';
        commit_transaction();
    }
} catch (Exception $e) {
    abort_transaction();
    $_SESSION['error']='Error while handling reservation request: '.$e->getMessage();
}
redirect($redir);

?>