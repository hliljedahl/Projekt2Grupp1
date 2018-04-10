<?php
    // Start MySQL Connection
    include('connect.php');


?>

<html>
<head>
    <title>DATABASE OF DOOM</title>
    <style type="text/css">
        .table_titles, .table_cells_odd, .table_cells_even {
                padding-right: 20px;
                padding-left: 20px;
                color: #000;
        }
        .table_titles {
            color: #FFF;
            background-color: #666;
        }
        .table_cells_odd {
            background-color: #CCC;
        }
        .table_cells_even {
            background-color: #FAFAFA;
        }
        table {
            border: 2px solid #333;
        }
        body { font-family: "Trebuchet MS", Arial; }
    </style>
</head>

    <body>
        <h1>Team1 Database</h1>


    <table border="0" cellspacing="0" cellpadding="4">
      <tr>
          <?php
              $sql_dev = "SELECT * FROM dev01";
              $dev_q = mysqli_query($conn,$sql_dev);
              while( $dev_list = mysqli_fetch_array($dev_q) ){
                  echo '<td class="table_titles">'.$dev_list["Devices"].'</td>';
              }
              #<td class="table_titles">Date and Time</td>
              #<td class="table_titles">Temperature</td>
              #<td class="table_titles">Humidity</td>

          #

          echo '</tr>';


          #<?php

              $sql = "SELECT * FROM data01 LIMIT 100";
              //"SELECT * FROM test ORDER BY test DESC"
              // Retrieve all records and display them
              $result = mysqli_query($conn,$sql);

              // Used for row color toggle
              $oddrow = true;

              // process every record
              while( $row = mysqli_fetch_array($result) )
              {
                  if ($oddrow)
                  {
                      $css_class=' class="table_cells_odd"';
                  }
                  else
                  {
                      $css_class=' class="table_cells_even"';
                  }

                  $oddrow = !$oddrow;

                  echo '<tr>';
                  $dev_q2 = mysqli_query($conn,$sql_dev);
                  while( $dev_list = mysqli_fetch_array($dev_q2) ){
                      #echo '<td class="table_titles">'.$dev_list["Devices"].'</td>';
                      $dev_name = $dev_list["Devices"];
                      #echo $dev_name;
                      echo '   <td'.$css_class.'>'.$row[$dev_name].'</td>';
                  }
                  #echo '   <td'.$css_class.'>'.$row["time"].'</td>';
                  #echo '   <td'.$css_class.'>'.$row["temp"].'</td>';
                  #echo '   <td'.$css_class.'>'.$row["humi"].'</td>';
                  echo '</tr>';
              }
          ?>

    </table>
    </body>
</html>
