<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
   "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="de" lang="de">
<?php
	include("class.tree.php");
?>
<head>
	<title>Tree Test</title>
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>

	<!-- Ajax class -->
	<script type="text/javascript" src="ajax.js"></script>
	<!-- Tree class -->
	<script type="text/javascript" src="tree.js"></script>
	<link rel="stylesheet" type="text/css" href="tree.css" />

</head>
<body>

<!-- Zutaten -->
          <div id="Tree">
	    <?php
	$tree=new Tree($_GET["id"],1);    // or $_POST["id"] numeric value of the root folder/category/directory to create the tree
	$tree->display();
	?>
            </div>
</body>
</html>
