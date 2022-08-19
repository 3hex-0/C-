#include <stdio.h>
#include <stdlib.h>
//#include <ctpye.h>
#include "gui_menu_tool.h"
#include "richtext.h"
#include "filehandler.h"
#include "gen_def.h"
#include "main.h"

extern SELECTIOIN exSelection[WORD_ITEM_MAX];
extern SYSUSERGRADE sysUserGrade;
int trueSelectionAllCount[ITEM_COUNT] = {-1}, tureSelectionIndex=0;
int gameNowTimer = 0, exitFlag=-1;


int main() {
	char tmpMainInput;

	sysInit();
	
	mainBegin:
	clearScreen();
	showMainMenu();

	// ����ģ�� 
	do{
		printf("\n�����룺");
		scanf("%c", &tmpMainInput);
		fflush(stdin); // ������뻺�� 
		if((tmpMainInput-'1'>=0)&&(tmpMainInput-'1'<=2)) break;
	}while(1);
	
	// ����ģ�� 
	switch(tmpMainInput){
		case '1': // ��ʼ���� 
			itemBeginGame();
			exitFlag = 1;
			break;
		case '2': // ���ֹ��� 
			itemGradeRule();
			exitFlag = 1;
			break;
		case '3': // �˳�ϵͳ 
			exitFlag = 0;
			break;
		default:
			break;
	}
	
	// �쳣�˳�ģ�� 
	if(exitFlag<=0){
		pSSuccess("[~]�����˳��ɹ�");
		return 0;
	}else{
		goto mainBegin; 
	}
	
	return 0;
}

void itemGradeRule(void){
	pSError("1.ÿ�������������Ӣ��Ӣ����(��10��)");
	pSWarning("2.ÿ�δ�Խ���һ��");
	pSSuccess("3.ÿ�δ���۷�");
	
	printf("\n\n[~]��߳ɼ�:\n");
	if(gameNowTimer!=0){
		printf("[ʱ��]:%s\t[�ɼ�]:%d\n", sysUserGrade.userGradeMax.nowTime, 
										sysUserGrade.userGradeMax.grade);
	}else{
		pSInfo("��δ��ʼ����Ϸ��û����߼�¼��"); 
	}
	
	printf("[~]��10�γɼ�:\n");
	printUserGrade(0);
	wait();
}

void itemBeginGame(void){
	char nowTime[32] = {0}; 
	int len=0, i=0, maxIndex=0; 
	len = loadWordByFile(WORD_LIST_PATH);
	
	// ��ʼ����γɼ� 
	sysUserGrade.userGradeTen[gameNowTimer].grade = 0;
	getNowTime(nowTime);
	strcpy(sysUserGrade.userGradeTen[gameNowTimer].nowTime, 
			nowTime); 
	
	// ��ʼ��Ϸ 
	for(i=0;i<ITEM_COUNT;i++){
		randSelection(len, i);
	}
	
	// ��ӡ���γɼ�
	printUserGrade(gameNowTimer+1);
//	printUserGrade(0);
	
	gameNowTimer++;
	
	// ��մ����¼ 
	for(i=0;i<ITEM_COUNT;i++){
		trueSelectionAllCount[i] = -1;
	}
	
	// ͳ�������� 
	sysUserGrade.userGradeMax = sysUserGrade.userGradeTen[0];
	for(i=0;i<10;i++){
		if(sysUserGrade.userGradeTen[i].grade>sysUserGrade.userGradeMax.grade)
		{
			maxIndex = i;
		}
	}
	if(maxIndex!=0){
		sysUserGrade.userGradeMax = sysUserGrade.userGradeTen[maxIndex];
	}
	
	wait();
} 

// ��ӡ�ɼ� 
// mode: 0 ȫ���ɼ� 
// ���� ��ӡ��Ӧ�� �±�ĳɼ� �����Ϊ10 
void printUserGrade(int mode){
	int i=0, n=(gameNowTimer<10)?gameNowTimer:10;
	if(mode==0){
		for(i=0;i<n;i++){  // <-----------------
			if(gameNowTimer!=0)
				printf("[����]%d\t[ʱ��]:%s\t[�ɼ�]:%d\n", i+1, sysUserGrade.userGradeTen[i].nowTime, 
										sysUserGrade.userGradeTen[i].grade);
		}
		for(;i<10;i++){
			printf("[����]%d\t[ʱ��]:%s\t[�ɼ�]:%s\n", i+1,"\\", "\\");
		}
	}else if(mode<=10){
		printf("[����]%d\t[ʱ��]:%s\t[�ɼ�]:%d\n", mode, sysUserGrade.userGradeTen[mode-1].nowTime, sysUserGrade.userGradeTen[mode-1].grade);
	}else{
		printf("ֻ������10�μ�¼��\n[����]%d\t[ʱ��]:%s\t[�ɼ�]:%d\n", 10, sysUserGrade.userGradeTen[9].nowTime, 
														sysUserGrade.userGradeTen[9].grade);
	}
}

// ϵͳ��Ҫ�ĳ�ʼ�� 
void sysInit(void)
{
	int i=0;
	for(i=0;i<ITEM_COUNT;i++){
		trueSelectionAllCount[i] = -1;
	}
	
	srand(time(NULL));
}

// �����һ�� ����
// һ����ȷ�� 3�������
void randSelection(int itemLengthMax, int index){
	int i=0, randNum[4]={0}, tmpIndex=0;
	QUESTION exQuestion;
	
	puts("");
	
	// ����4��α�����
	do{
		tmpIndex = rand()%itemLengthMax;
	}while(selectIndex(tmpIndex));
	
//	debug_showArr();
	
	randNum[0] = tmpIndex;
	
	if(tureSelectionIndex<ITEM_COUNT)
		trueSelectionAllCount[tureSelectionIndex++] = randNum[0]; // ��¼��������Ŀ 
	
	randNum[1] = (randNum[0]+3)%itemLengthMax;
	randNum[2] = (randNum[1]+3)%itemLengthMax;
	randNum[3] = (randNum[2]+3)%itemLengthMax;
	
//	printf("%d , %d %d %d %d\n",itemLengthMax, randNum[0], randNum[1],randNum[2],randNum[3]);
	
	// װ��ѡ�� 
	i=0;	 
	exQuestion.pos[0] = exSelection[randNum[0]];
	exQuestion.pos[1] = exSelection[randNum[1]];
	exQuestion.pos[2] = exSelection[randNum[2]];
	exQuestion.pos[3] = exSelection[randNum[3]];
	
	exQuestion.trueSelection =  rand()%4; // �����ȷ��
	exQuestion.grade = 1; 
	exQuestion.mode = rand()%2+1; // �������ģʽ  
	
	// ��ʾ
	// ��� 
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_LIGHT_BLUE);
	
	printf("%d.", index+1);
	
	if(exQuestion.mode == 1){ // ����Ӣ 
		printf("[%s] ����ȷ����:\n", 
		exQuestion.pos[exQuestion.trueSelection].chineseWord);
	}else if(exQuestion.mode == 2){// Ӣ����  
		printf("[%s] ����ȷ����:\n", 
		exQuestion.pos[exQuestion.trueSelection].englishWord);
	}
	for(i=0;i<4;i++)
	{
		if(exQuestion.mode == 1){ // ����Ӣ 
			printf("%c. %s\t\t", 'A'+i, exQuestion.pos[i].englishWord);
		}else if(exQuestion.mode == 2){// Ӣ���� 
			printf("%c. %s\t\t", 'A'+i, exQuestion.pos[i].chineseWord); 
		}
	} 
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
	
	puts("");
	
	// ͳ����εĳɼ� 
	countUserGrade(&exQuestion);
}

void countUserGrade(QUESTION *tmpQuestion){
	 char tmpInput;
	
	do{
		printf("\n������𰸣�");
		tmpInput = getchar();
		fflush(stdin);
		if((((tmpInput-'A')<=3)&&((tmpInput-'A')>=0))||
			(((tmpInput-'a')<=3)&&((tmpInput-'a')>=0)))
			break;
	}while(1);
	
	// �ӷ� 
	if(((tmpInput-'A')==tmpQuestion->trueSelection)
		||((tmpInput-'a')==tmpQuestion->trueSelection)){
			sysUserGrade.userGradeTen[gameNowTimer].grade += tmpQuestion->grade;
		}
}

// ��ѯ α����� �����ظ� 
int selectIndex(int key){
	int i=0, end=ITEM_COUNT-1;
	int low=0,high=0,mid=0;
	// ���� 
	while(end){
		for(i=0;i<=end;i++)
		{
			if(trueSelectionAllCount[i]>trueSelectionAllCount[i+1]){
				SWAP(trueSelectionAllCount[i], trueSelectionAllCount[i+1]);
			}
		}
		end--;
	}
//	printf("Key:%d\n", key);
	// ���ַ�
	low = 0, high = ITEM_COUNT-1;
	while(low<high){
		mid = (low+high)/2;
		if(trueSelectionAllCount[mid] == key){
//			puts("true");
			return 1;
		}else if(trueSelectionAllCount[mid] > key){
			high = mid-1;
		}else{
			low = mid+1;
		}
	}
//	puts("false");
	return 0;
} 

// ���뵥��
int loadWordByFile(char *filePath){
	int i=0, readedLength=0, j=0;
	char tmpWordString[WORD_ITEM_MAX][WORD_STRING_LENGTH_MAX], tmpString[2][WORD_STRING_LENGTH_MAX];
	readedLength = readStrFromFile(WORD_LIST_PATH , tmpWordString); // ���뵥���ļ�
	for(i=0;i<readedLength;i++){
		// ȥ������ 
		j = strlen(tmpWordString[i]);
		tmpWordString[i][j-1] = tmpWordString[i][j];
		
		// �и��ַ��� 
		if(splitString(tmpWordString[i], tmpString))
		{
			// ���� 
			strcpy(exSelection[i].englishWord, tmpString[0]);
			strcpy(exSelection[i].chineseWord, tmpString[1]);
		//	printf("%s @ %s\n", exSelection[i].englishWord, exSelection[i].chineseWord);
		}
	} 
	return readedLength;
} 

// ����ַ��� dev:space(ASCII:\s \t) 
int splitString(char *posString, char resString[][WORD_STRING_LENGTH_MAX]){
	char *p = posString;
	int i=0;
	if(isspace(posString[i])) return 0;
	
	// english
	while(isalpha(*p))
	{
		(*resString)[i++] = *p;
		p++;
	}
	(*resString)[i] = '\0';
	resString++;
	
	while(isspace(*p)) p++;
	
	// chinese
	i=0;
	while(*p)
	{
		(*resString)[i++] = *p;
		p++;
	}
	(*resString)[i] = '\0';
	return 1;
}

// ������ 
void showMainMenu(void){
	char itemText[3][50] = {"1.��ʼ��ϰ","2.���ֹ���","3.�˳���ϰ"};
	initMenu("���ʴ�����Ϸ",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(16);
	showMenu(); 
}

void debug_showArr(void){
	int i=0;
	for(i=0;i<ITEM_COUNT;i++){
		if(i%5==0)
			puts("");
		printf("%d\t", trueSelectionAllCount[i]);
	}
}
