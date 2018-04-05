<?php
    // Connect to MySQL
    include("connect.php");

    // Prepare the SQL statement

//dfgdfgfdg

    $sql = "DELETE FROM data01 WHERE id=69";

    //$SQL = "INSERT INTO yourdatabasename.data (time,temp,humi,test) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["test"]."')";
    //$sql_in = "INSERT INTO test (time,temp,humi,id) VALUES ('$dateS','33.2','13.3','4')";
    //$sql_in = "INSERT INTO data01 (time,temp,humi,id) VALUES ('$dateS','".$_GET["temp"]."','".$_GET["humi"]."','".$_GET["id"]."')";

    if (mysqli_query($conn, $sql)) {

        echo "Record deleted successfully";
    }
    else {

        echo "Error deleting record: " . mysqli_error($conn);

    }


    //http://www.lonelycircuits.se/add_data.php?temp=XX&humi=XX&id=XX


    // Execute SQL statement
    mysqli_query($conn,$sql_in);

    // Go to the review_data.php (optional)
    //header("Location: index.php");
?>
