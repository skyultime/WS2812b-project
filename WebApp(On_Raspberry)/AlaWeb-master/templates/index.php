<head>
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
<title>WS2812b web ctrl</title>
<META NAME="description" content="New projects : WS2812b web controller with raspberry pi 3b+ and stm32/arduino nano microcontrollers ! Site cloud d'ingénierie Hardware,Software... Ici vous pouvez retrouver de nombreuses méthodes en électronique de commutation, programmation orientée objets..." />
<meta name="keywords" content="Cloud,cloud,stm32, Altium, Lt Spice, Matlab,électron,expérience,propulsion,actionneur,stratégie, Solidworks, Barre de led réactive, capteurs, électronique de commutation, VHDL, FPGA, Software,Hardware,Systèmes embarqués" />
<meta name="robots" content="INDEX,NOFOLLOW" />
<meta name="viewport" content="width=device-width, initial-scale=1.0">

</head>


	<?php include("fullscreen_bar.html"); ?>
<?php include("cloud.html"); ?>
<html>


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
<link rel="icon" type="image/png" href="logo.png" />

<body>
<?php

//$conn = new mysqli("192.168.56.101", "gpi2", "network", "projet");
// $sql="DELETE FROM Processus";
// if ($conn->query($sql) === TRUE) {
                  //OK
//                } else {
//                      echo "Error: " . $sql . "<br>" . $conn->error;
//                   }

 //mysql_close();
$connexion = new mysqli("localhost", "gpi2", "root","projet"); 
if ($connexion->connect_errno) { 
	printf("´Echec de la connexion : %s %s");
exit();
}

$connexion->set_charset("utf8");
$maRequete2 = "SELECT fonction FROM Processus";
$result2 = $connexion->query($maRequete2);
if(!$result2) {
} else {
$resultat2 = $result2->fetch_assoc(); // ... 
$inviteEstConnecte=0;
$adminEstConnecte=0;
while($resultat2){ 
if ($resultat2["fonction"]==0){
	$inviteEstConnecte+=1;
        //echo "invite";
} else if ($resultat2["fonction"]==1){
	$adminEstConnecte+=1;
	//echo "admin";
}
$resultat2 = $result2->fetch_assoc();
	}
	$result2->free();
}
$connexion->close();
//mysql_close();
//echo $inviteEstConnecte."&".$adminEstConnecte;

?>

<div id="container">
            <!-- zone de connexion -->

<form action="login.php" method="POST">
 <h1>Connection</h1>
Login : <input type="text" placeholder = "Type your login"  name = "login" required>
<br />
Password : <input type="password" placeholder = "Type your password"  name = "pwd" required>
<input type="submit" id="submit" value="LOGIN" />


<?php
if ($adminEstConnecte>=1){

	echo"connexion :".$adminEstConnecte." (administrateur)<br/>";
	echo '<body onLoad="alert(\'Un administrateur est connecté, vous risquez de ne pas pouvoir vous connecter...\')">';
}
if ($inviteEstConnecte>=1){
       echo"connexion :".$inviteEstConnecte." (session invitée)</br>";
       echo '<body onLoad="alert(\'Une session invitée est connectée, vous risquez de ne pas pouvoir vous connecter...\')">';
}
?> 


<html>
<head>
<style>
.button {
  display: inline-block;
  border-radius: 4px;
  background-color:#33CDFF;
  border: none;
  color: #FFFFFF;
  text-align: center;
  font-size: 15px;
  padding: 15px;
  width: 150px;
  transition: all 0.5s;
  cursor: pointer;
  margin: 5px;
}

.button span {
  cursor: pointer;
  display: inline-block;
  position: relative;
  transition: 0.5s;
}

.button span:after {
  content: '\00bb';
  position: absolute;
  opacity: 0;
  top: 0;
  right: -20px;
  transition: 0.5s;
}

.button:hover span {
  padding-right: 25px;
}

.button:hover span:after {
  opacity: 1;
  right: 0;
}
</style>
</head>
<body>

</body>
</html>

</form>
<button class="button" style="vertical-align:middle" onclick="myFunction()"><span>1ère connexion ?</span></button>
<p id="demo"></p>

<script>
function myFunction() {
  var person = prompt("Entrez votre e-mail s'il vous plaît ?", "");
  if (person == null || person == ""|| !(person.indexOf('@')>-1)) {
	//Nothing réessayez
        alert("Adresse e-mail erronée!");
  } else {
	 alert("Requête bien prise en compte !");

	    //send e-mail   	
	//$destinataire = person;
	$expediteur = 'alexy.debus@hotmail.fr'; 
	$objet = 'Connexion WS2812b Controller Website'; 
	/*$headers  = 'MIME-Version: 1.0' . "\n"; // Version MIME
	/*$headers .= 'Content-type: text/html; charset=ISO-8859-1'."\n"; // l'en-tete Content-type pour le format HTML
	$headers .= 'Reply-To: '.$expediteur."\n"; // Mail de reponse
	$headers .= 'From: "Nom_de_expediteur"<'."Alexy DEBUS".'>'."\n"; // Expediteur
	$headers .= 'Delivered-to: '.person."\n"; // Destinataire     
        $message = '<div style="width: 100%; text-align: center; font-weight: bold"> Bonjour'.$_POST['name'].'! \n'.$_POST['message'].'</div>';
      */ 
       if (mail(person, $objet, $message,'')){
    	       alert("e_mail envoyée");
       }else{
    	       alert("Votre message n'a pas pu être envoyé");
       }
}
}
</script>

</body>
</html>

