<?php
    // Connect to MySQL
    include("connect.php");

    // Prepare the SQL statement
    date_default_timezone_set('Europe/Stockholm');
    $dateS = date('Y/m/d h:i:s', time());
    echo $dateS;

    //$SQL = "INSERT INTO yourdatabasename.data (time,temp,humi,test) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["test"]."')";
    //$sql_in = "INSERT INTO test (time,temp,humi,id) VALUES ('$dateS','33.2','13.3','4')";
    $sql_dev = "SELECT * FROM dev01";
    $dev_q = mysqli_query($conn,$sql_dev);

    $sql_date = "INSERT INTO data01 (time) VALUES ('$dateS')";

    mysqli_query($conn,$sql_date);

    while( $dev_list = mysqli_fetch_array($dev_q) ){

        $devCOL = $dev_list["Devices"];

        if($devCOL != time){
            $devGET = $_GET["$devCOL"];
            echo $devCOL;
            echo "#";
            echo $devGET;
            echo "#";
            $sql_insert = "UPDATE data01 SET $devCOL = $devGET WHERE time = '$dateS'";
            #echo $sql_insert;
            #$sql_insert = "INSERT INTO data01 ($devdev) VALUES (".$_GET["$devdev"].")";
            mysqli_query($conn,$sql_insert);
        }
        //echo '<td class="table_titles">'.$dev_list["Devices"].'</td>';
    }
    echo $sql_insert;

    //$sql_in = "INSERT INTO data01 (time,temp,humi) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."')";



    //http://www.lonelycircuits.se/add_data.php?temp=XX&humi=XX&id=XX


    // Execute SQL statement
    //mysqli_query($conn,$sql_date);

    // Go to the review_data.php (optional)
    //header("Location: index.php");
?>
