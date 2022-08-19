#include <stdio.h>
#include <stdlib.h>
#include "gui_menu_tool.h"  // �˵�API 
#include "richtext.h"       // ���ı�API 
#include "filehandler.h"	// �ļ�����API 
#include "gen_def.h"		// ͨ�ú궨��API 
#include "main.h"			
#include "nodelist.h"		// �������API 
#include "passwd.h"			// �����½API 

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
		
		printf("��һ��ʹ�ã����������룺");
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
	
	// ��֤���� 
	loadPWStr();
	if(checkPWStr()==-1){
		wait();
		return 0;
	}
	wait();
	
	// �˵���ʼ�� 
	begin:
	mainMenu();
	
	// ������ģ�� 
	do{
		printf("\n������:");
		
		userInput = getchar();
		fflush(stdin);
		if(((userInput-'0')>=0)&&((userInput-'0')<=9)) {
			break;
		}
		else{
			mainMenu();
		}
	}while(1);
	
	
	// ����ѡ��ģ��
	switch(userInput){
		case '0': // �˳�
			exitFlag = 0; 
			break;
		case '1': // ¼����Ϣ 
			funcInputInfo();
			exitFlag = 1; 
			break;
		case '2': // ��ѯ�ɼ� 
			funcSearchInfo();
			exitFlag = 2; 
			break;
		case '3': // ɾ���ɼ� 
			funcDelStdInfo();
			exitFlag = 3; 
			break;
		case '4': // �޸ĳɼ� 
			funcUpdateStdInfo();
			exitFlag = 4; 
			break;
		case '5': // ����ɼ� 
			funcInsertStdInfo();
			exitFlag = 5;
			break;
		case '6': // ���� 
			funcSortList();
			exitFlag = 6;
			break;
		case '7': // ͳ������ 
			funcCountStdNum();
			exitFlag = 7;
			break;
		case '8': // ��ӡǰ 20����Ϣ 
			funcPrintListNew();
			exitFlag = 8;
			break;
		case '9': // 
			randTenInfo();
			exitFlag = 9;
			break;
		default:
			exitFlag = -1; // �����쳣 
			break;
	}
	
	// �쳣�˳�����ģ��
	if(exitFlag<0){ // �쳣�˳� 
	pSError("[~]ϵͳ���������˳�ϵͳ");
		exit(exitFlag);
	}else if(exitFlag==0){
		//...
		pSSuccess("[~]ϵͳ�����˳�");
		exit(exitFlag);
	}else{
		//...
		wait();
		goto begin;
	}
	
	return 0;
}

void randTenInfo(void){
	int i=0;
	DATA tmpData;
	
	for(i=0;i<10;i++){
		tmpData = randStdInfo(i);
		insertNodeByEnd(nodeHead, tmpData);
	}
	pSSuccess("[~]�������10����¼�ɹ�");
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]�������ݳɹ�");
	}else{
		pSError("[~]��������ʧ��"); 
	}
}

// ϵͳ���� ��ʼ�� 
void systemInit(void){
	srand(time(NULL));
	
	// ��ʼ��ͷ�ڵ� 
	nodeHead = createNullList();
	
	// ���� �ļ��е�����
	loadInfoFromDataFile();
//	if(loadInfoFromDataFile()){
//		pSSuccess("[~]����ɹ�");
//	}else{
//		pSError("[~]����ʧ��"); 
//	} 
	
} 

int checkFirstUser(void){
	FILE *fp = openFile(USER_FIRST_USE_PATH, "rb", 0);
	if(fp==NULL){ // ��һ��ʹ��ϵͳ 
		openFile(USER_FIRST_USE_PATH, "wb", 0); 
		return 1;
	}else{     // ���ǵ�һ��ʹ��ϵͳ 
		return 0;
	}
} 

void funcSortList(void){
	listSortFunc(nodeHead);
	pSSuccess("[~]�������(��ѧ������)");
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]�������ݳɹ�");
	}else{
		pSError("[~]��������ʧ��"); 
	}
}

void funcInsertStdInfo(void){
	int insertInfoCount=0, i=0, flag=0;
	int inputDataId=0;
	char tmpChar; 
	DATA tmpData;
	
	// �û�����ģ��
	do{
		mainMenu();
		printf("\n������ѧ�ţ����룩:\n");
		scanf("%d", &inputDataId);
		fflush(stdin); 
		
		flag = searchNodeByPosData(nodeHead, inputDataId);
		
		// ѧ�� 
		printf("\n[~]������ѧ��:");
		scanf("%d", &tmpData.num);
		fflush(stdin); 
		
		// ���� 
		printf("\n[~]����������:");
		scanf("%s", tmpData.name);
		fflush(stdin); 
		
		// ���� 
		printf("\n[~]����������:");
		scanf("%d", &tmpData.age);
		fflush(stdin); 
		
		// �Ա� 
		printf("\n[~]�������Ա�:");
		scanf("%c", &tmpData.sex);
		fflush(stdin); 
		
		// �ֻ�
		printf("\n[~]�������ֻ�:");
		scanf("%s", tmpData.mobile);
		fflush(stdin); 
		
		// qq�� 
		printf("\n[~]������qq��:");
		fflush(stdin); 
		scanf("%s", tmpData.qq);
		
		// רҵ 
		printf("\n[~]������רҵ:");
		scanf("%s", tmpData.direction);
		fflush(stdin); 
		
		if(flag==1){
			insertNodeByPosData(nodeHead, inputDataId, tmpData);
		} else{
			insertNodeByEnd(nodeHead, tmpData); 
		}
		
		insertInfoCount++;
		
		printf("�ü�¼������ɣ��Ƿ��������? y/n��\n");
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ���� 
			pSInfo("[~]��������"); 
			printf("��������%3d����¼\n", insertInfoCount);
			break;
		}
	} while(1);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]�������ݳɹ�");
	}else{
		pSError("[~]��������ʧ��"); 
	}
}

void funcUpdateStdInfo(void){
	int updateInfoCount=0, i=0;
	int inputDataId=0;
	char tmpChar; 
	DATA tmpData;
	
	// �û�����ģ��
	do{
		mainMenu();
		printf("\n������ѧ�ţ����£�:\n");
		scanf("%d", &inputDataId);
		
		if(searchNodeByPosData(nodeHead, inputDataId)==1){
		// ѧ�� 
		printf("\n[~]������ѧ��:");
		scanf("%d", &tmpData.num);
		fflush(stdin); 
		
		// ���� 
		printf("\n[~]����������:");
		scanf("%s", tmpData.name);
		fflush(stdin); 
		
		// ���� 
		printf("\n[~]����������:");
		scanf("%d", &tmpData.age);
		fflush(stdin); 
		
		// �Ա� 
		printf("\n[~]�������Ա�:");
		scanf("%c", &tmpData.sex);
		fflush(stdin); 
		
		// �ֻ�
		printf("\n[~]�������ֻ�:");
		scanf("%s", tmpData.mobile);
		fflush(stdin); 
		
		// qq�� 
		printf("\n[~]������qq��:");
		scanf("%s", tmpData.qq);
		fflush(stdin); 
		
		// רҵ 
		printf("\n[~]������רҵ:");
		scanf("%s", tmpData.direction);
		fflush(stdin); 
			
			// ���� ���뵽������ 
			updateNodeByPosData(nodeHead, inputDataId, tmpData); 
			updateInfoCount++;	
		}
		
		printf("�ü�¼�޸���ɣ��Ƿ�����޸�? y/n��\n");
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ���� 
			pSInfo("[~]�����޸�"); 
			printf("��������%3d����¼\n", updateInfoCount);
			break;
		}
	} while(1);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]�������ݳɹ�");
	}else{
		pSError("[~]��������ʧ��"); 
	}
}

void funcPrintListNew(void){
	pSInfo("[~]���20����¼��");
	printList(nodeHead, 0);
}

void funcDelStdInfo(void){
	int inputDataId=0;
	char tmpChar; 
	
	// �û�����ģ��
	do{
		mainMenu();
		fflush(stdin);
		
		// ѧ�� 
		printf("\n[~]������ѧ�ţ�ɾ����:");
		scanf("%d", &inputDataId);
		delNodeByPosDataRe(nodeHead, inputDataId); // �ݹ�ɾ��
		
		printf("\n�Ƿ����ɾ��? y/n��\n");
		
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ���� 
			pSInfo("[~]�������˵�"); 
			break;
		}
	} while(1);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]�������ݳɹ�");
	}else{
		pSError("[~]��������ʧ��"); 
	}
}

void funcCountStdNum(void){
	printf("[~]�ð༶�й��� [%d] ��\n", listLength(nodeHead));
} 

void funcSearchInfo(void){
	int inputDataId=0;
	char tmpChar; 
	
	// �û�����ģ��
	do{
		mainMenu();
		fflush(stdin);
		
		// ѧ�� 
		printf("\n[~]������ѧ�ţ���ѯ��:");
		scanf("%d", &inputDataId);
		fflush(stdin); 
		
		searchNodeByPosData(nodeHead, inputDataId); 
		
		printf("\n�Ƿ������ѯ? y/n��\n");
		
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // ��y/Y ���� 
			pSInfo("[~]�������˵�"); 
			break;
		}
	} while(1);
	
}

void funcInputInfo(void){
	int i=0, nowUserTimer=0, newNodeCount=0;
	char tmpChar;
	DATA tmpData;
	
	// �û�����ģ��
	do{
		mainMenu();
		nowUserTimer++;
		printf("\n��ǰ����¼���%3d��ѧ����Ϣ\n", nowUserTimer);
		
		// ѧ�� 
		printf("\n[~]������ѧ��:");
		scanf("%d", &tmpData.num);
		fflush(stdin); 
		
		// ���� 
		printf("\n[~]����������:");
		scanf("%s", tmpData.name);
		fflush(stdin); 
		
		// ���� 
		printf("\n[~]����������:");
		scanf("%d", &tmpData.age);
		fflush(stdin); 
		
		// �Ա� 
		printf("\n[~]�������Ա�:");
		scanf("%c", &tmpData.sex);
		fflush(stdin); 
		
		// �ֻ�
		printf("\n[~]�������ֻ�:");
		scanf("%s", tmpData.mobile);
		fflush(stdin); 
		
		// qq�� 
		printf("\n[~]������qq��:");
		scanf("%s", tmpData.qq);
		fflush(stdin); 
		
		// רҵ 
		printf("\n[~]������רҵ:");
		scanf("%s", tmpData.direction);
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
	
//	printList(nodeHead);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]�������ݳɹ�");
	}else{
		pSError("[~]��������ʧ��"); 
	}
}

// ���ļ��� �������� 
int loadInfoFromDataFile(){
	return !loadListFromHexFile(nodeHead, DATA_FILE_PATH);
}

// ���� ���浽�ļ��� 
int saveInfoToDataFile(){
	return !saveListToHexFile(nodeHead, DATA_FILE_PATH);
}

// ���˵� 
void mainMenu(){
	char itemText[10][50] = {"0.�˳�"
							,"1.¼��ɼ�"
							,"2.��ѯ�ɼ�"
							,"3.ɾ���ɼ�"
							,"4.�޸ĳɼ�"
							,"5.����ɼ�"
							,"6.����"
							,"7.ͳ��ѧ������"
							,"d-8.��20����¼"
							,"d-9.���10����¼"};
	clearScreen();
	
	initMenu("ѧ������ϵͳ",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(17);
	showMenu(); 
	printf("\n\n[info]d-8,d-9Ϊ���Թ��ܣ�ʵ���޴˹���");
}
