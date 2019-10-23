<!DOCTYPE html>
<html>
<head>
<title>GIESSBERT</title>

<link href='https://fonts.googleapis.com/css?family=Orbitron:400,700' rel='stylesheet'>
<link rel='stylesheet' type='text/css' href='lib/style/style.css'>
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js'></script>

</head>
<body>

<h1>GIEßBERT</h1>
<p>live data</p>
<p>&nbsp;</p>

<script>

   function write(data) {
     document.write("<div class='col'><a href=''>TEMP<br>" + data.values[0].temp + "<br><p></a><div class='col'><a href=''>HUMIDITY<br>" + data.values[0].humidity + "<br><p></a></div><div class='col'><a href=''>LIGHTS<br>" + data.values[0].light + "<br><p></a></div></div>");
  }
    
</script>

<div class='flex-grid'>

<?php
  try
  {
    // Datenbank öffen
    $db = new PDO('sqlite:/home/pi/farmbot.db');
     //Daten auslesen und anzeigem
    $result = $db->query('SELECT * FROM farmbot;');
    foreach($result as $row)
    {
      print_r("<div class='col'><a href=''>TEMP<br>" . $row[2] . "<br><p></a></div>");
    }
    // Datenbankverbindung schließen
    $db = NULL;
  }
  catch(PDOException $e)
  {
    print 'Fehler: '.$e->getMessage();
  }
?>

</div>



</body>
</html>