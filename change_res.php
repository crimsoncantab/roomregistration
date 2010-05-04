<?
	require_once 'inc/util.inc';
        require_once 'inc/sql_scripts.inc';
        auth_page(basename(__FILE__), get_user_perm(), 'home.php');
        redirect('master_view.php');
?>
