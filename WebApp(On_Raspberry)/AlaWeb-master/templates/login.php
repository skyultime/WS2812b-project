<!DOCTYPE html>

<head>
<title>Formulaire d'identification</title>
</head>

<body>

<?php

$login = $_POST['login'];
$pwd = $_POST['pwd'];
 
// On définit un login et un mot de passe de base pour tester notre exemple. Cependant, vous pouvez très bien interroger votre base de données afin de savoir si le visiteur qui se connecte est bien membre de votre site

// on teste si nos variables sont définies
if (isset($_POST['login']) && isset($_POST['pwd'])) {	

$connexion = new mysqli("localhost", "gpi2", "root","projet");

if ($connexion->connect_errno) {
printf("´Echec de la connexion : %s %s",
$connexion->connect_errno, $connexion->connect_error);
exit();
}



// on s´electionne le jeu de caract`eres
$connexion->set_charset("utf8");
// requete `a la base de donn´ees :
$maRequete  = "SELECT login, motDePasse,numUtilisateur FROM Utilisateur WHERE login = '$login' AND motDePasse = '$pwd'";
$maRequete2 = "SELECT fonction FROM Processus";
$result = $connexion->query($maRequete);
$result2 = $connexion->query($maRequete2);

if(!$result) {
//echo "la requete ne s’est pas executee";
} else {
//echo "la requete s’est bien passee";
// on va chercher les resultats:
$resultat = $result->fetch_assoc(); // ...
$numeroUtilisateur = $resultat["numUtilisateur"];

// on libere le tableau des resultats:
$result->free();
}

if(!$result2) {
//echo "la requete ne s’est pas executee";
} else {
//echo "la requete s’est bien passee";
// on va chercher les resultats:
$resultat2 = $result2->fetch_assoc(); // ...

while($resultat2){
	//echo "connexion ?".$resultat2["fonction"];
	if ($resultat2["fonction"]==0){
	$inviteEstConnecte=1;
	//echo "invite connecte";
	} 	
	else if ($resultat2["fonction"]==1){
	$adminEstConnecte=1;
	//echo "admin connecte";
	//}else {
	//$inviteEstConnecte=0;
	//$adminEstConnecte=0;
	}
	$resultat2 = $result2->fetch_assoc();
}
//$fonction = $resultat2["fonction"];
//echo "admin connecte=".$adminEstConnecte;
//echo "invite connecte=". $inviteEstConnecte;

// on libere le tableau des resultats:
$result2->free();
}

// on ferme la connexion a la base:
//$connexion->close();
//mysql_close();
// on vérifie les informations du formulaire, à savoir si le pseudo saisi est bien un pseudo autorisé, de même pour le mot de passe
	if (isset($numeroUtilisateur) ) {
		 $dateDep = date("Y-m-d H:i:s");
		// dans ce cas, tout est ok, on peut démarrer notre session
	
		// on la démarre :)
		session_start ();
		// on enregistre les paramètres de notre visiteur comme variables de session ($login et $pwd) (notez bien que l'on utilise pas le $ pour enregistrer ces variables)
		$_SESSION['dateDep']= $dateDep;

		if ($numeroUtilisateur == 1) {
			$_SESSION['login'] = $_POST['login'];
			$_SESSION['pwd'] = $_POST['pwd'];
			$_SESSION['numeroUtilisateur'] = $numeroUtilisateur;
		$conn = new mysqli("localhost", "gpi2", "root","projet");
		$sql="INSERT INTO Processus(login,ip,fonction) VALUES('admin','0.0.0.0',1)";
		//$sql2="INSERT INTO nb_online(depart)VALUES($dateDep)";
		if ($conn->query($sql) === TRUE) {
                  //OK
                } else {
                      echo "Error: " . $sql . "<br>" . $conn->error;
                   }
		
		

		//header("watchAdmin.php");
		// on redirige notre visiteur vers une page de notre section membre
		header ('location:alaLed.php');
		}else if (($numeroUtilisateur > 1)&&($adminEstConnecte<1)&&($inviteEstConnecte<1)) {
			
                        $_SESSION['login'] = $_POST['login'];
                        $_SESSION['pwd'] = $_POST['pwd'];
			$_SESSION['numeroUtilisateur'] = $numeroUtilisateur;
		$conn = new mysqli("localhost", "gpi2", "root","projet");
		$sql2 = "INSERT INTO Processus(login,ip,fonction) VALUES('invite','0.0.0.0',0)";

 if ($conn->query($sql2) === TRUE) {
 } else {
echo "Error: " . $sql2 . "<br>" . $conn->error;
}

		 header ('location:alaLed.php');
		 }else if (($numeroUtilisateur > 1)&&($adminEstConnecte>=1)||($inviteEstConnecte>=1)) {
		 	//echo "Probleme !";
			echo '<body onLoad="alert(\'Veuillez patentier...Une personne est déja connectée !\')">';
                // on redirige notre visiteur vers une page de notre section membre
                //echo "statut actuel ".$fonction;
		 echo '<meta http-equiv="refresh" content="0;URL=index.php">';
		
} 
	}else {
		// Le visiteur n'a pas été reconnu comme étant membre de notre site. On utilise alors un petit javascript lui signalant ce fait
		echo '<body onLoad="alert(\'Membre non reconnu...\')">';
		// puis on le redirige vers la page d'accueil
		echo '<meta http-equiv="refresh" content="0;URL=index.php">';
	}

}

else {
	echo 'Les variables du formulaire ne sont pas déclarées.';
}

?>
 <?php include("cloud.html");?> </body> </html> 
