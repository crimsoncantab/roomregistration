<?
require_once 'util.inc';
class Event {
    private $data;

    static public function getEventHeaderRow() {
        echo '<tr>'.
        '<th>User</th><th>Room</th><th>Building</th>'.
        '<th>Request Time</th><th>Desc</th><th>Start Time</th>'.
        '<th>End Time</th><th>Priority</th></tr>';//<th>Recurrence Pattern</th>
    }
    public function  __construct($data, $from_post=false) {
        $this->data = $data;
        if ($from_post) {
            change_from_post();
        }
    }

    #not being used yet
    public function change_from_post() {
            $month= $_POST['month'];
            $day = $_POST['day'];
            $start = $_POST['start_time'];
            $end = $_POST['end_time'];
            $this->data['start_time'] = mktime((int)$start, (int)(($start-floor($start)) * 60), 0, $month, $day);
            $this->data['end_time'] = mktime((int)$end, (int)(($end-floor($end)) * 60), 0, $month, $day);

    }

    public function getId() {
        return $this->data['event_id'];
    }

    public function exists_in_db() {
        return isset ($this->data['event_id']);
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

    public function getHtmlRow() {
        echo '<tr';
        if (can_edit_res($this->getUser())) {
            echo  ' class="clickable" onclick="javascript:window.location=\'change_res.php?event_id='.$this->getId().'\'"';
        }
        echo '><td>'.$this->getUser().'</td><td>'.$this->getRoom().'</td><td>'.$this->getBldg().'</td>'.
        '<td>'.$this->getReqDate().'</td><td>'.$this->getDesc().'</td><td>'.$this->getStart().'</td>'.
        '<td>'.$this->getEnd().'<td>'.$this->getPriority().'</td></td></tr>';//<td>'.$this->getRec().'</td>
    }
}

?>