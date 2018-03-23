<?php
	//$host_name = "rootdb.cqbr0bmbwpy6.ap-south-1.rds.amazonaws.com";
	$host_name = "localhost";
	$user_name = "root";
	$password = "db_password";
	$db_name = "rootdatabase";
	$db_port = 3306;
	$db_socket = "TCP";
	//$CLIENT_SSL_FLAG = MYSQLI_CLIENT_SSL;
	//$CLIENT_SSL_DONT_VERIFY_FLAG = MYSQLI_CLIENT_SSL_DONT_VERIFY_SERVER_CERT;
	/*
	$ssl_ca = "/rdsdbdata/rds-metadata/ca-cert.pem";
	$ssl_ca_path = null;
	$ssl_cert = "/rdsdbdata/rds-metadata/server-cert.pem";
	$ssl_key = "/rdsdbdata/rds-metadata/server-key.pem";
	$ssl_ciphers = null;
	*/
	//$conn = mysqli_connect($host_name,$user_name,$password,$db_name,$db_port);
	$link = mysqli_init();
	//mysqli_ssl_set($link,$ssl_key,$ssl_cert,$ssl_ca,$ssl_ca_path,$ssl_ciphers);
	//$conn = mysqli_real_connect($link,$host_name,$user_name,$password,$db_name,$db_port,$db_socket,$CLIENT_SSL_FLAG);
	$conn = mysqli_real_connect($link,$host_name,$user_name,$password,$db_name,$db_port,$db_socket);
	
	if(!$conn)
	{
		die("Connection failed: ".mysqli_connect_error());
	}
	else
	{
		//echo "Connection estrablished successfully!";
	}
?>