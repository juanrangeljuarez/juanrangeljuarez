<html> 
	<head> 
		<style>
			td{
				text-align:      center;
				width:           3em;
				height:          3em;				
			}
		</style>
	</head>
	
	<body onload='timer=setInterval("countUP()", 1000 );'> 
		<form action="#" method="post">
			<button type ="submit" name="logout" value="send to database">Logout</button>			
    	</form>
    	<br/>	
    	Time: <div id="timer_container"></div>
		<p>
			<script type="text/javascript">
			function clearTimer()
				 {
				 	counter = 0;
				 	localStorage.setItem("seconds",counter);
				 }
				  
			</script>
		<?php

			session_start();
			$user = $_SESSION["user_name"];
			echo "Welcome ".$user;

			if (isset($_POST['logout']))
        	{
        			session_start();

        			echo '<script type="text/javascript">',
     					'clearTimer();',
    					 '</script>';
					$_SESSION["user_name"] = "";
					unset($_SESSION['user_name']);
					header("Refresh: 1; url = http://cs3750juan.epizy.com/login.php");		             	
			}
	
			if(isset($_POST['postcounter']))
			{
				$time = $_POST['postcounter'];
				$user = $_SESSION["user_name"];
				
				$servername = "sql304.epizy.com";
				$username = "epiz_23868833";
				$password = "oZwNrrIhSLY3r";
				$dbname =  "epiz_23868833_game";

				$conn = new mysqli($servername, $username,$password,$dbname);

				if($conn->connect_error)
				{
					die("Connection failed:". $conn->connect_error);
				}
				$sql = "SELECT * FROM  GameMines WHERE User = '" . $user . "'";
				$result = $conn->query($sql);
				if($result->num_rows > 0)
				{
					$row = $result->fetch_assoc();
					$idUser = $row['ID'];
					$query = "INSERT INTO Scores (IDName, Score) VALUES ('" . $idUser . "', '" . $time . "')"; 
					mysqli_query($conn,$query);
					echo $idUser." ".$time;
					session_start();
					$_SESSION["user_name"] = $user;
				}

			}

		?>
		<script src="https://code.jquery.com/jquery-1.10.2.js"></script>
		<script>
			function myFunction(obj)
			{
				var clear;
				$.ajax({
				        url: "http://cs3750juan.epizy.com/LearningJson.php",
				        method: "GET",
				        async: false,
				        data: { cellobjid : obj.id },
				        dataType: "text",
				        success: function(data) {
				         	obj.innerHTML = data;
				         	clear = data;
					    }
				});
				if(clear == -1)
				{
					clearTimer();
				}
				
			}
		</script>
		<script src="http://code.jquery.com/jquery-1.10.2.js"></script>
				<script src="http://code.jquery.com/ui/1.11.2/jquery-ui.js"></script>
				<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"></script>
			<script type="text/javascript">
				var counter = 0;
				var timer;
				if(localStorage.getItem("seconds") != null)
				{
					counter = parseInt(localStorage.getItem("seconds"));
				}
				else
				{
				 	counter = 0;
				}
					
				function countUP () {

					 counter = counter + 1;//increment the counter by 1
					 	//display the new value in the div
					 document.getElementById("timer_container").innerHTML = counter;
					localStorage.setItem("seconds",counter);
					 
				 }
				 function stopCounter()
				 {
				 	/*$.post('http://cs3750juan.epizy.com/playGame.php',{postcounter:counter},
				 	function(data) {
				 		//$('#result').html(data);	
				 	});*/
				 	counter = 0;
				 }

				  function stopCounterWin()
				 {
				 	$.post('http://cs3750juan.epizy.com/playGame.php',{postcounter:counter},
				 	function(data) {
				 		//$('#result').html(data);	
				 	});
				 	counter = 0;
				 }
				 function clearTimer()
				 {
				 	counter = 0;
				 	localStorage.setItem("seconds",counter);
				 } 
			</script>
		</p>
		<table id = "GameBoard" border="1" style = "border-collapse: collapse">
			<tr>
				<td id = "0-0" onclick = "myFunction(this)">.</td>
				<td id = "0-1" onclick = "myFunction(this)">.</td>
				<td id = "0-2" onclick = "myFunction(this)">.</td>
				<td id = "0-3" onclick = "myFunction(this)">.</td>
				<td id = "0-4" onclick = "myFunction(this)">.</td>
				<td id = "0-5" onclick = "myFunction(this)">.</td>
				<td id = "0-6" onclick = "myFunction(this)">.</td>
				<td id = "0-7" onclick = "myFunction(this)">.</td>
				<td id = "0-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = '1-0' onclick = "myFunction(this)">.</td>
				<td id = "1-1" onclick = "myFunction(this)">.</td>
				<td id = "1-2" onclick = "myFunction(this)">.</td>
				<td id = "1-3" onclick = "myFunction(this)">.</td>
				<td id = "1-4" onclick = "myFunction(this)">.</td>
				<td id = "1-5" onclick = "myFunction(this)">.</td>
				<td id = "1-6" onclick = "myFunction(this)">.</td>
				<td id = "1-7" onclick = "myFunction(this)">.</td>
				<td id = "1-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "2-0" onclick = "myFunction(this)">.</td>
				<td id = "2-1" onclick = "myFunction(this)">.</td>
				<td id = "2-2" onclick = "myFunction(this)">.</td>
				<td id = "2-3" onclick = "myFunction(this)">.</td>
				<td id = "2-4" onclick = "myFunction(this)">.</td>
				<td id = "2-5" onclick = "myFunction(this)">.</td>
				<td id = "2-6" onclick = "myFunction(this)">.</td>
				<td id = "2-7" onclick = "myFunction(this)">.</td>
				<td id = "2-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "3-0" onclick = "myFunction(this)">.</td>
				<td id = "3-1" onclick = "myFunction(this)">.</td>
				<td id = "3-2" onclick = "myFunction(this)">.</td>
				<td id = "3-3" onclick = "myFunction(this)">.</td>
				<td id = "3-4" onclick = "myFunction(this)">.</td>
				<td id = "3-5" onclick = "myFunction(this)">.</td>
				<td id = "3-6" onclick = "myFunction(this)">.</td>
				<td id = "3-7" onclick = "myFunction(this)">.</td>
				<td id = "3-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "4-0" onclick = "myFunction(this)">.</td>
				<td id = "4-1" onclick = "myFunction(this)">.</td>
				<td id = "4-2" onclick = "myFunction(this)">.</td>
				<td id = "4-3" onclick = "myFunction(this)">.</td>
				<td id = "4-4" onclick = "myFunction(this)">.</td>
				<td id = "4-5" onclick = "myFunction(this)">.</td>
				<td id = "4-6" onclick = "myFunction(this)">.</td>
				<td id = "4-7" onclick = "myFunction(this)">.</td>
				<td id = "4-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "5-0" onclick = "myFunction(this)">.</td>
				<td id = "5-1" onclick = "myFunction(this)">.</td>
				<td id = "5-2" onclick = "myFunction(this)">.</td>
				<td id = "5-3" onclick = "myFunction(this)">.</td>
				<td id = "5-4" onclick = "myFunction(this)">.</td>
				<td id = "5-5" onclick = "myFunction(this)">.</td>
				<td id = "5-6" onclick = "myFunction(this)">.</td>
				<td id = "5-7" onclick = "myFunction(this)">.</td>
				<td id = "5-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "6-0" onclick = "myFunction(this)">.</td>
				<td id = "6-1" onclick = "myFunction(this)">.</td>
				<td id = "6-2" onclick = "myFunction(this)">.</td>
				<td id = "6-3" onclick = "myFunction(this)">.</td>
				<td id = "6-4" onclick = "myFunction(this)">.</td>
				<td id = "6-5" onclick = "myFunction(this)">.</td>
				<td id = "6-6" onclick = "myFunction(this)">.</td>
				<td id = "6-7" onclick = "myFunction(this)">.</td>
				<td id = "6-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "7-0" onclick = "myFunction(this)">.</td>
				<td id = "7-1" onclick = "myFunction(this)">.</td>
				<td id = "7-2" onclick = "myFunction(this)">.</td>
				<td id = "7-3" onclick = "myFunction(this)">.</td>
				<td id = "7-4" onclick = "myFunction(this)">.</td>
				<td id = "7-5" onclick = "myFunction(this)">.</td>
				<td id = "7-6" onclick = "myFunction(this)">.</td>
				<td id = "7-7" onclick = "myFunction(this)">.</td>
				<td id = "7-8" onclick = "myFunction(this)">.</td>
			</tr>
			<tr>
				<td id = "8-0" onclick = "myFunction(this)">.</td>
				<td id = "8-1" onclick = "myFunction(this)">.</td>
				<td id = "8-2" onclick = "myFunction(this)">.</td>
				<td id = "8-3" onclick = "myFunction(this)">.</td>
				<td id = "8-4" onclick = "myFunction(this)">.</td>
				<td id = "8-5" onclick = "myFunction(this)">.</td>
				<td id = "8-6" onclick = "myFunction(this)">.</td>
				<td id = "8-7" onclick = "myFunction(this)">.</td>
				<td id = "8-8" onclick = "myFunction(this)">.</td>
			</tr>
			</table>
		<?php //session_destroy(); ?>
	</body>
</html>