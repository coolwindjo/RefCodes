#!/bin/bash

dos2unix DAT_NeedCopyList.txt

DATfolder=DAT
mkdir $DATfolder

while read value; do
	echo $value
	#cp "//10.157.136.102/adas_db_1/Daimler_MPC5.5/$value/GT/$value.zip" L3/ -v
	#https://stackoverflow.com/questions/22009364/is-there-a-try-catch-command-in-bash#answer-48066872
	if cp //10.157.136.102/adas_db_1/Cosette/Daimler_MPC5.5/$value/$value.dat $DATfolder -v ; then
		echo 'Hello'
	elif cp //10.157.136.102/adas_db_31/Cosette/Daimler_MPC5.5/$value/$value.dat $DATfolder -v ; then
		echo 'Hello2'
	else
		cp //10.157.136.102/vadas/Cosette/Daimler_MPC5.5/$value/$value.dat $DATfolder -v
	fi

	#./DATconverter_MPC5.5_v0.60.exe -i= `realpath $DATfolder/#value.dat` -t= 50

done < DAT_NeedCopyList.txt

# ./L3converter/Dat2L3.exe L3converter/parameters.ini