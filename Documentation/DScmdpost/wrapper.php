<?php
//wrapper.php written 07/12/2003 By Gregory Dietsche for IceBox. All Rights Reserved.
//Modified 7/25/2003 by Greg to work with the DS website.

//ignore any leading slashes as they will not be necessary (this is partially security related)
	$file=ltrim($_GET['file'],"\\/");
	
//check file for possible arguments (this is probabbly a dirty hack for php session variables?)
//with the apache .htaccess file, we can end up with $_GET['file']=index.htm?var=someval so it needs
//to be seperated out
	parse_str(substr($file,strpos($file,"?")+1), $arglist);	//Place any argument (1 at most expected) into $_GET
	while(list($var, $val) = each($arglist))
	{
		$_GET[$var]=$val;
		$$var=$val;
	}
	
//a fancy way of seperating path and argument info out of the $file variable
	$file=parse_url($file);
	$_GET['file']=$file=$file['path'];
	
	if(!isset($_GET['key']) || $_GET['key']!="125sdgsdfg4mn4580zlgmk34Kl")
	{
		header("Location: http://www.detachedsolutions.com/404.php"); 
		die();
	}

	if(!(eregi("^[a-z_./ 0-9]*$", $file) && !eregi("\\.\\.", $file)) || substr($file,-4)!=".htm")
	{
		header("Location: http://www.detachedsolutions.com/404.php");
		die();
	}

	//a fix ... otherwise, this script expects to run at the root...
	$file=substr($file,strlen("cmdpost/"),strlen($file)-strlen("cmdpost/"));
	
	if(!is_file($file))
	{//a true 404... the file does not exist
		header("Location: http://www.detachedsolutions.com/404.php");
		die();
	}
	else
		$content=@file($file);

	$pagename=rtrim($content[0],"\n\r");	//Clean Up for display in the Title bar area
	$pagename=str_replace("<!--","",$pagename);	//remove any comment tags from the first line
	$pagename=str_replace("-->","",$pagename);
	$pagename=strip_tags($pagename);		//Clean Up for display in the Title bar area
	
	$content=implode('',$content);			//prepare the array for display via echo

//Show The Page
	include "../begin.php";
		echo $content;
	include "../end.php";
?>