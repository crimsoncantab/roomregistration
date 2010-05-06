<?
require_once 'util.inc';
class Event {
    private $data;
    private $has_conflicts;
    private $to_evict;

    static public function getEventHeaderRow() {
        echo '<tr>'.
                '<th>User</th><th>Room</th><th>Building</th>'.
                '<th>Request Time</th><th>Desc</th><th>Start Time</th>'.
                '<th>End Time</th><th>Priority</th></tr>';//<th>Recurrence Pattern</th>
    }
    public function  __construct($sql_row=false, $change_from_post = false) {
        $this->to_evict = array();
        $this->has_conflicts = NULL;
        if ($sql_row) {
            $this->data = $sql_row;
        } else {
            $this->data = array();
        }
        if ($change_from_post) $this->change_from_post();
    }

    public function change_from_post() {
        if (isset ($_POST['description'])) {
            $this->data['description'] = $_POST['description'];
        }
        if (isset ($_POST['priority'])) {
            $priority = $_POST['priority'];
            $priority = min(array(max(array($priority, 1)), $_SESSION['max_priority']));
            $this->data['priority'] = $priority;
        }
        if (isset ($_POST['room'])) {
            $this->data['room'] = $_POST['room'];
            if (isset ($_POST['building'])) {
                $this->data['building'] = $_POST['building'];
            }
        }
        if (isset ($_POST['start_time'])) {
            $month= $_POST['month'];
            $day = $_POST['day'];
            $start = $_POST['start_time'];
            $end = $_POST['end_time'];
            if ($start == $end) throw new Exception('Start and End Date cannot be the same');
            else if ($start > $end) {
                $temp = $end;
                $end = $start;
                $start = $temp;
            }
            if ($start < $GLOBALS['beg'] || $end > $GLOBALS['end'] || $month < 1 ||
                    $month > 12 || $day < 1 || $day > 31) throw new Exception('Dates out of range.');
            $this->data['start_time'] = mktime((int)$start, (int)(($start-floor($start)) * 60), 0, $month, $day);
            $this->data['end_time'] = mktime((int)$end, (int)(($end-floor($end)) * 60), 0, $month, $day);
        }
        $id = $this->getId();
        if (!isset($id)) { #this is a new event
            $this->data['huid'] = $_SESSION['uid'];
            $this->data['event_id'] = NULL;
        }
    }

    public function canEdit() {
        return can_edit_res($this->getUser());
    }

    public function getId() {
        if (!isset ($this->data['event_id'])) return NULL;
        return $this->data['event_id'];
    }

    public function exists_in_db() {
        return !is_null($this->getId());
    }

    public function getUser() {
        return $this->data['huid'];
    }

    public function getRoom() {
        return $this->data['room'];
    }

    public function getBldg() {
        return $this->data['building'];
    }

    public function getReqDate() {
        return $this->data['date_req'];
    }

    public function getDesc() {
        return $this->data['description'];
    }

    public function getStart() {
        return $this->data['start_time'];
    }

    public function getEnd() {
        return $this->data['end_time'];
    }

    public function getPriority() {
        return $this->data['priority'];
    }

    public function getRec() {
        return $this->data['recurring'];
    }

    public function getHtmlRow($use_default_edit=true) {
        echo '<tr';
        if ($use_default_edit && can_edit_res($this->getUser())) {
            echo  ' class="clickable" onclick="javascript:window.location=\'change_res.php?event_id='.$this->getId().'\'"';
        }
        echo '><td>'.$this->getUser().'</td><td>'.$this->getRoom().'</td><td>'.$this->getBldg().'</td>'.
                '<td>'.$this->getReqDate().'</td><td>'.$this->getDesc().'</td><td>'.$this->getStart().'</td>'.
                '<td>'.$this->getEnd().'</td><td>'.$this->getPriority().'</td></tr>';//<td>'.$this->getRec().'</td>
    }

    #only true if we can't evict someone
    public function hasConflicts() {
        if (!isset($this->has_conflicts)) { //do logic only once
            $events = resDateRangeRoom($this->getStart(), $this->getEnd(), $this->getRoom(), $this->getBldg(), $this->getId());
//            print_r($events);die();
            foreach ($events as $event) {
                if ($event->getPriority() < $this->getPriority()) {
                    $this->to_evict[] = $event;
                } else {
                    $this->has_conflicts = true;
                    break;
                }
            }
        }
        return $this->has_conflicts;
    }


    public function delete() {
        delete_res($this->getId());
        #notify user
    }
    public function persist() {

        if (!$this->hasConflicts()) {
            foreach ($this->to_evict as $event) {
                $event->delete();
            }
            if ($this->exists_in_db()) {
                update_res($this->getId(), $this->getRoom(), $this->getBldg(), $this->getStart(), $this->getEnd());
            } else {
                add_res($this->getRoom(), $this->getBldg(), $this->getDesc(), $this->getStart(), $this->getEnd(), $this->getPriority());
                $this->data['event_id'] = get_last_id();
            }
        } else {
            throw new Exception('Conflicts with other events');
        }
        #notify user

        return $this->getId();
    }

}

?>