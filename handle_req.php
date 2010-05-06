<?
require_once 'inc/util.inc';
if (isset ($_POST['redir'])) {
    $redir = $_POST['redir'];
} else {
    $redir = 'home.php';
}
auth_page(basename(__FILE__), $redir);

begin_transaction();
$event = new Event();
try {

    if (isset($_POST['event_id'])) {
        $event = getEvent($_POST['event_id']);
        $event->change_from_post();
        if (!$event->canEdit()) {
            throw new Exception('Modification not allowed.');
        }
    } else {
        $event->change_from_post();
    }
    if (isset ($_POST['delete'])) {
        $event->delete();
        $_SESSION['error']='Event deleted!';
    } else {
        $event_id = $event->persist();
        $_SESSION['error']='Event '.$event_id.' reserved!';
    }
    commit_transaction();
} catch (Exception $e) {
    abort_transaction();
    $_SESSION['error']='Error while handling reservation request: '.$e->getMessage();
}
redirect($redir);

?>
