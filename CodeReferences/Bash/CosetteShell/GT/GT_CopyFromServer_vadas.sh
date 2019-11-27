#!/bin/bash

dos2unix GTNeedCopyList.txt

GTfolder=GT
mkdir $GTfolder

while read value; do
	echo $value
	#cp "//10.157.136.102/adas_db_1/Daimler_MPC5.5/$value/GT/$value.zip" L3/ -v
	if wget64 "http://10.157.136.122:8080/adas_db_1/Daimler_MPC5.5/$value/GT/$value.zip" -P $GTfolder; then
		echo 'Hello'
	else
		wget64 "http://10.157.136.122:8080/vadas/Daimler_MPC5.5/$value/GT/$value.zip" -P $GTfolder
	fi
	unzip $GTfolder/$value.zip -d $GTfolder/$value
done < GTNeedCopyList.txt