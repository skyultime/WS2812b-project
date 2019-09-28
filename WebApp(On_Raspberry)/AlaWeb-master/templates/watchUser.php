<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8" />
		<title>Watch</title>
	</head>
	<body>
		<?php
			$connect = new mysqli("192.168.56.101", "gpi2","network", "projet");
			$connect->set_charset("utf8");
			if ($connect->connect_errno) {
				printf("Echec de la connexion : %s %s", $connect->connect_errno, $connect->connect_error);
				exit();
			}			
				$sql="INSERT INTO Processus(login,ip,fonction) VALUES ('invite','0.0.0.0',0)";				
				$connect->close;
			include("alaLed.php");
		?>
	</body>
</html>
	
