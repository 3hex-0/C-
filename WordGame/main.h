#ifndef _MAIN_H_
#define _MAIN_H_

#define WORD_ITEM_MAX 100
#define WORD_STRING_LENGTH_MAX 100
#define WORD_LIST_PATH "./data/wordlist.txt"
#define ITEM_COUNT 10

// ���ʽṹ�� 
typedef struct _Selection{
	char englishWord[100];
	char chineseWord[100];
}SELECTIOIN;

// ѡ�� 
typedef struct _Question{
	SELECTIOIN pos[4]; // ѡ�� 
	int trueSelection; // ��ȷ���±� 
	int grade;    // ����
	int mode; // ����ģʽ  1������Ӣ  2��Ӣ���� 
}QUESTION;

// �û����γɼ��ṹ��
typedef struct _UserGrade{
	char nowTime[32];
	int grade;
}USERGRADE; 

// �û��ɼ��ṹ��
typedef struct _SysUserGrade{
	USERGRADE userGradeTen[10];
	USERGRADE userGradeMax;
}SYSUSERGRADE; 

SYSUSERGRADE sysUserGrade;

SELECTIOIN exSelection[WORD_ITEM_MAX];

void sysInit(void);
int splitString(char *posString, char resString[][WORD_STRING_LENGTH_MAX]);
int loadWordByFile(char *filePath);
void showMainMenu(void);
void randSelection(int itemLengthMax, int index);
int selectIndex(int key);

void itemBeginGame(void);
void itemGradeRule(void);
void printUserGrade(int mode);

void countUserGrade(QUESTION *tmpQuestion);

void debug_showArr(void);

#endif
 
