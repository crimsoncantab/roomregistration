#!/usr/local/bin/php
<?
# TODO
require_once 'inc/util.inc';
redir_if_logged_in('home.php');

require_once 'inc/html_temp.inc';
template_start_html();
template_head('HRR');
template_start_body('Harvard Room Reservation');
?>
<div>
    Here is some text.
</div>
<?
template_end();
?>