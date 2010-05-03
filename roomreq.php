<?
	require_once 'inc/html_temp.inc';
	$role = get_user_perm();
        template_start(basename(__FILE__), 'HRR', 'Harvard Room Reservation - Request Room', '.');
?>
<div>
	<? print_r($_SESSION) ?><br/>
    Enter search criteria (* required):
    <form action="room_res.php" method="get" id="login_form">
        <table>
            <tr>
                <td>
                    <span>*Capacity</span>
                    <input type="text" name="uid" value="" size="12"/>
                </td>
            </tr>
            <tr>
                <td>*Projector: 
					<input type="radio" name="projector" value="false" checked>No
					<input type="radio" name="projector" value="true">Yes
                </td>
            </tr>
            <tr>
                <td>*Time: 
					<input type="radio" name="projector" value="false" checked>No
					<input type="radio" name="projector" value="true">Yes
                </td>
            </tr>
            <tr>
                <td>
                    <input type="submit" value="Login" name="sub"/>
                </td>
            </tr>
        </table>
    </form>
</div>

<?
	template_end();
?>
