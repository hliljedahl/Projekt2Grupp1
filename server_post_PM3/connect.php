<?php
//$servername = "localhost";
$servername = "lonelycircuits.se.mysql";
$username = "lonelycircuits_se";
$password = "grupp1";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $username);

// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
//echo "Connected successfully \n";
?>
