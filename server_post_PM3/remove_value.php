<?php

//******************************************************************************
//http://www.lonelycircuits.se/data/remove_value.php?max=XX
//******************************************************************************
//      OR
//******************************************************************************
//http://www.lonelycircuits.se/data/remove_value.php?remove=XX
//******************************************************************************

    // Connect to MySQL
    include("connect.php");



    //MAX NUMBER OF ROWS
    if($_GET["max"]){
        $max = $_GET["max"];
    }
    else{
        $max = 10;
    }

    // Prepare the SQL statement
    //Count thee number of rows
    $sql_count = "SELECT * FROM data";
    $sql_res = mysqli_query($conn, $sql_count);
    $numrows = mysqli_num_rows($sql_res);
    $sql_remove = $numrows - $max;

    if($_GET["remove"]){
        $sql_remove = $_GET["remove"];
    }

    //System Print
    echo nl2br ("\n" . $numrows. "\n");
    echo nl2br ("\n" . $sql_remove. "\n");


    //If the number of rows is more then..
    if($sql_remove > 0){

        //Prepare the SQL statement
        //$sql_top = "SELECT TOP $sql_remove * FROM data01";
        $sql = "DELETE FROM data LIMIT $sql_remove";

        //Delete unwanted rows
        if (mysqli_query($conn, $sql)) {

            echo "Record deleted successfully";
        }
        else {

            echo "Error deleting record: " . mysqli_error($conn);

        }
    }else {

        echo nl2br ("\n Nothing to delete \n");

    }


?>
