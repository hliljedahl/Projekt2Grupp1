<?php
    // Connect to MySQL
    include("connect.php");

    $sensorRemove = $_GET["remove"];

    //Find sensor ID to delete
    $sql_sensors = "SELECT * FROM sensors WHERE name = '$sensorRemove'";
    $sensors = mysqli_query($conn,$sql_sensors);
    $sensors_id = mysqli_fetch_array($sensors);
    $sensors_id_var = $sensors_id["id"];

    //Delete all zones with extras.
    $sql_s_del = "DELETE FROM sensors WHERE id = '$sensors_id_var'";
    $sql_d_del = "DELETE FROM data WHERE sensor_id = '$sensors_id_var'";

    //Add new column with the ID from Dev01
    //$sql_rem = "ALTER TABLE  data01 DROP $zoneRemove";

    //http://www.lonelycircuits.se/data/remove_sensors.php?remove=XX

    // Execute SQL statement
    if(mysqli_query($conn,$sql_s_del)){

        echo "Sensor: ";
        echo $sensorRemove;
        echo " removed";
        mysqli_query($conn,$sql_d_del);

    }
    else{
        echo "Not found Zone : ";
        echo $sensorRemove;
    }

    //Line break

    // Go to the review_data.php (optional)
    //header("Location: index.php");

?>
