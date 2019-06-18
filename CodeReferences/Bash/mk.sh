#!/bin/bash
dos2unix EvaluateDatList.txt

# while은 EvaluateDatList.txt에서 한 줄씩 데이터를 읽어 
# -r은 bash에서 \(백슬래쉬)를 읽을 때 사용하는 기호입니다.
while read -r path; do

	echo $path

	# EvaluateDatList.txt에는 평가할 DAT의 절대경로가 있습니다. 절대경로에서 파일이름을 파싱합니다.
	# 마지막에 .dat 라는 인자를 추가하여 확장자 없이 파일이름만 추출합니다.
	name=`basename $path .dat`	

	# 파일이름으로 결과가 저장될 폴더를 미리 생성합니다.
	mkdir -p "/e/Result/$name"

	# 파일경로를 EvaluateDat.txt에 출력합니다. 이 파일은 ADTF 필터에서 사용합니다.
	echo "$path" > EvaluateDat.txt

	# VL1300에 영상을 입력할 DAT의 경로를 입력합니다.
	echo "$path" > "/d/Reprocessing/vl1300_rel_20180828/PC SW/file_LND.list"

	# ADTF를 실행합니다. 반드시 LND_HiLS2가 activate되어 있어야 합니다.
	'/c/Program Files/ADTF/2.13.2/bin/adtf_devenv.exe' "C:\Users\LGE\Desktop\MPC55_Measurement\config\system.xml" -run
done < EvaluateDatList.txt

# # 
# DATfolder=/d/LND
# while read -r value; do
#need to be modified ip address
# 	if cp //10.157.136.102/adas_db_1/Cosette/Daimler_MPC5.5/$value/$value.dat $DATfolder -v ; then
# 		echo 'Hello'
# 	elif cp //10.157.136.102/adas_db_3/Cosette/Daimler_MPC5.5/$value/$value.dat $DATfolder -v ; then
# 		echo 'Hello2'
# 	else
# 		cp //10.157.136.102/vadas/Cosette/Daimler_MPC5.5/$value/$value.dat $DATfolder -v
# 	fi

# 	# EvaluateDatList.txt에는 평가할 DAT의 절대경로가 있습니다. 절대경로에서 파일이름을 파싱합니다.
# 	# 마지막에 .dat 라는 인자를 추가하여 확장자 없이 파일이름만 추출합니다.
# 	name=$value
# 	path=${DATfolder}/${value}.dat
# 	echo $path

# 	# 파일이름으로 결과가 저장될 폴더를 미리 생성합니다.
# 	mkdir -p "/e/Result/$name"

# 	# 파일경로를 EvaluateDat.txt에 출력합니다. 이 파일은 ADTF 필터에서 사용합니다.
# 	echo "$path" > EvaluateDat.txt

# 	# VL1300에 영상을 입력할 DAT의 경로를 입력합니다.
# 	echo "$path" > "/d/Reprocessing/vl1300_rel_20180828/PC SW/file_LND.list"

# 	# ADTF를 실행합니다. 반드시 LND_HiLS2가 activate되어 있어야 합니다.
# 	'/c/Program Files/ADTF/2.13.2/bin/adtf_devenv.exe' "C:\Users\LGE\Desktop\MPC55_Measurement\config\system.xml" -run

# 	rm -rf $path
# done < EvaluateDatList.txt
# only DAT name