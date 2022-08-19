#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "gen_def.h"
#include "richtext.h"
#include "gui_menu_tool.h"
#include "filehandler.h"
#include "main.h"

/*
	�û���XM ��С���� 
	���룺123456
	��ע������������󳬹�3�Σ��޷���½�� ��./data/infoload.txt�У���3�޸�Ϊ0�������õ�½������ 
		./--lib���Զ���Ŀ��ļ�
		  --data��ϵͳ����������ļ�����
		  --local�����ԣ�CN�����ģ�EN��Ӣ�ģ� 
*/

int main(){
	char str[100][LINE_TEXT_MAX];
	byte inputPara=0;
	
	// 0.���ſ����޲���
	checkCard();	
	
	// 1.��֤�û� 
	if(verifyUser()==0) {
		pSInfo("[~]Enter������");
		wait(); 
		return ;
	} 
	
	pSInfo("[~]Enter������");
	wait();
	
	// 2.����ѡ�����
	initInterface();  
	
	// 3.���˵�����
	mainInterface();  
	 
	while(1)
	{
		if(langFlag==1){
			pSCursor("\n[���˵�]");
		}else{
			pSCursor("\n[Main menu]");
		}

		userInputInfo();
		scanf("%d", &inputPara);
		
		// 4. ����ѡ�� 
		switch(inputPara)
		{
			// 1.��ѯ
			case 1:
				if(langFlag==1){
					pSCursor("\n[���˵�]-[��ѯ]");
				}else{
					pSCursor("\n[Main menu]-[Query]");
				}
				itemFuncCheck();
				break;
			// 2.ȡ��
			case 2:
				if(langFlag==1){
					pSCursor("\n[���˵�]-[ȡ��]");
				}else{
					pSCursor("\n[Main menu]-[Withdraw money]");
				}
				
				itemFuncUpdate(1);
				break;
			// 3.���
			case 3:
				if(langFlag==1){
					pSCursor("\n[���˵�]-[���]");
				}else{
					pSCursor("\n[Main menu]-[Deposit]");
				}
				itemFuncUpdate(2);
				break;
			// 4.ת�� 
			case 4:
				if(langFlag==1){
					pSCursor("\n[���˵�]-[ת��]");
				}else{
					pSCursor("\n[Main menu]-[Account details]");
				}
				itemFuncUpdate(3); 
				break;
			// 5.��ˮ
			case 5:
				if(langFlag==1){
					pSCursor("\n[���˵�]-[��ˮ]");
				}else{
					pSCursor("\n[Main menu]-[Transfer accounts]");
				}
				itemFuncDetails();
				break;
			// 6.�˳�
			case 6:
				exitFlag = 1;
				break;
			default:
				exitFlag = 2;
				break;
		}
		
		// ����Ļ  
		clearScreen();
		showMenu();
		
		// �˳����� 
		if(exitFlag==1)
		{
			clearScreen();
			if(langFlag==1)
			{
				pSSuccess("\n[~]�����˳��ɹ�");
			}else
			{
				pSSuccess("\n[~]Exit Successfully��");
			}
			wait();
			break; 
		}else if(exitFlag==2){
			clearScreen();
			if(langFlag==1)
			{
				pSError("\n[~]�쳣���룬�˳���");
			}else
			{
				pSError("\n[~]Abnormal input, Exit!");
			}
			wait();
			break; 
		}
		
	}
	
	return 0;
}

// ��֤�û� 
int verifyUser(void){
	char userPasswd[STRING_MAX], tmpUserPasswd[STRING_MAX];
	char userLoadFailedCount[2][STRING_MAX];
	int errorCount = 0, j=0;
	
	fflush(stdin); 
	
	readStrFromFile(USER_LOAD_PATH, userLoadFailedCount); 
	errorCount = atoi(userLoadFailedCount[0]);
	
	if(errorCount>(USER_PASSWD_FAILED_MAX_COUNT-1))
	{
		pSError("[!]�����������������ﵽ���Σ����ѱ����ᣬ�뵽��̨�ⶳ��");
		return 0;
	}
	
	again:
	printf("[~]���������룺");
	j = strlen(userInfoOnLine.userPasswd);
	strcpy(tmpUserPasswd, userInfoOnLine.userPasswd);
	tmpUserPasswd[j-1] = tmpUserPasswd[j]; 
	
	scanf("%s", userPasswd);
	
	if(strcmp(tmpUserPasswd, userPasswd)) // ������� 
	{
		errorCount++;
		if(errorCount>(USER_PASSWD_FAILED_MAX_COUNT-1))
		{
			pSError("[!]�����������������ﵽ���Σ����ѱ����ᣬ�뵽��̨�ⶳ��");
			itoa(errorCount, userPasswd, 10);
			writeStrFromFile(USER_LOAD_PATH, userPasswd);
			return 0;
		}else{
			if(errorCount>(USER_PASSWD_FAILED_MAX_COUNT-1))
			{
				pSError("[!]�����������������ﵽ���Σ����ѱ����ᣬ�뵽��̨�ⶳ��");
				itoa(errorCount, userPasswd, 10);
				writeStrFromFile(USER_LOAD_PATH, userPasswd);
				return 0;
			}else{
				pSError("[!]�������");
			}
			goto again;
		}
	}
	else{
		itoa(errorCount, userPasswd, 10);
		writeStrFromFile(USER_LOAD_PATH, userPasswd);
		return 1;
	} 
} 

// mode:1 ȡǮ   mode:2 ��Ǯ  mode:3 ת�� 
void itemFuncUpdate(byte mode){
	int money=0, quitFlag=0;
	char tmpStr[STRING_MAX*3], tmpStrMoney[STRING_MAX], otherAccount[STRING_MAX];

	fflush(stdin);
	if(mode==3){
		if(langFlag==1)
		{
			printf("�Է��˺ţ�");
		}else{
			printf("Account number of the opposite party:");
		}
		gets(otherAccount);
	} 

	if(langFlag==1)
	{
		printf("�����ֻ֧�ְ�Ԫ��[����:-1]��");
	}else{
		printf("Input amount (only a few hundred)[back:-1]:");
	}
	
	do
	{
		fflush(stdin);
		scanf("%d", &money);
		
		// �˳� 
		if(money==-1) {
			quitFlag = 1;
			break;
		}
		
		money = (money/100)*100;
		
		// ����  ȡ��ģʽ 
		if(mode==1)
		{
			if((money>userInfoOnLine.deposit)) {
				if(langFlag==1){
					pSError("[!]����");
				}else{
					pSError("[!]Your balance is not enough.");
				}
				goto cn_next;
			}
		}
		
		// ������Ϲ淶 
		if((money>0)&&(!(money>(mode==1?30000:50000)))) break;
		
		// ���벻���Ϲ淶 
		else{
			// ȡ��ģʽ 
			if(mode==1)
			{
				if(langFlag==1)
				{
					pSError("[!]���淶�������3��");	
				}else{
					pSError("[!]The amount is not standardized, or more than 30000");
				}
			}
			// ���ģʽ 
			else{
				if(langFlag==1)
				{
					pSError("[!]���淶�������5��");
				}else{
					pSError("[!]The amount is not standardized, or more than 50000");
				}
			}
		}
		
		cn_next:
		if(langFlag==1)
		{
			printf("�����ֻ֧�ְ�Ԫ����");
		}else{
			printf("Input amount (only a few hundred):");
		}
		
	}while(1);
	
	if(quitFlag==1){
		return;
	}
	
	// ȡ�� �� ת�� 
	if((mode==1)||(mode==3))
	{
		userInfoOnLine.deposit -= money;
	}
	// ��� 
	else if(mode==2){
		userInfoOnLine.deposit += money;
	}

	// �������� 
	strcat(tmpStr, userInfoOnLine.userName);
	strcat(tmpStr, userInfoOnLine.userPasswd);
	strcat(tmpStr, itoa(userInfoOnLine.deposit, tmpStrMoney, 10));
	
	// д��ɹ�	
	if(writeStrFromFile(USER_INFO_PATH, tmpStr)==1)
	{
		// ȡ�� 
		if(mode==1)
		{
			if(langFlag==1)
			{
				pSSuccess("[~]ȡ��ɹ�");
				printf("[~]��-%d\n", money);
			}else{
				pSSuccess("[~]Withdrawal successful");
				printf("[~]Amount of money��-%d\n", money);
			}	
		}
		// ��� 
		else if(mode==2){
			if(langFlag==1)
			{
				pSSuccess("[~]����ɹ�");
				printf("[~]��+%d\n", money);
			}else{
				pSSuccess("[~]Deposit succeeded");
				printf("[~]Amount of money��+%d\n", money);
			}
		}
		// ת�� 
		else if(mode==3){
			if(langFlag==1)
			{
				pSSuccess("[~]ת���ɹ�");
				printf("Ŀ���˻���%s\n", otherAccount);
				printf("[~]��-%d\n", money);
			}else{
				pSSuccess("[~]Transfer accounts succeeded");
				printf("[~]Amount of money��-%d\n", money);
			}
		}
		if(mode==3){
			accountDetails(mode, money, otherAccount);
		}else{
			accountDetails(mode, money, NULL);
		}
	}
	// д��ʧ�� 
	else
	{
		// ȡ�� 
		if(mode==1)
		{
			if(langFlag==1)
			{
				pSError("[~]ȡ��ʧ��");
			}else{
				pSSuccess("[~]Withdrawal Failed");
			}	
		}
		// ���
		else if(mode==2){
			if(langFlag==1)
			{
				pSSuccess("[~]���ʧ��");
			}else{
				pSError("[~]Deposit Failed");
			}
		}
		// ת�� 
		else if(mode==3){
			if(langFlag==1)
			{
				pSSuccess("[~]ת��ʧ��");
			}else{
				pSError("[~]Transfer accounts Failed");
			}
		}
	}
	
	if(langFlag==1){
		puts("\n[~]Enter���˳�");
	}else{
		puts("\n[~]Enter to exit");
	}
	wait();
} 

// ��¼������ˮ 
void accountDetails(byte mode, int money, char *otherAccount){
	char tmpStr[STRING_MAX*2], tmpMoney[STRING_MAX];
	char nowTime[32] = {0};
    
    getNowTime(nowTime);

    strcpy(tmpStr, "[");
	strcat(tmpStr, nowTime);
	strcat(tmpStr, "  ");
	if(mode==1){		
		strcat(tmpStr, "ȡ��]����");
	}else if(mode==2){
		strcat(tmpStr, "���]����");
	}else if(mode==3){
		strcat(tmpStr, "ת��]��");
		strcat(tmpStr, "�Է��˺ţ�");
		strcat(tmpStr, otherAccount);
		strcat(tmpStr, "  ��");
	}
	printf("%d\n", money);
	itoa(money, tmpMoney, 10);
	strcat(tmpStr, tmpMoney);
	strcat(tmpStr, "\n");
	
	addStrFromFile(SYS_LOG_PATH, tmpStr);	
}

// ��ѯ������ˮ 
void itemFuncDetails(void){
	char tmpLog[100][STRING_MAX];
	int i=0, n = readStrFromFile(SYS_LOG_PATH,tmpLog);
	if(langFlag==1)
	{
		pSInfo("[~]����100����ˮ:");
	}else{
		pSInfo("[~]Recent 100 account information:");
	}
	for(i=0;i<n;i++)
	{
		puts(tmpLog[i]);
	}
	
	if(langFlag==1){
		puts("\n[~]Enter���˳�");
	}else{
		puts("\n[~]Enter to exit");
	}
	wait();
}

// ��ȡ��ǰʱ�� 
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

// ��ѯ��� 
void itemFuncCheck(void){
	if(langFlag==1)
	{
		printf("���:%d", userInfoOnLine.deposit);
		puts("\n[~]Enter���˳�");
	}else
	{
		printf("Balance:��%d", userInfoOnLine.deposit);
		puts("\n[~]Enter to exit");
	}
	
	fflush(stdin);
	getchar();
}

// �ȴ� ������ 
void wait(void){
	fflush(stdin);
	getchar();
}

// �����û���Ϣ 
void loadUserInfo(char *filepath){
	char tmpUserInfo[3][STRING_MAX];
	readStrFromFile(filepath, tmpUserInfo);
	strcpy(userInfoOnLine.userName, tmpUserInfo[0]);
	strcpy(userInfoOnLine.userPasswd, tmpUserInfo[1]);
	userInfoOnLine.deposit = atoi(tmpUserInfo[2]);
//	printf("%s %s %d\n", userInfoOnLine.userName, userInfoOnLine.userPasswd, userInfoOnLine.deposit); 
}

// ��ʽ������Ϣ 
void userInputInfo(void){
	if(langFlag==1)
	{
		printf("\n[~]����:");
	}else
	{
		printf("\n[~]input:");
	}
}

// ��鿨���� 
void checkCard(void){
	char c;
	pSInfo("[~]�����ſ���������P/p�������ſ���");
	
	do{
		c = getchar();
		if((c=='P')||(c=='p'))
		{
			pSSuccess("[~]�ſ�����ɹ�");
			
			// �����û���Ϣ���û���������  |  �û������Ϣ�� 
			loadUserInfo(USER_INFO_PATH);
			pSInfo("[~]��ӭ�û���");
			printf("User: %s\n", userInfoOnLine.userName);
			
			break;
		}else
		{
			pSError("[!]�ſ�δ����");
		}
		fflush(stdin);
	}while(1);	
}

// ����˵� 
void loadMenuConfig(char *filepath){
	char tmpMainItemText[MAIN_TITLE_COUNT+1][STRING_MAX] = {"ATM�˵�","��ѯ","���","ȡ��","ת��","�˳�"};
	int i=0, j=0;
	int r = readStrFromFile(filepath, tmpMainItemText);
	
	j=strlen(tmpMainItemText[0]);
	tmpMainItemText[0][j-1] = tmpMainItemText[0][j];
	strcpy(mainTitle, tmpMainItemText[0]);
	
	for(i=0;i<MAIN_TITLE_COUNT;i++)
	{
		j=strlen(tmpMainItemText[i+1]);
		tmpMainItemText[i+1][j-1] = tmpMainItemText[i+1][j];
	
		strcpy(mainItemText[i], tmpMainItemText[i+1]);
	}
} 

// ��ʼ���� 
void initInterface(void){
	char itemText[2][50] = {"1.����","2.English"};
	initMenu("��ѡ������",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(12);
	showMenu();
	
	printf("\n[~]����:");
	
	if(getchar() == '2'){ // en : 2
		loadMenuConfig(LOCAL_LANG_EN);
		langFlag = 2;
	}else{ // cn : 1 and other
		loadMenuConfig(LOCAL_LANG_CN);
		langFlag = 1;
	}
	
	clearScreen();
} 

// ���˵� 
void mainInterface(void){
	initMenu(mainTitle, mainItemText, sizeof(mainItemText)/sizeof(mainItemText[0]));
	createMenu(13);
	showMenu();
} 
