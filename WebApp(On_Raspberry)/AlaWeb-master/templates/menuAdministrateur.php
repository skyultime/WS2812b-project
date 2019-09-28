<head> <title>Menu Admin.</title> </head> 

<body> <h1>Page restreint aux administrateurs du système !</h1> 

<?php

session_start();

$num = $_SESSION['numeroUtilisateur'];

if (isset ($_SESSION['numeroUtilisateur']) AND $num == 1) {
     
?>

<h2><a href = "alaLed.php">WS2812b Controller</a>
<h2><a href = "Arduino.php">Pair system</a>
<h2><a href = "settings.php">Parameters</a>
<h2><a href = "logout.php.php">Log out</a> !

<?php
}
else if (isset ($_SESSION['numeroUtilisateur']) AND $num > 1){
	 echo '<body onLoad="alert(\'Accès non autorisé...\')">';
?>

<h2><a href = "logout.php">Exit</a> !

<?php
	
}
include("cloud.html");
?>
</body>
