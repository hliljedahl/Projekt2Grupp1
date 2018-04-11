<?php
    // Connect to MySQL
    include("connect.php");
    include("devices.php");

    $columnRemove = $_GET["remove"];


    //Add new device ID in Dev01
    $sql_out = "DELETE FROM dev01 WHERE Devices = '$columnRemove'";
    //Add new column with the ID from Dev01
    $sql_rem = "ALTER TABLE  data01 DROP $columnRemove";

    //http://www.lonelycircuits.se/data/remove_device.php?remove=XX

    // Execute SQL statement
    if(mysqli_query($conn,$sql_out)){
        echo "Removed from dev01: ";
        echo $columnRemove;
    }
    else{
        echo "Not removed in dev01";
    }

    //Line break
    echo  nl2br ("\n");

    // Execute SQL statement
    if(mysqli_query($conn,$sql_rem)){
        echo "Removed from data01: ";
        echo $columnRemove;
    }
    else{
        echo "Not removed in data01";
    }

    // Go to the review_data.php (optional)
    //header("Location: index.php");

?>
