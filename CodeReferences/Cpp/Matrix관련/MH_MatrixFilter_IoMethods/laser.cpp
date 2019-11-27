// laser.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

class CVector{
public:
	double x,y;
};


#define COL 698
#define ROW 529

int _tmain(int argc, _TCHAR* argv[])
{
	FILE *f = fopen("aa.txt","r");
	char buf[500];

	CVector **data = new CVector*[COL];
	for(int n=0; n<COL; n++){
		data[n] = new CVector[ROW];
	}

	int i=0;
	int j=0;

	while(fscanf(f,"%s",buf)!=NULL){
		if(buf[strlen(buf)-1]==','){
			buf[strlen(buf)-1]='\0';
			//break;
		}
		//printf("%s\n",buf);
		i++;
		//if(atoi(buf)==2) break;
		if(i%2==0) {
			data[j][i/2-1].x = atof(buf);
		}
		if(i%2==1 & i!= 1) {
			data[j][i/2-1].y = atof(buf);
		}

		if(i==ROW*2+1) {
			i=0;
			j++;

			if(j>=COL) break;
		};
	}
	//printf("total num is %d",i);
	//return 0;

	//Test1 1열 x만 찍기
	for(int k=0; k<529; k++){
		printf("%f\n", data[0][k].x);
	}

	
	return 0;
}

