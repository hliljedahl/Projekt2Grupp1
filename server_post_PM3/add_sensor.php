<?php

//******************************************************************************
//http://www.lonelycircuits.se/data/add_sensor.php?zone=XXX&name="YYY"&type="ZZZ"&ip=XYZ
//******************************************************************************

    // Connect to MySQL
    include("connect.php");

    $sensor_name = $_GET["name"];
    $zone_name = $_GET["zone"];
    $type_name = $_GET["type"];
    //$type_name = $_GET["type"];
    $ipadress  = $_GET["ip"];

    //echo $zone_name;


    //echo $sensor_name;
    //echo $zone_name;
    //echo $type_name;



    $sql_zone = "SELECT * FROM zone WHERE room_des = '$zone_name'";
    $zone = mysqli_query($conn,$sql_zone);
    $zone_id = mysqli_fetch_array($zone);
    //$ipadress = "192.168.1.184";
    //echo $zone_id["id"];
    //echo $zone_id;
    //echo "      ";
    $zone_id_var = $zone_id["id"];
    //echo $zone_id_var;
    //echo "      ";
    $sql_sensor = "INSERT INTO sensors (name, zone_id, type, ipadress) VALUES ($sensor_name, $zone_id_var, $type_name, '$ipadress')";

    //echo $sql_sensor;
    //echo "      ";

    if(mysqli_query($conn,$sql_sensor)){

        echo "Added: ";
        echo $sensor_name;
        echo " to: ";
        echo $zone_name;

    }
    else{

        echo "Error";

    }

    //http://www.lonelycircuits.se/data/add_sensor.php?zone=XXX&name="YYY"&type="ZZZ"&ip=XYZ

?>
