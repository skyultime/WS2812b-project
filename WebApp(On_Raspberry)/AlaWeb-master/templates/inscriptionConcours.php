<?php include("cloud.html"); ?>
<html>
<head>
<style type="text/css"> 
body{
    background: #01FCD7;
}
#container{
    width:400px;
    margin:0 auto;
    margin-top:10%;
}
/* Bordered form */
form {
    width:100%;
    padding: 30px;
    border: 1px solid #f1f1f1;
    background: #fff;
    box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);
}
#container h1{
    width: 38%;
    margin: 0 auto;
    padding-bottom: 10px;
}

/* Full-width inputs */
input[type=text], input[type=password] {
    width: 100%;
    padding: 12px 20px;
    margin: 8px 0;
    display: inline-block;
    border: 1px solid #ccc;
    box-sizing: border-box;
}

/* Set a style for all buttons */
input[type=submit] {
    background-color: #01AFFF;
    color: white;
    padding: 14px 20px;
    margin: 8px 0;
    border: none;
    cursor: pointer;
    width: 100%;
}
input[type=submit]:hover {
    background-color: white;
    color: blue;
    border: 1px solid #50FCE7;
}
</style>

</head>

<body>



<?php

session_start();

        $connexion = new mysqli("192.168.56.101", "gpi2", "network", "projet");
        $connexion->set_charset("utf8");
        $maRequete  = "SELECT * FROM Utilisateur WHERE numUtilisateur > 0 ";

        $result = $connexion->query($maRequete);
        $listeUtilisateur = $result->fetch_assoc();
?>
<div id="container">
            <!-- zone d'inscription -->

<form action="retourCreationConcours.php" method="POST">
 <h1>Inscription</h1>
Description : <input type="text" placeholder = "Entrer votre description "  maxlength="500" name = "description" required>
<br />
Date de début du concours : <input type="date" placeholder = "Entrer la date de début du concours "  maxlength="15" name = "dateDebut" required>
<br />

Date de fin du concours : <input type="date" placeholder = "Entrer la date de fin du concours "  maxlength="15" name = "dateFin" required>
<br />
 
Choisir votre président :<select name="president">
        <?php  while($listeUtilisateur){
         
 ?> <option value = "<?php echo $listeUtilisateur['numUtilisateur']; ?>" ><?php echo $listeUtilisateur['nom']." ".$listeUtilisateur['prenom'];?></option>$
<?php 
 $listeUtilisateur = $result->fetch_assoc();
}
?>
</select>
<?php
// on libere le tableau des resultats:
        $result->free();
// on ferme la connexion a la base:
$connexion->close();
?>
<br />

<input type="submit" id="submit" value="Créer le concours" />
<a href="listeConcours.php"> Concours déja enregistré?</a>
<a href="menuAdministrateur.php"> Annuler ?</a>

<?php
              if(isset($_GET['erreur'])){
                    $err = $_GET['erreur'];
                    if($err==1 || $err==2)
                        echo "<p style='color:red'>Utilisateur ou mot de passe incorrect</p>";
                }
            	 ?>

</form>

</body>
</html>


	
