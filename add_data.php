<?php
    // Connect to MySQL
    include("connect.php");

    // Prepare the SQL statement
      date_default_timezone_set('Europe/Stockholm');
     $dateS = date('d/m/Y h:i:s', time());
    echo $dateS;
//    $SQL = "INSERT INTO yourdatabasename.data (time,temp,humi,test) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["test"]."')";
    //$sql_in = "INSERT INTO test (time,temp,humi,id) VALUES ('$dateS','33.2','13.3','4')";
    $sql_in = "INSERT INTO data01 (time,temp,humi,id) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["id"]."')";



    //http://www.lonelycircuits.se/add_data.php?temp="+temp+"&humi="+humi+"&id="+id


    // Execute SQL statement
    mysqli_query($conn,$sql_in);

    // Go to the review_data.php (optional)
    //header("Location: index.php");
?>
