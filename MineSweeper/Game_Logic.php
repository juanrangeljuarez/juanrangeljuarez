<html> 
	<head> 
	</head>
	
	<body> 
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
			$colCount = 15;
			$rowCount = 15;
			
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
			
			
			$JSONBoard = json_encode($arr,JSON_FORCE_OBJECT);
			
			$_SESSION['board']= $JSONBoard;
			} //End Function
			
			session_start();
			
			// Run the Inital Board ONly Once.
			if(!isset($_SESSION['board'])){
				//echo "I am starting init game ";
				init_Game();				
				//echo "I have finished init Game";
			}
			
			
			// Function setting the cell been checked to true
			// then saving session variable again. 
			
			function setAndSave($cRow, $cCol){
				$selectedCell = $cRow . '-' . $cCol;
				$individualCell;
				$list = json_decode($_SESSION['board'],true);
				
				$individualCell = $list[selectedCell];
				$individualCell['beenChecked'] = 1;
				
				//$gameBoard[$cRow][$cCol]->beenChecked = true;
				
				checkWinner();
				
				// If Session is not win or loose update Table 
				
			}
			
			// This Function checks winning condition. It will be called after every click in Javascript
			function checkWinner(){
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
				
			}
			
			
			
			
			// $list = json_decode($_SESSION['board'],true);
			 //var_dump($list);
			//$x = $list['0-0'];
			//echo " THis is before the specific Value <br>";
			//var_dump($x);
			//$x['beenChecked'] = 1;
			//echo $x["beenChecked"];
			//echo json_decode($_SESSION['board']);
			//session_destroy();
		?>
	</body>
</html>