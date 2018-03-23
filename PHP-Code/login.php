<?php
	session_start();
	include 'connectdb.php';

	$user_name = $_POST['user_name'];
	$password = $_POST['password'];
	
	$sql = "SELECT * FROM User_Account WHERE user_name='$user_name' AND password='$password'";
	//$result = mysqli_query($conn,$sql);
	$result = mysqli_query($link,$sql);
	
	//mysqli_close($conn);
	//mysqli_close($link);

	if(!$row=mysqli_fetch_assoc($result))
	{
		session_destroy();
		header('Location: login.html?LoginAttempt="failed"',true,301);
	}
	else
	{
		//echo "You are logged in!";
		$_SESSION['user_id'] = $row['user_id'];
		$_SESSION['user_name'] = $row['user_name'];

		if(isset($_SESSION['user_id']))
		{
			header('Location: status.html',true,301);
		}
		else
		{
			//header('Location: login.php');
		}
	}
?>