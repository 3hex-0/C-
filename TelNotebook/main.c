#include <stdio.h>
#include <stdlib.h>
#include "gui_menu_tool.h"  // �˵�API 
#include "richtext.h"       // ���ı�API 
#include "file_handler.h"	// �ļ�����API 
#include "gen_def.h"		// ͨ�ú궨��API 
#include "main.h"
#include "node_list.h"		// �������API 
#include "passwd.h"			// �����½API 
#include "rand_data.h"      
#include "inputcheck.h"     


#define S_N 5
int exitFlag=0; // >0:�����˳�  ==0:�����˳�  <0:�쳣�˳�
NODE *nodeHead = NULL;

int main() {
	char userInput;
	char tmpPW[100];

	// ��һ��ʹ��ϵͳ
	if(checkFirstUser()==1) {
		pSInfo("[~]��һ��ʹ��ϵͳ��ϵͳ�Լ�������...");
		// check...
		Sleep(1000);

		pSInfo("[~]���ڽ��б�Ҫ���ã������ĵȴ�...");
		// config...
		Sleep(500);

		pSInfo("[~]�����������...");
		// finally config...
		Sleep(500);

		printf("[~]��һ��ʹ�ã����������룺");
		// set load passwd
		gets(tmpPW); 
		updatePWData(tmpPW, 0);
		pSSuccess("[~]��½�������óɹ�");
		

		Sleep(500);
		pSSuccess("[~]�������");
		wait();
	}

	// ϵͳ��ʼ
	systemInit();
	
	loadPWStr();
	// ��֤����
	if(checkPWStr()==-1) {
		wait();
		return 0;
	}
	wait();

	// �˵���ʼ��
begin:
	mainMenu();

	// ������ģ��
	do {
		printf("\n������:");

		userInput = getchar();
		fflush(stdin);
		if(((userInput-'0')>=1)&&((userInput-'0')<=8)) {
			break;
		} else {
			mainMenu();
		}
	} while(1);


	// ����ѡ��ģ��
	switch(userInput) {
		case '1': // ¼��
			funcInputInfo();
			exitFlag = 1;
			break;
		case '2': // ɾ��
			funcDelStdInfo();
			exitFlag = 2;
			break;
		case '3': // ��ӡ
			funcPrintListNew();
			exitFlag = 3;
			break;
		case '4': // ��ѯ
			funcSearchInfo();
			exitFlag = 4;
			break;
		case '5': // ����
			if(saveInfoToDataFile()) {
				pSSuccess("[~]�������ݳɹ�");
			} else {
				pSError("[~]��������ʧ��");
			}
			exitFlag = 5;
			break;
		case '6': // ����
			if(loadInfoFromDataFile()) {
				pSSuccess("[~]����ɹ�");
			} else {
				pSError("[~]����ʧ��");
			}
			exitFlag = 6;
			break;
		case '7': // �˳�
			exitFlag = 0;
			break;
		case '8': //
			randTenInfo();
			exitFlag = 8;
			break;
		default:
			exitFlag = -1; // �����쳣
			break;
	}

	// �쳣�˳�����ģ��
	if(exitFlag<0) { // �쳣�˳�
		pSError("[~]ϵͳ���������˳�ϵͳ");
		exit(exitFlag);
	} else if(exitFlag==0) {
		//...
		pSSuccess("[~]ϵͳ�����˳�");
		exit(exitFlag);
	} else {
		//...
		wait();
		goto begin;
	}

	return 0;
}

void randTenInfo(void) {
	int i=0;
	DATA tmpData;

	for(i=0; i<10; i++) {
		tmpData = randNodeData();
		insertNodeByEnd(nodeHead, tmpData);
	}
	pSSuccess("[~]�������10����¼�ɹ�");

}

// ϵͳ���� ��ʼ��
void systemInit(void) {
	srand(time(NULL));

	// ��ʼ��ͷ�ڵ�
	nodeHead = createNullList();

	// ���� �ļ��е�����
	loadInfoFromDataFile();

}

int checkFirstUser(void) {
	FILE *fp = openFile(USER_FIRST_USE_PATH, "rb", 0);
	if(fp==NULL) { // ��һ��ʹ��ϵͳ
		fp = openFile(USER_FIRST_USE_PATH, "wb", 0);
		return 1;
	} else {    // ���ǵ�һ��ʹ��ϵͳ
		return 0;
	}
}

void funcPrintListNew(void) {
	pSInfo("[~]���м�¼��");
	printList(nodeHead, 0);
}

void funcDelStdInfo(void) {
	char inputDataId[100];
	char tmpChar;

	// �û�����ģ��
	do {
		mainMenu();
		fflush(stdin);

		// ѧ��
		printf("\n[~]������������ɾ����:");
		gets(inputDataId);
		delNodeByPosDataStrRe(nodeHead, inputDataId); // ɾ��

		printf("\n�Ƿ����ɾ��? y/n��\n");

		fflush(stdin);
		tmpChar = getchar();

		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ����
			pSInfo("[~]�������˵�");
			break;
		}
	} while(1);

}


void funcSearchInfo(void) {
	char inputDataId[100];
	char tmpChar;

	// �û�����ģ��
	do {
		mainMenu();
		fflush(stdin);

		// ѧ��
		printf("\n[~]��������������ѯ��:");
		gets(inputDataId);
		fflush(stdin);

		searchNodeByPosDataStr(nodeHead, inputDataId);

		printf("\n�Ƿ������ѯ? y/n��\n");

		fflush(stdin);
		tmpChar = getchar();

		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ����
			pSInfo("[~]�������˵�");
			break;
		}
	} while(1);

}

void funcInputInfo(void) {
	int i=0, nowUserTimer=0, newNodeCount=0;
	char tmpChar;
	DATA tmpData;

	// �û�����ģ��
	do {
		mainMenu();
		nowUserTimer++;
		printf("\n��ǰ����¼���%3d����Ϣ\n", nowUserTimer);

		// 
		printf("\n[~]����������:");
		scanf("%s", tmpData.name);
		fflush(stdin);

		// 
		printf("\n[~]���������:");
		scanf("%s", tmpData.city);
		fflush(stdin);

		// 
		printf("\n[~]������ʡ:");
		scanf("%s", tmpData.province);
		fflush(stdin);

		// 
		printf("\n[~]���������:");
		scanf("%s", tmpData.state);
		fflush(stdin);

		// 
		printf("\n[~]������绰:");
		scanf("%s", tmpData.tel);
		fflush(stdin);

		// ���� ���뵽������
		insertNodeByEnd(nodeHead, tmpData);
		newNodeCount++;

		printf("�ü�¼¼����ɣ��Ƿ����¼��? y/n��\n");
		fflush(stdin);
		tmpChar = getchar();
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ����
			pSInfo("[~]����¼��");
			printf("����%3d����¼\n", newNodeCount);
			break;
		}
	} while(1);
}

// ���ļ��� ��������
int loadInfoFromDataFile() {
	freeList(nodeHead);
	return !loadListFromHexFile(nodeHead, DATA_FILE_PATH);
}

// ���� ���浽�ļ���
int saveInfoToDataFile() {
	return !saveListToHexFile(nodeHead, DATA_FILE_PATH);
}

// ���˵�
void mainMenu() {
	char itemText[8][50] = {"1.ͨ��¼¼��"
	                        ,"2.ͨ��¼ɾ��"
	                        ,"3.ͨ��¼��ʾ"
	                        ,"4.ͨ��¼���ݲ�ѯ"
	                        ,"5.ͨ��¼���ݱ���"
	                        ,"6.ͨ��¼���ݼ���"
	                        ,"7.�˳�ϵͳ"
	                        ,"d-8.���10����¼"
	                       };
	clearScreen();

	initMenu("<ͨ ���� ��¼>",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(33);
	showMenu();
	printf("\n\n[info]d-8Ϊ���Թ��ܣ�ʵ���޴˹���");
}
