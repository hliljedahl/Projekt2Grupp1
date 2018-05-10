

<?php
//******************************************************************************
//http://www.lonelycircuits.se/data/remove_sensors_name.php?name=XX
//******************************************************************************

    // Connect to MySQL
    include("connect.php");

    $sensorRemove = $_GET["name"];

    //Find sensor ID to delete
    $sql_sensors = "SELECT * FROM sensors WHERE name = '$sensorRemove'";
    //$sql_s_del = "DELETE FROM sensors WHERE id = '$sensors_id_var'";
    //$sensors_del = mysqli_query($conn,$sql_s_del);
    $sensors = mysqli_query($conn,$sql_sensors);
    /*$sensors_id = mysqli_fetch_array($sensors);
    $sensors_id_var0 = $sensors_id["id"];
    $sensors_id_var1 = $sensors_id[1];
    */
    //echo $sensors;

    while ($sensors_id = mysqli_fetch_array($sensors)) {
        //echo $sensors_id['id'];
        $sensors_id_var = $sensors_id["id"];
        $sql_s_del = "DELETE FROM sensors WHERE id = '$sensors_id_var'";
        $sql_d_del = "DELETE FROM data WHERE sensor_id = '$sensors_id_var'";


        if(mysqli_query($conn,$sql_s_del)){

            echo "Sensor: ";
            echo $sensorRemove;
            echo " removed";
            echo nl2br ("\n");
            if(mysqli_query($conn,$sql_d_del)){
                echo "and its values..."
            }else{
                echo "but didn't find any values..."
            }
            echo nl2br ("\n");

        }
        else{
            echo "Not found Sensor : ";
            echo $sensorRemove;
            echo nl2br ("\n");
        }

    }

    //echo $sensors_id_var1;
    //echo $sensors_id_var1;

    //Delete all zones with extras.
    /*
    $sql_s_del = "DELETE FROM sensors WHERE id = '$sensors_id_var'";
    $sql_d_del = "DELETE FROM data WHERE sensor_id = '$sensors_id_var'";

    //Add new column with the ID from Dev01
    //$sql_rem = "ALTER TABLE  data01 DROP $zoneRemove";

    //http://www.lonelycircuits.se/data/remove_sensors_name.php?name=XX

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
*/
    //Line break

    // Go to the review_data.php (optional)
    //header("Location: index.php");

?>
