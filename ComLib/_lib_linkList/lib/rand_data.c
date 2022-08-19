#include "rand_data.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
	ex:
		printf("%d\n", randNum(5,10));
		printf("%lf\n", randDouble(0, 5, 8));
		puts(randString(5, 1234));
		putchar(randChar(2));
*/

// ���������ʼ��
void randInit() {
	srand((uint)time(NULL));
}

// ���һ�������� ָ����Χ�� ֧����������
int randNum(int min, int max) {

	if(min>max) return 0;
	// ... check max and min
	else if(min==max) return max; // resNum = max;

	if((min==0)&&(max<0)) {
		return -(rand()%(-(max-1)));
	} else if((min==0)&&(max>0)) {
		return (rand()%(max+1));
	} else if((min<0)&&(max<0)) {
		return rand()%(max-min+1)+min;
	} else if((min<0)&&(max>0)) {
		return -(rand()%((-min)-(-max)+1)+(-max));
	} else if((min>0)&&(max>0)) {
		return ((rand()%(max-min))>(-min))?(rand()%max+1+0):(-(rand()%(-min)+1+0));
	}

	return ;
}

// ���һ��С���� ָ����Χ��
double randDouble(int begin, int end, uint valueLen) {
	double resNum = 0.0, tmpNum=0.0;
	int i=0;

	// �������
	resNum = (double)randNum(begin, end);

	// ���С��
	for(i=0; i<valueLen+1; i++) {
		tmpNum = ((double)randNum(0, 9))/(10.0*(i+1));
		resNum += tmpNum;
		tmpNum = 0.0;
	}
	return resNum;
}

// ���һ���ַ����� ����ָ���ַ������ȣ� ����ָ���ַ��� (base: ASCII)
// seekId: 1����д  2��ȫСд  3������ 4�������ַ�
// ex: seekId = 134   ����������д�����֣������ַ��� �ַ������
char *randStr(uint strLength, uint seekId) {
	char seekIdStr[100], *resStr = NULL;
	uint nowLength = 0, seekLength = 0;

	itoa(seekId, seekIdStr, 10);
	seekLength = strlen(seekIdStr);
	resStr = (char *)malloc(sizeof(char)*strLength);

	while(nowLength < strLength) {

		resStr[nowLength] = randChar(seekIdStr[rand()%seekLength] - '0');

		nowLength++;
	}
	resStr[nowLength] = '\0';
	return resStr;
}

// ���һ���ַ���ָ���ַ���
char randChar(uint seekId) {
	switch(seekId) {
		case 1:
			return 'A' + rand()%('Z'-'A'+1);
			break;
		case 2:
			return 'a' + rand()%('z'-'a'+1);
			break;
		case 3:
			return '0' + rand()%('9'-'0'+1);
			break;
		case 4:
			switch(rand()%4) {
				case 0:
					return ' ' + rand()%('/'-' '+1);
					break;
				case 1:
					return '[' + rand()%('['-'`'+1);
					break;
				case 2:
					return ':' + rand()%('@'-':'+1);
					break;
				case 3:
					return '{' + rand()%('{'-'~'+1);
					break;
				default:
					return ' ' + rand()%('/'-' '+1);
					break;
			}
			break;
			// more ...
		default:
			return '\0';
			break;
	}
}


// ��ȡ��ǰʱ�� 
/*
	char nowTime[32] = {0};
    getNowTime(nowTime);
*/
int getNowTime(char *nowTime){
	char acYear[5] = {0};
	char acMonth[5] = {0};
	char acDay[5] = {0};
	char acHour[5] = {0};
	char acMin[5] = {0};
	char acSec[5] = {0};

	time_t now;
    struct tm* timenow;
    
    time(&now);
    timenow = localtime(&now);

    strftime(acYear,sizeof(acYear),"%Y",timenow);
    strftime(acMonth,sizeof(acMonth),"%m",timenow);
    strftime(acDay,sizeof(acDay),"%d",timenow);
    strftime(acHour,sizeof(acHour),"%H",timenow);
    strftime(acMin,sizeof(acMin),"%M",timenow);
    strftime(acSec,sizeof(acSec),"%S",timenow);

	strncat(nowTime, acYear, 4);
	strcat(nowTime, "-");
	strncat(nowTime, acMonth, 2);
	strcat(nowTime, "-");
	strncat(nowTime, acDay, 2);
	strcat(nowTime, " ");
	strncat(nowTime, acHour, 2);
	strcat(nowTime, ":");
	strncat(nowTime, acMin, 2);
	strcat(nowTime, ":");
	strncat(nowTime, acSec, 2);

	return 0;
}









