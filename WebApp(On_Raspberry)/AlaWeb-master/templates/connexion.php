<?php session_start(); $titre="Connexion"; include("includes/identifiants.php"); 
include("includes/debut.php"); include("includes/menu.php"); echo '<p><i>Vous êtes ici</i> : <a 
href="./index.php">Index du forum</a> --> Connexion'; ?> <?php //echo '<h1>Connexion</h1>'; //if ($id!=0) 
erreur(ERR_IS_CO);
?>

<?php if (!isset($_POST['pseudo'])) //On est dans la page de formulaire {
    echo '<form method="post" action="connexion.php">
    <fieldset>
    <legend>Connexion</legend>
    <p>
    <label for="pseudo">Pseudo :</label><input name="pseudo" type="text" id="pseudo" /><br />
    <label for="password">Mot de Passe :</label><input type="password" name="password" id="password" />
    </p>
    </fieldset>
    <p><input type="submit" value="Connexion" /></p></form>
    <a href="./register.php">Pas encore inscrit ?</a>
     
    </div>
    </body>
    </html>';
}
?> <?php
else
