<head> <title>Inscription Competiteur</title> </head>

<body> 
<?php

session_start();


$num = $_SESSION['numeroUtilisateur'];
$refConcours = $_SESSION['numConcours'];
echo "bonjour".$refConcours;

$conn = new mysqli("192.168.56.101", "gpi2", "network", "projet");

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

if (isset ($_SESSION['numeroUtilisateur']) AND $num > 1) {

$sql = "INSERT INTO Participe(refUtilisateur,refConcours) VALUES ('$num','$refConcours')";


if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

// on ferme la connexion à la base
mysql_close();

?>
<h2><a href = "menuConcours.php">Retour en arrière</a>
	
<?php
}
else if (isset ($_SESSION['numeroUtilisateur']) AND $num = 1){
         echo '<body onLoad="alert(\'Accès non autorisé...\')">';
?>

<h2><a href = "site.php">Retourner à l'accueil</a>

<?php

}
include("cloud.html");
?>
</body>
