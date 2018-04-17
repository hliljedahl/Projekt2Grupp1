<?php
    // Connect to MySQL
    include("connect.php");

    $zoneRemove = $_GET["remove"];

    //Find zone ID to delete
    $sql_zone = "SELECT * FROM zone WHERE room_des = '$zoneRemove'";
    $zone = mysqli_query($conn,$sql_zone);
    $zone_id = mysqli_fetch_array($zone);
    $zone_id_var = $zone_id["id"];

    //Find sensor ID to delete
    $sql_sensors = "SELECT * FROM sensors WHERE zone_id = '$zone_id_var'";
    $sensors = mysqli_query($conn,$sql_sensors);
    $sensors_id = mysqli_fetch_array($sensors);
    $sensors_id_var = $sensors_id["id"];

    //Delete all zones with extras.
    $sql_z_del = "DELETE FROM zone WHERE id = '$zone_id_var'";
    $sql_s_del = "DELETE FROM sensors WHERE zone_id = '$zone_id_var'";
    $sql_d_del = "DELETE FROM data WHERE sensor_id = '$sensors_id_var'";

    //Add new column with the ID from Dev01
    //$sql_rem = "ALTER TABLE  data01 DROP $zoneRemove";

    //http://www.lonelycircuits.se/data/remove_zone.php?remove=XX

    // Execute SQL statement
    if(mysqli_query($conn,$sql_z_del)){

        echo "Zone: ";
        echo $zoneRemove;
        echo " removed";

        if(mysqli_query($conn,$sql_s_del)){
            echo  nl2br ("\n");
            echo "Sensor with id: ";
            echo $zone_id_var;
            echo " removed";
            mysqli_query($conn,$sql_d_del);
        }
    }
    else{
        echo "Not found Zone : ";
        echo $zoneRemove;
    }

    //Line break

    // Go to the review_data.php (optional)
    //header("Location: index.php");

?>
