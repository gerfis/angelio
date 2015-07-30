<?php
/*
* -------------------------------------------------------
* CLASSNAME:        Tree
* GENERATION DATE:  02.09.2007
* FOR MYSQL TABLE:  Defined by user
* DESCRIPTION:		This class generate a dynamic tree ajax directory of items retrieved from MySQL dabatase tables.
*					Could be used to load folders/categories/directories.
* -------------------------------------------------------
*/

include_once("class.database.php");

// ********************** DECLARACION DE LA CLASE

class Tree { // clase : inicio

// ********************** DECLARACION DE ATRIBUTOS

	var $id = "1";
	var $tiefe="1";
	var $database; // Instancia de la base de datos

	var $table = "tbl_Kunden_Online";
	var $fieldId = "KundenID_online";
	var $fieldFrom = "SponsorID_O";
	var $fieldView = "strUsername_O";
	var $fieldDeph = "strPLZ_O";
	var $fieldAktiv = "ysnInaktiv";	

// ********************** METODO CONSTRUCTOR

	function Tree($id,$tiefe) {
		$this->id = $id;
		$this->tiefe = $tiefe;
		$this->database = new Database();
		if(!isset($this->id))
			$this->id = "1";
		if(!isset($this->tiefe))
			$this->tiefe = $_POST["tiefe"];
	}


// ********************** METODO LIST

	function countSub($id) {
		$sql =  "SELECT COUNT($this->fieldId) AS subOptions FROM $this->table";
		$sql.= " WHERE $this->fieldFrom = \"$id\";";
		// echo $sql . "<br>";
		$this->database->rows = $this->database->getResult($this->database->query($sql),"subOptions");
	}

	function listSub($id) {
		$sql =  "SELECT $this->fieldId,$this->fieldView,$this->fieldDeph,$this->fieldAktiv FROM $this->table";
		$sql.= " WHERE $this->fieldFrom = \"$id\" ORDER BY strUsername_O;";
		// echo $sql . "<br>";
		return $this->database->query($sql);
	}

	function display() {
		$this->listSub($this->id);
		if($this->database->getNumRows() > 0) {
			while($row=$this->database->fetchRow()) {

				$tree_sub=new Tree($row[$this->fieldId],$this-tiefe + 1);
				$tree_sub->countSub($row[$this->fieldId]);

				$output .= "<div class=\"fld_ln\">";
				$tiefe_anzeige = $this->tiefe;
				$tiefe = $this->tiefe + 1;

				if ($tree_sub->database->getNumRows() > 0 && $tiefe < 8) { 
					$output .= "<a class='Zweig' href=\"Javascript:loadTree(".$row[$this->fieldId].",".$tiefe.")\">&nbsp;+&nbsp;</a>";
				} else {
					$output .= "<span class='Blatt' >&nbsp;+&nbsp;</span>"; 
				}
				$output .= "&nbsp;&nbsp;<a class='Tiefe".$tiefe." istaktiv" . $row[$this->fieldAktiv] . "' href='/downline/".$row[$this->fieldId]."'>".$tiefe_anzeige.". <span id='KleinBild'>".$row[$this->fieldView]."</span></a>";
				$output .= "<div id=\"c".$row[$this->fieldId]."\" class=\"fld_ln\" style=\"display:none;\"></div>";
				$output .= "</div><br style=\"clear:both\">";
			}
		}
		// echo $output;
		return $output;
	}

} // clase : fin

?>