<?php

//******************************************************************************
//http://www.lonelycircuits.se/data/add_zone.php?zone="XX"
//******************************************************************************

    // Connect to MySQL
    include("connect.php");

    $zone_name = $_GET["zone"];

    $sql_zone = "INSERT INTO zone (room_des) VALUES ($zone_name)";

    if(mysqli_query($conn,$sql_zone)){

        echo "Added: ";
        echo $zone_name;

    }
    else{

        echo "Error";

    }

    //http://www.lonelycircuits.se/data/add_zone.php?zone="XX"

?>
