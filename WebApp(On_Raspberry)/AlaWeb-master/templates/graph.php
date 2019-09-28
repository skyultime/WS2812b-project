<?php
 
$connexion = new mysqli("localhost", "gpi2", "root", "projet");
if ($connexion->connect_errno) {
//printf("´Echec de la connexion : %s %s",$connexion->connect_errno, $connexion->connect_error);
exit();
}

// on s´electionne le jeu de caract`eres
$connexion->set_charset("utf8");
// requete `a la base de donn´ees :
$maRequete  = "SELECT AVG(TO_SECONDS(depart)- TO_SECONDS(arrivee)) AS dur ,depart,arrivee,count(ip) AS ip FROM nb_online GROUP BY DAY(depart) ORDER BY MONTH(depart), DAY(depart)";

$result = $connexion->query($maRequete);
if(!$result) {
//echo "la requete ne s’est pas executee";
} else {
//echo "la requete s’est bien passee";
$resultat = $result->fetch_assoc(); // ...
$tbl=array(); // pour créer le tableau 
$tbl2=array(); // pour créer le tableau 
$compteur = 0;
while($resultat){
  ?> <br/>
  <?php 	  
  echo "Connexion le : ".$resultat["depart"];
?></br>
<?php
  echo "Nombre de connexions à ce jour: ".$resultat["ip"];
?></br>
<?php 
  //$duree = $resultat["arrivee"]-$resultat["depart"]
  //echo "Durée moyenne de connexions à ce jour: ".$resultat["dur"];
?>
<?php

  $tbl[$compteur]= $resultat["depart"];
  $tbl2[$compteur]= $resultat["ip"];
  if ($resultat["dur"]>0){
      $tbl3[$compteur]= $resultat["dur"];
  }else{
     $tbl3[$compteur]= 0;
  }
  //$temps = date('H:i:s',$tbl3[$compteur]);
  echo "Durée moyenne de connexions à ce jour: ".((int)($tbl3[$compteur]/60))." min";
  ?></br>
  <?php

  $compteur = $compteur +1;
  $resultat = $result->fetch_assoc(); // ...

}
?></br>
<?php
//echo $tbl[0];
//echo $tbl2[0];
// on libere le tableau des resultats: 
$result->free(); 
}
// on ferme la connexion a la base:
//$connexion->close();
//mysql_close();
?>
<?php
$increment = 0;
$max = sizeof($tbl);
$max2=sizeof($tbl2);

//echo $max."&".$max2;

$dataPoints = array(
      array("label"=> $tbl[$max-10] ,"y"=> $tbl2[$max-10]),
      array("label"=> $tbl[$max-9] , "y"=> $tbl2[$max-9]),
      array("label"=> $tbl[$max-8] , "y"=> $tbl2[$max-8]),
      array("label"=> $tbl[$max-7] , "y"=> $tbl2[$max-7]),
      array("label"=> $tbl[$max-6] , "y"=> $tbl2[$max-6]),
      array("label"=> $tbl[$max-5] , "y"=> $tbl2[$max-5]),
      array("label"=> $tbl[$max-4] , "y"=> $tbl2[$max-4]),
      array("label"=> $tbl[$max-3] , "y"=> $tbl2[$max-3]),
      array("label"=> $tbl[$max-2] , "y"=> $tbl2[$max-2]),
      array("label"=> $tbl[$max-1] , "y"=> $tbl2[$max-1]),
      array("label"=> $tbl[$max-0] , "y"=> $tbl2[$max-0]),
);	
?>
<!DOCTYPE HTML>
<html>
<head>  
<script>
window.onload = function () {
 
var chart = new CanvasJS.Chart("chartContainer", {
	animationEnabled: true,
	theme: "light2",
	title:{
		text: "Nombre de connexions journalières des 10 derniers jours :"
	},
	axisX:{
		// title: "Date(s)",
		crosshair: {
			enabled: true,
			snapToDataPoint: true
		}
	},
	axisY:{
		title: "Nombre de connexions",
		crosshair: {
			enabled: true,
			snapToDataPoint: true
		}
	},
	toolTip:{
		enabled: false
	},
	data: [{
		type: "area",
		dataPoints: <?php echo json_encode($dataPoints, JSON_NUMERIC_CHECK); ?>
	}]
});
chart.render();
 
}

</script>
</head>
<body>
<div id="chartContainer" style="height: 370px; width: 100%;"></div>
<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
</br>
<a href="settings.php">Retour</a>
</br>
<br><a href="graph2.php">Durée de connexions des utilisateurs</a></br>
</body>
</html>                              
<?php
include("cloud.html");
?>
