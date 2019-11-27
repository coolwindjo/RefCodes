#!/bin/bash

dos2unix GTNeedCopyList.txt

while read value; do
	echo $value

	mkdir -p $value
	if cp -v //10.157.136.102/adas_db_1/Cosette/Daimler_MPC5.5/$value/GT/* $value; then
		echo 'Hello'
	elif cp -v //10.157.136.102/adas_db_3/Cosette/Daimler_MPC5.5/$value/GT/* $value; then
		echo 'Hello2'
	else
		cp -v //10.157.136.102/vadas/Cosette/Daimler_MPC5.5/$value/GT/* $value
	fi
done < GTNeedCopyList.txt

