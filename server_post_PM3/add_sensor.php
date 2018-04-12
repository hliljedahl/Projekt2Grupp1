<?php
    // Connect to MySQL
    include("connect.php");

    $sensor_name = $_GET["name"];
    $zone_name = $_GET["zone"];
    $type_name = $_GET["type"];

    //echo $sensor_name;
    //echo $zone_name;
    //echo $type_name;



    $sql_zone = "SELECT * FROM zone WHERE room_des = '$zone_name'";
    $zone = mysqli_query($conn,$sql_zone);
    $zone_id = mysqli_fetch_array($zone);
    //echo $zone_id["id"];

    $zone_id_var = $zone_id["id"];

    $sql_sensor = "INSERT INTO sensors (name, zone_id, type) VALUES ($sensor_name, $zone_id_var, $type_name)";

    if(mysqli_query($conn,$sql_sensor)){

        echo "Added: ";
        echo $sensor_name;
        echo " to: ";
        echo $zone_name;

    }
    else{

        echo "Error";

    }

    //http://www.lonelycircuits.se/data/add_zone.php?zone="XX"

?>
