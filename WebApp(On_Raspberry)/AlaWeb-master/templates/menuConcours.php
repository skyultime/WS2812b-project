<!DOCTYPE html> <html>
    <head>
        <meta charset="utf-8" />
        <title>Menu user</title>

	 </head>

        

<body> <h1>Users menu</h1>

<?php

session_start();
$_SESSION['numConcours'] = $numConcours;


if (isset ($_SESSION['numeroUtilisateur']) AND $_SESSION['numeroUtilisateur'] > 1) {

?>

<h2><a href = "alaLed.php">WS2812b Controller</a>
<h2><a href = "settings.php">ColorWheel interface</a>
<h2><a href = "Arduino.php">Pair system</a>
<h2><a href = "logout.php.php">Log out</a> !

<?php
}
else if (isset ($_SESSION['numeroUtilisateur']) AND $_SESSION['numeroUtilisateur']=1){
         echo '<body onLoad="alert(\'Accès non autorisé...\')">';
?>

<h2><a href = "logout.php">Exit</a> !

<?php

}
include("cloud.html");
?>
</body>



