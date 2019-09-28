<head>
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
</head>

<?php
// ------------------------------------------------------------------------- //
// Compteur de connectés //
// ------------------------------------------------------------------------- //
// Auteur: Merckel Loïc //
// Web: http://www.merckel.org/spip //
// ------------------------------------------------------------------------- //

/*
Ce script permet de connaître le nombre de visiteurs connectés sur une période
de temps donnée (i.e. permet de savoir combien il y a de visiteurs en ligne).
Ce script n'utilise pas de base de données. Il stocke les informations dans un
fichier .dat */

// $time est le temps en seconde à partir duquel on considère que
// le visiteur n'est plus connecté

// $text_color est la couleur d'affichage du compteur

// $filename est le nom du fichier créé pour stocker les informations

function nb_visiteurs_connecte($time=600,$text_color="red",$filename="data.dat")
{
$ip = getenv("REMOTE_ADDR");
$date=time();

$i=0;
$ii=0;
$bool=0;

if(file_exists($filename))
{
if($fichier=fopen($filename,"r"))
{
while(!feof($fichier))
{
$ligne=fgets($fichier,4096);
$tab=explode("|",$ligne);

if($tab[1]>0)
{
$tab_de_tab[$i][0]=$tab[0];
$tab_de_tab[$i][1]=$tab[1];

$i++;
}
}
fclose($fichier);
}
}

for($j=0;$j<$i;$j++)
{
if(($date-chop($tab_de_tab[$j][1]))>$time)
{
//on ne fait rien
}
else
{
$tab_de_tab_actualise[$ii][0]=$tab_de_tab[$j][0];
$tab_de_tab_actualise[$ii][1]=chop($tab_de_tab[$j][1]);
$ii++;
}
}

for($j=0;$j<$ii;$j++)
{
if($tab_de_tab_actualise[$j][0]==$ip)
{
$bool=1;
}
}

if($bool==0)
{
$tab_de_tab_actualise[$ii][0]=$ip;
$tab_de_tab_actualise[$ii][1]=$date;
$ii++;
}

if($fichier=fopen($filename,"w"))
{
for($j=0;$j<$ii;$j++)
{
fputs($fichier,chop($tab_de_tab_actualise[$j][0]));
fputs($fichier,"|");
fputs($fichier,chop($tab_de_tab_actualise[$j][1]));
fputs($fichier,"\n");
}

fclose($fichier);
}

echo "<font color=\"",$text_color,"\"><b>",$ii,"</b>

<a>personne connectée actuellement sur ce site";

}
nb_visiteurs_connecte(600,"blue");
?>
</br>
