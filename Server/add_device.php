<?php
    // Connect to MySQL
    include("connect.php");
    include("devices.php");

    $columnName = $_GET["dev"];
    echo "Added: ";
    echo $columnName;

    //Add new device ID in Dev01
    $sql_in = "INSERT INTO dev01 (Devices) VALUES ('$columnName')";
    //Add new column with the ID from Dev01
    $sql_new = "ALTER TABLE  data01 ADD $columnName double NOT NULL";

    //http://www.lonelycircuits.se/data/add_device.php?dev=XX

    // Execute SQL statement
    mysqli_query($conn,$sql_in);

    mysqli_query($conn,$sql_new);

    // Go to the review_data.php (optional)
    //header("Location: index.php");

?>
