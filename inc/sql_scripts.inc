<?
#This file lists all the queries needed.
#When a query takes parameters, they should be escaped with ?
#The query should be called with the mysql_safe() function in util.inc,
#along with it's arguments and the link identifier for the mysql connection
#
#an example query:
#$query='INSERT INTO table(col1, col2) values(?,?)';
#
#a call to execute this query:
#mysql_safe($query, $conn, array($var1, $var2));

#authenticates user.  takes username, phash params, returns user info
$query_auth_user=''; #TODO

#register user.  takes username, phash, other varibles..
$query_reg_user=''; #TODO

#add reservation.  takes room info, other variables...
#assumes time/location are available
$query_add_res=''; #TODO

#find reservation(s) during certain time interval and for certain room
#takes room and time interval
#hmm, we might need a little transaction to help us out here.  we have to check
#for availability, then add a reservation if possible, all in one swoop.
$query_curr_res=''; #TODO


?>