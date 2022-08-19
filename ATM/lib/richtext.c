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
