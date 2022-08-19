#include "passwd.h"

char passwordStr[2][LINE_TEXT_MAX]={"\0", "\0"}; // 0: password 1: ����Ĵ������ 

// ���������ļ� 
void loadPWStr(void){
	
	readStrFromFile(PW_FIILE_PATH, passwordStr);
//	puts(passwordStr[0]);
//	puts(passwordStr[1]);
	
}

// ��֤���� 
int checkPWStr(void){
	char tmpPassword[LINE_TEXT_MAX] = {'\0'};
	int inputError = 0, len=0;
	
	if(!strcmp(passwordStr[1], "3")){ // ����ﵽ3�� 
		pSError("[!]���������������ﵽ���Σ��޷�������֤������ϰ����Ա");
		return -1; 
	}
	
	len = strlen(passwordStr[0]);
	passwordStr[0][len-1] = passwordStr[0][len];
	inputError = passwordStr[1][0]-'0'; // �������������� 
	
	PW_BEGIN_GOTO:
	
	fflush(stdin);
	printf("���������룺");
	gets(tmpPassword);
	
	if(!strcmp(passwordStr[0], tmpPassword)){ // ������ȷ 
		pSSuccess("[~]������ȷ����֤ͨ��");
		
		// �̻���Ϣ
		updatePWData(passwordStr[0], inputError);
		
		return 0;
	}else{ // ������� 
		inputError ++;
		if(inputError==3){
			pSError("[!]���������������ﵽ���Σ��޷�������֤������ϰ����Ա");
			
			updatePWData(passwordStr[0], inputError);
			
			return -1; 
		}else{
			goto PW_BEGIN_GOTO;
		}
	}
}

// ����������Ϣ
void updatePWData(char *passwd, int errorCount){
	char base[10] = {errorCount+'0', '\0'};
	
	strcat(passwd, "\n");
	strcat(passwd, base);
	writeStrToFile(PW_FIILE_PATH, passwd);
	
}



