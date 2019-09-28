<?php
// On démarre la session
session_start ();

/**
     * Get current user IP Address.
     * @return string
**/     
/*    function get_ip_address() {
        if ( isset( $_SERVER['HTTP_X_REAL_IP'] ) ) {
            return $_SERVER['HTTP_X_REAL_IP'];
        } elseif ( isset( $_SERVER['HTTP_X_FORWARDED_FOR'] ) ) {
            // Proxy servers can send through this header like this: X-Forwarded-For: client1, proxy1, proxy2
            // Make sure we always only send through the first IP in the list which should always be the client IP.
            return (string) self::is_ip_address( trim( current( explode( ',', $_SERVER['HTTP_X_FORWARDED_FOR'] ) ) ) );
        } elseif ( isset( $_SERVER['REMOTE_ADDR'] ) ) {
            return $_SERVER['REMOTE_ADDR'];
        }
        return '';
    }
*/
 $conn = new mysqli("localhost", "gpi2", "root", "projet");
 $sql="DELETE FROM Processus";
 $dateArr= date("Y-m-d H:i:s");
 $dateDep = $_SESSION['dateDep'];
 $ip = '192.168.56.101';//get_ip_address(); 
 $sql2="INSERT INTO nb_online(depart,arrivee,ip)VALUES('$dateArr','$dateDep','$ip')";
 if ($conn->query($sql) === TRUE) {
                  //OK
                } else {
                      echo "Error: " . $sql . "<br>" . $conn->error;
                   }
 if ($conn->query($sql2) === TRUE) {
	}else {
	echo "Error: " . $sql . "<br>" . $conn->error;
	}
//$connexion->close(); 
//mysql_close();

// On détruit les variables de notre session
session_unset ();

// On détruit notre session
session_destroy ();

// On redirige le visiteur vers la page d'accueil
header ('location: index.php');
?>
