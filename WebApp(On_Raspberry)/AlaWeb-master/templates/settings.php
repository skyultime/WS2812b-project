 			<style> .menuDroite { height:auto; width:175px; float:right; ;} </style> 

<!DOCTYPE html> <html>
    <head>
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
        <meta charset="utf-8" />
        <title>Settings</title>

	 </head>    

<body> <h2> Nous sommes le <?php echo date('d/m/Y'); ?> Il est  <?php echo date('h:i:s'); ?></h2>	
<?php

session_start();
	$connexion = new mysqli("localhost", "gpi2", "root", "projet");
	$date =  date("Y-m-d");
	$maRequete ="SELECT COUNT(*) AS c FROM nb_online WHERE depart like '%$date%' && arrivee like '%$date%'"; 
	$maRequete2 ="SELECT COUNT(DISTINCT ip) AS d FROM nb_online WHERE depart like '%$date%' && arrivee like '%$date%'";
//$result = $connexion->query($maRequete);
$result = mysqli_query($connexion,$maRequete);
$result2 = mysqli_query($connexion,$maRequete2);

if(!$result) {
} else {
//$resultat = $maRequete->fetch_assoc(); // ...
//$nb_connexion = $resultat['count'];
//echo $nb_connexion;
 while($row=mysqli_fetch_assoc($result))
 {
        $nb_connexion=$row['c'];
 }

$result->free();
}

if(!$result2) {
} else {
 while($row=mysqli_fetch_assoc($result2))
{
	$nb_connexion_diff=$row['d'];
}
$result2->free();
}
// on ferme la connexion a la base: 
//$connexion->close();
//mysql_close();

include ("connectes.php");
echo "Nombre de connexions aujourd'hui: ".$nb_connexion;
?></br><?php echo "Nombre de sessions différentes connectées aujourd'hui: ".$nb_connexion_diff;
//Graph
?></br>
<?php
//include("graph.php");
?>
<br><a href="graph.php">Nombre de connexions des 10 derniers jours</a></br>
<br><a href="graph2.php">Durée de connexions des utilisateurs</a></br>
<?php
//include("graph2.php");
?>
</br>
En cas de problème, envoyez-moi un mail...<a href="mailto:fixed@cloudebus.fr">Cliquer ici</a></br>
<?php
include("cloud.html");
?><br><a href="alaLed.php">Retour</a></br> 

</body>

