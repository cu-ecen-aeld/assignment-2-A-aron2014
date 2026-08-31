#!/bin/bash

numargs=$#

if [ $numargs -lt 2 ]
then
	echo args not specified 	
	exit 1
fi

if [ -z $1 ]
then 
	echo empty target directory
	exit 1
fi
if [ -z $2 ]
then 
	echo empty string to write
	exit 1
fi
writefile=$1
writestr="$2"

touch $writefile
if [ ! -f $writefile ]
then
	echo file could not be created
	exit 1
fi
echo $writestr>$writefile
