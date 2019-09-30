<html>
	<head>
		
		<title>Login</title>
		
	</head>
	<body>
		

		<p>
<?php

			$servername = "sql304.epizy.com";
			$username = "epiz_23868833";
			$password = "oZwNrrIhSLY3r";
			$dbname =  "epiz_23868833_game";

			$conn = new mysqli($servername, $username,$password,$dbname);

			if($conn->connect_error)
			{
				die("Connection failed:". $conn->connect_error);
			} 
			
			
			if (isset($_POST['login2']))
        	{
        			$user = $_POST['username'];
        			$password   = $_POST['encryptedPassword'];

        			$password = hash('sha256', $password);
        			$salted = "$3%hj3kff$df".$password."6$#$hssjs83732";
					$password = hash('sha256', $salted);  

					$sql = "SELECT User,Password FROM  GameMines WHERE User = '" . $user . "' AND Password = '" . $password . "'";
					$result = $conn->query($sql);
					if ($result->num_rows > 0) 
					{
						
					    session_start();
					    $_SESSION["user_name"] = $user;
					    header("Refresh: 1; url = http://cs3750juan.epizy.com/playGame.php");
					} 
					else
					{
						session_start();
							$login = "failed";
							$_SESSION["user_login"] = $login;
							header("Refresh: 1; url = http://cs3750juan.epizy.com/login.php");
					}

			}
			$conn->close();

?>
</p>
	</body>
</html>