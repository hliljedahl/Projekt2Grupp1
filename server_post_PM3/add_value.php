<?php
    // Connect to MySQL
    include("connect.php");

    $sensor_name = $_GET["name"];
    $value = $_GET["value"];

    //echo $sensor_name;
    //echo $zone_name;
    //echo $type_name;

    // Prepare the SQL statement
    date_default_timezone_set('Europe/Stockholm');
    $dateS = date('Y-m-d h:i:s', time());


    $sql_sensor = "SELECT * FROM sensors WHERE name = '$sensor_name'";
    $sensor = mysqli_query($conn,$sql_sensor);
    $sensor_id = mysqli_fetch_array($sensor);
    //echo $zone_id["id"];

    $sensor_id_var = $sensor_id["id"];

    //$sql = "INSERT INTO `value`(`sensor_id`, `value`) VALUES (3,21)";

    //$sql_value = "INSERT INTO data (sensor_id, timestmp,  value) VALUES ($sensor_id_var, '$dateS', $value)";
    $sql_value = "INSERT INTO data (sensor_id, timestmp, value) VALUES ($sensor_id_var, '$dateS', $value)";

    echo $sql_value;

    //mysqli_query($conn,$sql_value)

    if(mysqli_query($conn,$sql_value)){

        echo "Added: ";
        echo $value;
        echo " to: ";
        echo $sensor_name;
        echo "(id=";
        echo $sensor_id_var;
        echo ")  ** at: ";
        echo $dateS;


    }
    else{

        //echo "Error";
        echo("Error description: " . mysqli_error($conn));


    }

    //http://www.lonelycircuits.se/data/add_zone.php?zone="XX"

?>
