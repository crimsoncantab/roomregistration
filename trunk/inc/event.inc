<?
require_once 'util.inc';
class Event {
    private $data;

    static public function getEventHeaderRow() {
        echo '<tr>'.
        '<th>User</th><th>Room</th><th>Building</th>'.
        '<th>Request Time</th><th>Desc</th><th>Start Time</th>'.
        '<th>End Time</th><th>Recurrence Pattern</th></tr>';
    }
    public function  __construct($sql_row) {
        $this->data = $sql_row;
    }

    private function getId() {
        return $this->data['event_id'];
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
        '<td>'.$this->getEnd().'</td><td>'.$this->getRec().'</td></tr>';
    }
}

?>