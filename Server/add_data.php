<?php
    // Connect to MySQL
    include("connect.php");

    // Prepare the SQL statement
    date_default_timezone_set('Europe/Stockholm');
    $dateS = date('Y/m/d h:i:s', time());
    echo $dateS;

    //$SQL = "INSERT INTO yourdatabasename.data (time,temp,humi,test) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["test"]."')";
    //$sql_in = "INSERT INTO test (time,temp,humi,id) VALUES ('$dateS','33.2','13.3','4')";
    $sql_in = "INSERT INTO data01 (time,temp,humi) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."')";



    //http://www.lonelycircuits.se/add_data.php?temp=XX&humi=XX&id=XX


    // Execute SQL statement
    mysqli_query($conn,$sql_in);

    // Go to the review_data.php (optional)
    //header("Location: index.php");
?>
