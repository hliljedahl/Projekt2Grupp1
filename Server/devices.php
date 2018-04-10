<?php
    // Connect to MySQL
    include("connect.php");


    $sql_count2 = "SELECT * FROM dev01";
    $sql_num2 = mysqli_query($conn, $sql_count2);
    $numrows2 = mysqli_num_rows($sql_num2);



?>
