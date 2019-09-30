<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Post to PHP Tutorial</title>
<script type="text/javascript" src="jquery.js"></script>
</head>
<body>
<form>
 <input type="text" id="name" placeholder="Enter Your Name..." /><br />
 <input type="text" id="age" placeholder="Enter Your age..." /><br />
 <input type="button" value="Submit" onclick="post();">
</form>

<div id="result"></div>

<script src="http://code.jquery.com/jquery-1.10.2.js"></script>
<script src="http://code.jquery.com/ui/1.11.2/jquery-ui.js"></script>
<script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"></script>

<script type="text/javascript">

function post()
{
 //alert("working");
 var name = $('#name').val();
 var age = $('#age').val();
 
 $.post('http://cs3750juan.epizy.com/testData.php',{postname:name,postage:age},
 function(data){
  $('#result').html(data);
 });
}

</script>
</body>
</html>