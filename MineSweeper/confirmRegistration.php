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
        			$repeatedPassword = $_POST['encryptedPasswordRepeated'];

       			
					$sql = "SELECT User FROM  GameMines WHERE User = '" . $user . "'";
					$result = $conn->query($sql);
		
					if($result->num_rows > 0)
					{
						session_start();
							$userExists = "failed";
							$_SESSION["user_exists"] = $userExists;
							header("Refresh: 1; url = http://cs3750juan.epizy.com/newUser.php");
					}
					else
					{
        	
	        			$password = hash('sha256', $password);
	        			$repeatedPassword = hash('sha256', $repeatedPassword);
	        			
	        			$salted = "$3%hj3kff$df".$password."6$#$hssjs83732";
	        			$repeatSalted = "$3%hj3kff$df".$repeatedPassword."6$#$hssjs83732";

						$password = hash('sha256', $salted);
						$repeatedPassword = hash('sha256',$repeatSalted);
						if($password == $repeatedPassword)
						{
							$query = "INSERT INTO GameMines (User, Password) VALUES ('" . $user . "', '" . $password . "')";
							if (mysqli_query($conn,$query))
			                {
			                	session_start();
					    		$_SESSION["user_name"] = $user;
					    		header("Refresh: 1; url = http://cs3750juan.epizy.com/playGame.php");
			                }
						}
						else
						{
							session_start();
							$status = "failed";
							$_SESSION["user_status"] = $status;
							header("Refresh: 1; url = http://cs3750juan.epizy.com/newUser.php");
					
						}
					}		               
			}
			
			$conn->close();

?>
