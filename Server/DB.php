<?php


// //getSearch
define("GETVAR_USERID", "userid");
define("GETVAR_BIOJSON", "biojson");
define("POSTVAR_USERID", "userid");
define("POSTVAR_BIOJSON", "biojson");
define("POSTVAR_CARD", "card");
define("POSTVAR_HEADER", "header");

define("POSTVAR_USER", "user");
define("POSTVAR_PASS", "pass");
define("POSTVAR_NAME", "name");


// define("GETVAR_EVENTID", "eventid");


function getSQLConnection(){
	$host="localhost";
	$user="root";
	$password="root";
	$database="resonate";
	$link = mysqli_connect($host,$user,$password,$database);
	return $link;
}

function endSQLConnection($CONNECTION){
	mysqli_close($CONNECTION);
}

function beginTransaction($CONNECTION){
	if(mysqli_connect_errno($CONNECTION)){
		return FALSE;
	}else{
		mysqli_autocommit($CONNECTION, FALSE);
		return TRUE;
	}
}

function endTransaction($success,$CONNECTION){
	if($success){
		mysqli_commit($CONNECTION);
	}else{
		mysqli_rollback($CONNECTION);
	}
}

?>