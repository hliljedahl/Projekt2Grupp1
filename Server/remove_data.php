<?php
    // Connect to MySQL
    include("connect.php");

    // Prepare the SQL statement
    //Count thee number of rows
    $sql_count = "SELECT * FROM data01";
    $sql_res = mysqli_query($conn, $sql_count);
    $numrows = mysqli_num_rows($sql_res);
    $sql_remove = $numrows - 10;
    echo nl2br ("\n" . $numrows);
    echo nl2br ("\n" . $sql_remove);


    //If the number of rows is more then..
    if($sql_remove > 0){

        //Prepare the SQL statement
        //$sql_top = "SELECT TOP $sql_remove * FROM data01";
        $sql = "DELETE FROM data01 LIMIT $sql_remove";

        //Delete unwanted rows
        if (mysqli_query($conn, $sql)) {

            echo "Record deleted successfully \n";
        }
        else {

            echo "Error deleting record: " . mysqli_error($conn);

        }
    }else {

        echo nl2br ("\n Nothing to delete \n");

    }

    //http://www.lonelycircuits.se/data/add_data.php?temp=XX&humi=XX&id=XX
    //http://www.lonelycircuits.se/data/add_data.php?temp=24&humi=12&id=8

?>
