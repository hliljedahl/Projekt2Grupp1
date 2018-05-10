<?php

//******************************************************************************
//http://www.lonelycircuits.se/data/add_inst.php?max="XX"
//    OR
//http://www.lonelycircuits.se/data/add_inst.php?update="XX"
//******************************************************************************

    // Connect to MySQL
    include("connect.php");

    $inst_max = $_GET["max"];
    $inst_update = $_GET["update"];

    if($inst_max){
        $sql_insert = "UPDATE inst SET max = $inst_max WHERE id = 1";
    }
    if($inst_update){
        $sql_insert = "UPDATE inst SET updte = $inst_update WHERE id = 1";
    }

    if(mysqli_query($conn,$sql_insert)){

        echo "Changed: ";
        echo $inst;

    }
    else{

        echo "Error";

    }

    //http://www.lonelycircuits.se/data/add_inst.php?max="XX"

?>
