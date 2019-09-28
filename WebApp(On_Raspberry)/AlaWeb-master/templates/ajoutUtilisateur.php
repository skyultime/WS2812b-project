<style> .menuDroite { height:auto; width:175px; float:right; ;} </style> 

<!DOCTYPE html> <html>
    <head>
        <meta charset="utf-8" />
        <title>Ajouter un utilisateur</title>

	 </head>

        

<body> <h1>Page restreint aux administrateurs du système !</h1>

<?php

session_start();

$num = $_SESSION['numeroUtilisateur'];

if (isset ($_SESSION['numeroUtilisateur']) AND $num == 1) {

?>
	<?php include("inscription.php")?>

<?php
}
else if (isset ($_SESSION['numeroUtilisateur']) AND $num > 1){
         echo '<body onLoad="alert(\'Accès non autorisé...\')">';
?>

<h2><a href = "site.php">Retourner à l'accueil</a> !

<?php

}
include("cloud.html");
?>
</body>



