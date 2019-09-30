<html>
	<head>
		
	</head>
	<body>
		
		<form action="#" method="post">
			<button type ="submit" name="logout" value="send to database">Logout</button>			
    	</form>
    	<p>
		<?php



					session_start();
					$user = $_SESSION["user_name"];
					echo "Welcome ".$user;

					if (isset($_POST['logout']))
		        	{
		        			session_start();
							$_SESSION["user_name"] = "";
							unset($_SESSION['user_name']);
							header("Refresh: 1; url = http://cs3750juan.epizy.com/login.php");		             	
					}


					$servername = "sql304.epizy.com";
					$username = "epiz_23868833";
					$password = "oZwNrrIhSLY3r";
					$dbname =  "epiz_23868833_game";

					


					$conn = new mysqli($servername, $username,$password,$dbname);

					if($conn->connect_error)
					{
						die("Connection failed:". $conn->connect_error);
					} 
					session_start();
					$name   = $_SESSION['user_name'];
					$text =  $_SESSION["user_text"];
					echo $text;

					$sql = "SELECT GM.User AS User, S.Score FROM  Scores AS S INNER JOIN GameMines AS GM ON S.IDName = GM.ID ORDER BY Score LIMIT 0 , 10";
					$result = $conn->query($sql);

					if ($result->num_rows > 0) 
					{
						echo "<h2>Top Players</h2>";
						$position = 1;
					    echo "<table border='1'>
						<tr>
						<th>Position</th>
						<th>Name</th>
						<th>Time</th>
						</tr>";
					    while($row = $result->fetch_assoc()) {
					        echo "<tr>";
					        echo "<td>" . $position . "</td>";
							echo "<td>" . $row['User'] . "</td>";
							echo "<td>" . $row['Score'] . "</td>";
							echo "</tr>";
							$position++;	
					    }
					    echo "</table>";
					} else 
					{
					    echo "0 results";
					}
					session_start();
					$_SESSION["user_name"] = $name;
					//echo "Name Score ",$name;
					$conn->close();

		?>
	</p>
</body>
</html>