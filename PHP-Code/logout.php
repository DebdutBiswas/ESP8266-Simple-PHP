<?php
	session_start();
	include 'connectdb.php';

	if(isset($_SESSION['user_id']))
	{
		session_destroy();

		//mysqli_close($conn);
		mysqli_close($link);

		header('Location: login.html',true,301);
	}
	else
	{
		//echo "<h1>You have to login first!</h1>";
		
		//header('Refresh:0.5; url=login.html');
		header('Location: login.html?LogoutAttempt="failed"',true,301);
	}
?>