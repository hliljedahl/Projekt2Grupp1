<?php
    // Connect to MySQL
    include("connect.php");
    include("devices.php");

    //$SQL = "INSERT INTO yourdatabasename.data (time,temp,humi,test) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["test"]."')";
    //$sql_in = "INSERT INTO test (time,temp,humi,id) VALUES ('$dateS','33.2','13.3','4')";


    $columnName = ".$_GET["dev"]."
    $sql_in = "INSERT INTO dev01 (devices) VALUES ('".$_GET["dev"]."')";


    $sql_new = "ALTER TABLE  `data01` ADD  `$columnName` double NOT NULL";

    //http://www.lonelycircuits.se/add_data.php?temp=XX&humi=XX&id=XX


    // Execute SQL statement
    mysqli_query($conn,$sql_in);

    mysqli_query($conn,$sql_new);

    // Go to the review_data.php (optional)
    //header("Location: index.php");

?>
