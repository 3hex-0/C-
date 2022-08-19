#include "richtext.h"
#include <stdio.h>
#include <windows.h>
/* 
 	filename : richtext.h/.c (���ı�API)
 	version  : v1.0
	content  : ����ʽ���ı���� API 
 	author   : 3hex
 	date     : 2020-10-27 
*/ 

/*
	���ܣ���ӡ��ʾ�ַ�������ɫ���壩 
*/  


// �ȴ� ������ 
void wait(void){
	printf("Enter������...");
	fflush(stdin);
	getchar();
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

void pSCursor(char *tmpString)
{
	_setConsoleTextColor(GMT_B_RED,GMT_F_HALF_WHITE);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

void pSInfo(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_HALF_LIGHT_BLUE);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCInfo(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_HALF_LIGHT_BLUE);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	���ܣ���ӡ�����ַ�������ɫ���壩 
*/  
void pSWarning(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_YELLOW);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCWarning(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_YELLOW);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	���ܣ���ӡ�����������ɫ���壩 
*/  
void pSError(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_RED);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCError(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_RED);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	���ܣ���ӡ��ȷ��ʾ�ַ�������ɫ���壩 
*/  
void pSSuccess(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_GREEN);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCSuccess(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_GREEN);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	���ܣ�����������ɫ
	����������ɫ��ǰ��ɫ��������ɫ��[����ʹ������] 
	���أ��� 
*/  
void _setConsoleTextColor(int backgroundColor,int foregroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor | foregroundColor);
}
