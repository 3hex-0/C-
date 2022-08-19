#include "gui_menu_tool.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

/*
	��GUI��ƹ��߿⣨ר�ã���ͨ�ã� 
	���ߣ�3hex (2020.9.26) 
	�÷���
		char itemText[3][50] = {"1.Star","2.Stop","3.Quit"};
		initMenu("Menu",itemText,sizeof(itemText)/sizeof(itemText[0]));
		createMenu(20,13);
		showMenu(); 

*/ 
MENU menu;
MENU_STYLE menuStyle = {{GMT_B_BLACK,GMT_F_WHITE}, '-'};
 
/*
	���ܣ���ʼ���˵� 
	���������⣬��Ŀ�б���ĳ���� 
	���أ��� 
*/
void initMenu(char title[STRING_MAX],char itemText[MENU_ITEM_COUNT_MAX][STRING_MAX],unsigned int itemCount)
{
	unsigned int i=0;
	strcpy(menu.title,title);
	menu.itemCount = itemCount;
	
	for(i=0;i<itemCount;i++)
	{
		strcpy(menu.itemText[i],itemText[i]);
	}
} 

/*
	���ܣ�����һ���˵� 
	������marginLeft[��߾�], styleID[���]
	���أ��� 
*/
/*
	styleID: AB
	A: 1:'*' 2:'-'(def) 3:'#'
	B: 1:B_BLACK F_WHITE(def) 2:B_RED F_WHITE 3: B_WHITE F_BLACK
	ex: 23��ʾ ʹ��"#"��Ϊ�߽��ַ������ð׵׺��� 
*/ 
void createMenu(unsigned int marginLeft,unsigned int styleID)
{
	menuStyleSelecter(styleID);
	menuStyle.margin[0] = marginLeft;
	menuStyle.margin[1] = 0;
}

/*
	���ܣ���ʾ�˵�  
	�������� 
	���أ��� 
*/
void showMenu()
{
	int i=0,j=0;
	//clearScreen();
	setConsoleTextColor(menuStyle.textStyle[0], menuStyle.textStyle[1]);
	setConsoleTextPositionByXY(menuStyle.margin[0],menuStyle.margin[1]);
	
	putchar(menuStyle.charType);
	printf("\t\t");
	printf(menu.title);
	printf("\t\t");
	putchar(menuStyle.charType);
	setConsoleTextPositionByXY(menuStyle.margin[0],1+menuStyle.margin[1]);
	
	
	for(i=0;i<menu.itemCount;i++){
		setConsoleTextPositionByXY(menuStyle.margin[0],i+2+menuStyle.margin[1]);
		putchar(menuStyle.charType);
		printf("\t\t");
		printf(menu.itemText[i]);
		printf("\t\t");
		putchar(menuStyle.charType);
	}
	resetAll();
}

/*
	���ܣ��˵����ѡ����������styleID�Բ˵����з����� 
	�������� 
	���أ��� 
*/
void menuStyleSelecter(unsigned int styleID)
{
	switch(styleID/10)
	{
		case 1:
			menuStyle.charType = '*';
			break;
		case 21:
			menuStyle.charType = '-';
			break;
		case 3:
			menuStyle.charType = '#';
			break;
		default:
			menuStyle.charType = '-';
			break;	
	}
	
	switch(styleID%10)
	{
		case 1:
			menuStyle.textStyle[0] = GMT_B_BLACK;
			menuStyle.textStyle[1] = GMT_F_WHITE;
			break;
		case 2:
			menuStyle.textStyle[0] = GMT_B_RED;
			menuStyle.textStyle[1] = GMT_F_WHITE;
			break;
		case 3:
			menuStyle.textStyle[0] = GMT_B_WHITE;
			menuStyle.textStyle[1] = GMT_F_BLACK;
			break;
		default:
			menuStyle.textStyle[0] = GMT_B_BLACK;
			menuStyle.textStyle[1] = GMT_F_WHITE;
			break;	
	}
}

/*
	���ܣ�����������ɫ
	����������ɫ��ǰ��ɫ��������ɫ��[����ʹ������] 
	���أ��� 
*/  
void setConsoleTextColor(int backgroundColor,int foregroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor | foregroundColor);
}

/*
	���ܣ���������λ�ã�ͨ��xy���� 
	������x,y 
	���أ��� 
*/  
void setConsoleTextPositionByXY(int x,int y)
{
	COORD c;
	c.X = x, c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);	
} 

/*
	���ܣ�������������  
	��������
	���أ��� 
*/ 
void resetAll()
{
	setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
} 

/*
	���ܣ�����  
	��������
	���أ��� 
*/  
void clearScreen()
{
	system("cls");
}

