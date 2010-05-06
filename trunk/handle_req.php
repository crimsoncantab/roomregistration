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
            $_SESSION['error'] = 'Modification not allowed.';
            redirect($redir);
        }
    } else {
        $event->change_from_post();
    }

} catch (Exception $e) {
    $_SESSION['error']='Bad arguments: '.$e->getMessage();
    redirect($redir);
    abort_transaction();
}

try {
    if (isset ($_POST['delete'])) {
        $event->delete();
        commit_transaction();
        $_SESSION['error']='Event deleted!';
    }
    else if ($event->hasConflicts()) {
        abort_transaction();
        $_SESSION['error']='Time not available.';
    } else {
        $event_id = $event->persist();
        commit_transaction();
        $_SESSION['error']='Event '.$event_id.' reserved!';
    }
} catch (Exception $e) {
    abort_transaction();
    $_SESSION['error']='Error while handling reservation request: '.$e->getMessage();
}
redirect($redir);

?>
