<?
require_once 'util.inc';
require_once 'sql_scripts.inc';
class Event {
    private $data;
    private $has_conflicts;
    private $to_evict;

    static public function getEventHeaderRow() {
        echo '<tr>'.
                '<th>User</th><th>Room</th><th>Building</th>'.
                '<th>Request Time</th><th>Desc</th><th>Start Time</th>'.
                '<th>End Time</th><th>Priority</th><th>Recurrence Pattern</th></tr>';
    }
    public function  __construct($sql_row=false, $change_from_post = false) {
        $this->to_evict = array();
        $this->has_conflicts = NULL;
        if ($sql_row) {
            $this->data = $sql_row;
            $this->data['start_time'] = strtotime( $this->data['start_time'] );
            $this->data['end_time'] = strtotime( $this->data['end_time'] );
        } else {
            $this->data = array();
        }
        if ($change_from_post) $this->change_from_post();
    }

    public function change_from_post() {
        $id = $this->getId();
        if (!isset($id)) { #this is a new event
            $this->data['huid'] = $_SESSION['uid'];
            $this->data['event_id'] = NULL;
            #can't change recurring on old events
            if (isset ($_POST['recurring'])) {
                $this->data['recurring']=$_POST['recurring'];
            } else {
                $this->data['recurring'] = 0;
            }
        }
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
            $start = $_POST['start_time'];
            $end = $_POST['end_time'];
            if ($start == $end) throw new Exception('Start and End Date cannot be the same');
            else if ($start > $end) {
                $temp = $end;
                $end = $start;
                $start = $temp;
            }
            if ($start < $GLOBALS['beg'] || $end > $GLOBALS['end']) throw new Exception('Dates out of range.');
            $start_min = (int)(($start-floor($start)) * 60);
            $start = (int) $start;
            $end_min = (int)(($end-floor($end)) * 60);
            $end = (int) $end;
            if ($this->isRecurring()) {
                $this->data['start_time'] = mktime($start, $start_min, 0, 0, 0, 0);
                $this->data['end_time'] = mktime($end, $end_min, 0, 0, 0, 0);
            } else {
                $month= $_POST['month'];
                $day = $_POST['day'];
                if ($month < 1 || $month > 12 || $day < 1 || $day > 31) throw new Exception('Dates out of range.');
                $this->data['start_time'] = mktime($start, $start_min, 0, $month, $day);
                $this->data['end_time'] = mktime($end, $end_min, 0, $month, $day);
            }
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

    public function getStartFormatted() {
        if ($this->isRecurring()) {
            return date("g:i a",$this->getStart());
        }
        return date("F j, Y, g:i a",$this->getStart());
    }

    public function getEndFormatted() {
        return date("g:i a",$this->getEnd());
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
    private static function retDayOfWeek($num) {
        if ($num==0) return 'None';
        if ($num==1) return 'Sunday';
        if ($num==2) return 'Monday';
        if ($num==3) return 'Teusday';
        if ($num==4) return 'Wednesday';
        if ($num==5) return 'Thursday';
        if ($num==6) return 'Friday';
        return 'Saturday';
    }

    public function getRecFormatted() {
        return Event::retDayOfWeek( $this->getRec());
    }

    public function isRecurring() {
        return $this->data['recurring'] != 0;
    }

    public function getHtmlRow($use_default_edit=true) {
        echo '<tr';
        if ($use_default_edit && can_edit_res($this->getUser())) {
            echo  ' class="clickable" onclick="javascript:window.location=\'change_res.php?event_id='.$this->getId().'\'"';
        }
        echo '><td>'.$this->getUser().'</td><td>'.$this->getRoom().'</td><td>'.$this->getBldg().'</td>'.
                '<td>'.$this->getReqDate().'</td><td>'.$this->getDesc().'</td><td>'.$this->getStartFormatted().'</td>'.
                '<td>'.$this->getEndFormatted().'</td><td>'.$this->getPriority().'</td><td>'.$this->getRecFormatted().'</td></tr>';
    }

    private function checkForConflicts($events) {
        foreach ($events as $event) {
            if ($event->getPriority() < $this->getPriority()
                    && ($this->isRecurring() || !$event->isRecurring())) {
                $this->to_evict[] = $event;
            } else {
                throw new Exception('Time not available.');
            }
        }
    }

    #only true if we can't evict someone
    private function hasConflicts() {
        if (!isset($this->has_conflicts)) { //do logic only once
            if ($this->isRecurring()) {
                foreach ($this->getRec() as $day_of_week) {
                    $events = resDatePatternRoom($this->getStart(), $this->getEnd(), $this->getRoom(), $this->getBldg(), $day_of_week, $this->getId());
                    $this->checkForConflicts($events);
                }
            } else {
                $events = resDateRangeRoom($this->getStart(), $this->getEnd(), $this->getRoom(), $this->getBldg(), $this->getId());
                $this->checkForConflicts($events);
            }
        }
        $this->has_conflicts = false;
        return $this->has_conflicts;
    }


    public function delete() {
        delete_res($this->getId());
        $this->notify_user('deleted');
    }
    public function persist() {

        if (!$this->hasConflicts()) {
            foreach ($this->to_evict as $event) {
                $event->delete();
            }
            if ($this->exists_in_db()) {
                update_res($this);
                $this->notify_user('modified');
            } else {
                $this->data['event_id'] = add_res($this);
                $this->notify_user('added');
            }
        } else {
            throw new Exception('Conflicts with other events');
        }

        return $this->getId();
    }


    private function notify_user($operation) {
        $message = 'The following event has been '.$operation.":\n";
        $message .= 'Description: '.$this->getDesc()."\n";
        $message .= 'Time: '.$this->getStartFormatted().' to '.$this->getEndFormatted()."\n";
        $message .= 'Room: '.$this->getRoom().' Building: '.$this->getBldg()."\n";
        if ($this->isRecurring()) $message .= 'Recurrence Pattern: ';
        {
            if (is_array($this->getRec())) {
                foreach($this->getRec() as $rec) {
                    $message .= date('l', $rec).' ';
                }
            }
            else $message .= $this->getRecFormatted();
        }
        $message .="\n\n".'The user that '.$operation.' the event: '.$_SESSION['username'];

        $subj = 'Room Reservation - event '.$operation;
        email($subj, $this->getUser(), $message);
    }
}


?>