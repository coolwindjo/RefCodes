#!/bin/bash

dos2unix L3NeedCopyList.txt

L3folder=L3
mkdir $L3folder

while read value; do
	echo $value
	cp "//10.157.136.102/adas_db_1/L3_AutoConversion/$value.L3" $L3folder -v
#	wget64 "http://10.157.136.122:8080/adas_db_1/Daimler_MPC5.5/$value/GT/$value.zip" -P GT
#	unzip GT/$value.zip -d GT/$value
done < L3NeedCopyList.txt
