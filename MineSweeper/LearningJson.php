<?php
				class cell{
				private $mine; 
				private $value; 
				private $beenChecked;
				// Constructor
				public function __construct(){
					$mine = 0;
					$value = 0;
					$beenChecked = 0;
				}
				// Getters and Setter for mine status
				public function get_mine(){
						if ($this->value == -1){
							return true; 
						}
						return false;
					
				}
				public function set_mine($bool){
				$this->value = -1;
				}
				
				// INcrement the number value if not a mine
				public function inc_value(){
					$this->value++;
				}
				public function get_value(){return $this->value;}
				
				// Getters and Setter for been Checked
				public function set_beenChecked($numb){
					$this->beenChecked = $numb; 
				}
				public function get_beenChecked(){
					return $this->beenChecked;
				}
			}
			
			// Initialize the game Board 
			function init_Game(){
			
			//*******************
			// Start of Game Logic 
			//*******************
			
			// Vars 
			$numbOfMines = 10;
			$colCount = 9;
			$rowCount = 9;
			
				for($r =0;  $r <$rowCount; $r++){
					for($c=0; $c<$colCount; $c++){
						$gameBoard[$r][$c] = new cell();
					}// End of Inner for 			
				}// End of outer for 
				// Fill the Game Board with Mines 
				$mc =0;		
				while($mc < $numbOfMines){
				
				$xCord = rand(0,$colCount-1);
				$yCord = rand(0,$rowCount-1);
				
				//if mine is already present
				// If it is start loop again 
				
				
				if($gameBoard[$yCord][$xCord]->get_mine()){
					echo "I am at a cell with a mine already";
					// Mine is already set try agian.
					$mc--;
					continue;
				}			
				
				echo "Placing mine ";
				$gameBoard[$yCord][$xCord]->set_mine(true); 
				
				echo "I am at position Row: " . $yCord ." Col: ".$xCord . "<br>";
				$mc++;
			}// End of outer for 
			
			for($r=0; $r<$rowCount; $r++){
				for($c=0; $c<$colCount; $c++){
					
					// If I am a mine Move to next
					/*if($gameBoard[$r][$c]->get_mine()){
						//$arr [$r . "-" .$c] = $gameBoard[$r][$c]->get_value();
						$arr [$r . "-" .$c] = json_encode($gameBoard[$r][$c],JSON_FORCE_OBJECT);
						continue;
					}*/
					if(!$gameBoard[$r][$c]->get_mine()){
					if($r==0){
						// Skip checking Top
							if($c ==0){
								// First in Col Only Check right
								if ($gameBoard[$r][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}elseif ($c == $colCount-1){
								//Last in Col only check left
								if ($gameBoard[$r][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}elseif($c!=0 && $c != $colCount-1){
								
								// Check Both
								if ($gameBoard[$r][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}
							
							
						}elseif ($r == $rowCount-1){
							// Skipcheck bottom
							if($c ==0){
								// First in Col Only Check right
								if ($gameBoard[$r][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}elseif ($c == $colCount-1){
								//Last in Col only check left
								if ($gameBoard[$r][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}elseif($c!=0 && $c != $colCount-1){
								
								// Check Both
								if ($gameBoard[$r][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}
						}else{
							//Check all three
							if($c ==0){
								// First Col 
								if ($gameBoard[$r][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}elseif ($c == $colCount-1){
								//Last in Col only check left
								if ($gameBoard[$r][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
							}elseif($c!=0 && $c != $colCount-1){
								
								// Check Both
								if ($gameBoard[$r][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r-1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c+1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								if ($gameBoard[$r+1][$c-1]->get_mine()){
									$gameBoard[$r][$c]->inc_value();
								}
								
							}
						}
					}						
				
				// This Creates Dictionary for JSON Conversion. Single Array Format (Row - Col : Value) 
				//$arr [$r . "-" .$c] = $gameBoard[$r][$c]->get_value();
				$arr [$r . "-" .$c] = array("value"=>$gameBoard[$r][$c]->get_value(),"beenChecked"=>$gameBoard[$r][$c]->get_beenChecked());				
				//echo " I have stored an cell object in Associative array";
				}// End Inner 
			}// End Outer 
			//}
			
			
			$JSONBoard = json_encode($arr, JSON_FORCE_OBJECT);
			
			$_SESSION['board']= $JSONBoard;
			} //End Function
			
			session_start();
			
			// Run the Inital Board ONly Once.
			if(!isset($_SESSION['board']) && !isset($_GET['stopMines'])){
				//echo "I am starting init game ";
				init_Game();								
				//echo "I have finished init Game";
			}
			

			if(isset($_GET['cellobjid']) && !isset($_GET['stopMines']))
		{
			// Function setting the cell been checked to true
			// then saving session variable again. 
			
				//$selectedCell = $cRow . '-' . $cCol;
			//	echo "Im in setAndSave";
				//$individualCell;
				$list = json_decode($_SESSION['board'],true);
				
				//$individualCell = $list[$_GET['cellobjid']];
				//$individualCell['beenChecked'] = 1;
				$list[$_GET['cellobjid']]['beenChecked'] = 1;
				//$gameBoard[$cRow][$cCol]->beenChecked = true;
				
				//checkWinner();
				
				//echo $individualCell['value'];
				// Store the Updated game board.
				$_SESSION['board'] = json_encode($list,JSON_FORCE_OBJECT);
				
				
				if ($list[$_GET['cellobjid']]['beenChecked'] == 1 && $list[$_GET['cellobjid']]['value']== -1){
					// they Lost 
						$checkWinner= -1;
				}else{
					$listSize = count($list);
					$cntr = 0;
					// Needs to Check Winner Condition
					foreach($list as $key => $value){
						//echo "Checking Cell " .$key . " and my value is " . $value['value'] . " and Been Checked is: " . $value['beenChecked'];
						if($value['beenChecked']!= 1 && $cntr < $listSize){
								// Not All Cells have benn checked
								// Still Playing
								$checkWinner=0;
								break;
							
						}else{// They win
							$checkWinner = 1;
						}
						$cntr++;
					}
				}
				//echo " I am a winner/ looser" . $checkWinner;				
				
		}

			/*
			if(isset($_GET['cellobjid']))
			{
				// Function setting the cell been checked to true
				// then saving session variable again. 
				
					//$selectedCell = $cRow . '-' . $cCol;
				//	echo "Im in setAndSave";
					$individualCell;
					$list = json_decode($_SESSION['board'],true);
					
					$individualCell = $list[$_GET['cellobjid']];
					$individualCell['beenChecked'] = 1;
					
					//$gameBoard[$cRow][$cCol]->beenChecked = true;
					
					//checkWinner();

					session_start();
				
					for($r =0;  $r <$rowCount; $r++){
						for($c=0; $c<$colCount; $c++){
							//First Check if Mine if not a mine check viewed Value
							if (gameBoard[$r][$c]->mine != -1){
								
								// Checking Been Checked Value 
								if ($gameBoard[$r][$c]->beenChecked == 0){
									// Not All Cells have been checked
									$_SESSION['status'] = 0;
									return;
								}
							}else if (gameBoard[$r][$c]->mine == -1 && $gameBoard[$r][$c]->beenChecked == 1){
								// They Lost the Game
								$_SESSION['status'] = -1;
								return;
							}
							
						}// End Innner
						
					}// end Outer
					
					$_SESSION['status'] = 1;

					echo $individualCell['value'];
					
			}*/


			if(isset($_GET['stopMines']))
			{
				$time = $_GET['stopMines'];
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

				if($checkWinner == -1){				
					// They Lost
					echo "-1";
					session_destroy();
				}elseif($checkWinner == 0){					
					// Still Playing
					echo $list[$_GET['cellobjid']]['value'];					
				}else{					
					// Winner Winner

					echo"100";
					session_destroy();
					
				}
				//echo "Done";
			}
		
			/*if(isset($_GET['showScores']))
			{
				session_start();
				$_SESSION["user_name"] = $user;
				header("Refresh: 1; url = http://cs3750juan.epizy.com/scoresMinesweeper.php",true,301);	

				//echo "<script type='text/javascript'>window.top.location='http://cs3750juan.epizy.com/scoresMinesweeper.php';</script>"
				exit();
				//echo "Failed";

			}*/
			
			// This Function checks winning condition. It will be called after every click in Javascript
			
		/*		session_start();
				
				for($r =0;  $r <$rowCount; $r++){
					for($c=0; $c<$colCount; $c++){
						//First Check if Mine if not a mine check viewed Value
						if (gameBoard[$r][$c]->mine != -1){
							
							// Checking Been Checked Value 
							if ($gameBoard[$r][$c]->beenChecked == 0){
								// Not All Cells have been checked
								$_SESSION['status'] = 0;
								return;
							}
						}else if (gameBoard[$r][$c]->mine == -1 && $gameBoard[$r][$c]->beenChecked == 1){
							// They Lost the Game
							$_SESSION['status'] = -1;
							return;
						}
						
					}// End Innner
					
				}// end Outer
				
				$_SESSION['status'] = 1;*/
?>