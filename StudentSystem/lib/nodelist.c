#include "nodelist.h"
#include "string.h"
#include <stdlib.h>

// ����API

// ���һ����Ϣ 
DATA randStdInfo(int flag)
{
	//ѧ��//����//�Ա�//����//�ֻ�//qq��//רҵ
	char tmpStr[100];
	DATA *tmpData = (DATA *)malloc(sizeof(DATA));

	tmpData->num = 1000 + flag;  // ѧ�� 
	
	tmpStr[0] = flag+'A', tmpStr[1] = '\0';
	strcat(tmpStr, "Name");
	strcpy(tmpData->name, tmpStr); // ���� 
	
	tmpStr[0] = (rand()%2?'M':'W');
	tmpData->sex = tmpStr[0]; // �Ա�
	
	tmpData->age = rand()%11+20; // ���� 20-30
	
	strcpy(tmpData->mobile, "180 0000 000"); // �ֻ�
	
	strcpy(tmpData->qq, "777 000"); // qq��
	
	strcpy(tmpData->direction, "ZY"); // רҵ
	
	return *tmpData;
}

// ����һ���յ����� 
NODE *createNullList(){
	int i=0;
	NODE *nodeHead=NULL;
	nodeHead = (NODE *)malloc(sizeof(NODE));
	
	nodeHead->next = NULL;
	
	return nodeHead;
}

//  ����һ���µĽڵ�
NODE *createNewNode(DATA tmpData){
	int i=0;
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	
	newNode->next = NULL;
	
	newNode->data = tmpData;
	
	return newNode;
} 

// ����ڵ� / ͷ�巨 
void insertNodeByHead(NODE *nodeHead, DATA tmpData){
	NODE *fpNode = nodeHead->next;
	NODE *newNode = createNewNode(tmpData);
	
	// ��һ�β��� �ڵ� 
	if(fpNode==NULL){
		nodeHead->next = newNode;
		return;
	}
	
	newNode->next = fpNode->next;
	fpNode->next = newNode;
	return;
}

// ����ڵ� / β�巨 
void insertNodeByEnd(NODE *nodeHead, DATA tmpData){
	NODE *forNode = nodeHead;
	NODE *newNode = createNewNode(tmpData);
	
	while(forNode->next != NULL){
		forNode = forNode->next;
	}
	
	forNode->next = newNode;
	return;
}

void insertNodeByPosData(NODE *nodeHead, int dataId, DATA tmpData){
	NODE *forNode = nodeHead;
	NODE *newNode = createNewNode(tmpData);
	
	while(!(forNode->data.num == dataId)){
		forNode = forNode->next;
	}
	
	newNode->next = forNode->next;
	forNode->next = newNode;
	return;
}

// ɾ���ڵ� / ͨ���±�  0 Ϊ��һ���ڵ� 
int delNodeByPosIndex(NODE *nodeHead, int posIndex){
	int indexCount=0;
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	if((posIndex-1)>listLength(nodeHead)) return -2;
	
	while(forNode != NULL){
		if(indexCount == posIndex) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
		indexCount++;
	}
	
	tmpNode->next = forNode->next;
	free(forNode);
	
	return 0;
} 

// ɾ���ڵ� / ͨ��ָ������ ��ֻɾ����һ�β�ѯ���� 
int delNodeByPosData(NODE *nodeHead, int dataId){
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	tmpNode->next = forNode->next;
	free(forNode);
	
	return 0;
}

// ɾ���ڵ� / ͨ��ָ������ ��ɾ�����еĲ�ѯ������ 
int delNodeByPosDataRe(NODE *nodeHead, int dataId){
	int count=0; 
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	NODE *checkNode = forNode;
	if(listIsNull(nodeHead)) return -1;
	
	while(1){
//		printf("%s|%s\n", dataId, forNode->data.studentInfo.id);
		if(forNode->data.num == dataId)
		{
			tmpNode->next = forNode->next;
			free(forNode);
			count++;
			forNode = tmpNode->next;
			checkNode = forNode;
		}else{
			forNode = forNode->next;
			checkNode = checkNode->next;
			tmpNode = tmpNode->next;
		}
		
		if(checkNode == NULL) break;	
	}
	if(count==0){
		printf("[~]û�иü�¼\n");
	}else{
		printf("[~]�ɹ�ɾ��[%d]����¼\n", count);
	}
	return count;
}

// �������� / ͨ��ָ�������� 
int updateNodeByPosData(NODE *nodeHead, int dataId, DATA tmpData){
	NODE *forNode = nodeHead->next, *tmpNode = nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	// update
	forNode->data = tmpData;
	
	return 0;
}

// �������� / ͨ��ָ�����±� 
int updataNodeByPosIndex(NODE *nodeHead, int posIndex, DATA tmpData){
	int indexCount=0;
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	if((posIndex-1)>listLength(nodeHead)) return -2;
	
	while(forNode != NULL){
		if(indexCount == posIndex) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
		indexCount++;
	}
	
	// update
	forNode->data = tmpData;
	
	return 0;
}

// ��ѯ��ӡ�ڵ� / ͨ��ָ�������� 
int searchNodeByPosData(NODE *nodeHead, int dataId){
	NODE *forNode = nodeHead->next;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
//		printf("%p\n", forNode);
		if(forNode->data.num == dataId){
			// print data
			printf("%d|%s|%c|%d|%s|%s|%s",
					forNode->data.num,
					forNode->data.name,
					forNode->data.sex,
					forNode->data.age,
					forNode->data.mobile,
					forNode->data.qq,
					forNode->data.direction);
			return 1; 
		}
		forNode = forNode->next;
	}
	
	printf("[!]δ��ѯ��������¼\n");
	return 0;
}

// ��ѯ��ӡ�ڵ� / ͨ��ָ�����±� 
int searchNodeByPosIndex(NODE *nodeHead, int posIndex){
	int indexCount=0;
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		if(indexCount == posIndex) {
			// print data
			printf("%d|%s|%c|%d|%s|%s|%s",
					forNode->data.num,
					forNode->data.name,
					forNode->data.sex,
					forNode->data.age,
					forNode->data.mobile,
					forNode->data.qq,
					forNode->data.direction);
			break;
		}
		indexCount++;
	}
	
	return 0;
}

// �ж� ����Ϊ�� 
int listIsNull(NODE *nodeHead){
	NODE *forNode = nodeHead->next;
	
	if(forNode == NULL) return 1;
	else return 0;
}

// ͳ�������� 
int listLength(NODE *nodeHead){
	int listLen=0; 
 	NODE *forNode = nodeHead->next;
	
	if(listIsNull(nodeHead)) return listLen;
	
	while(forNode != NULL){
		listLen++;
		forNode = forNode->next;
	}
	
	return listLen;
} 

// ��ӡ�ڵ���������� 
// mode:0 ��ӡȫ�� mode:1 ��ӡǰ20 
int printList(NODE *nodeHead, int mode){
	NODE *forNode = nodeHead->next;
	int count=0;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		count++; 
		// print data
		printf("%d|%s|%c|%d|%s|%s|%s",
					forNode->data.num,
					forNode->data.name,
					forNode->data.sex,
					forNode->data.age,
					forNode->data.mobile,
					forNode->data.qq,
					forNode->data.direction);
		puts("");
		if(mode==1){
			if(count>20){
				break;
			}
		}
		forNode = forNode->next; 
	}
	
	return 0;
}

// �̻� ���ݵ�hex�ļ� 
int saveListToHexFile(NODE *nodeHead, char *filePath){
	NODE *forNode = nodeHead->next;
	FILE *fp = NULL;
	
	if(listIsNull(nodeHead)) return -1;
	
	fp = openFile(filePath, "wb", 1);
	if(fp==NULL) return -2;
	
	while(forNode != NULL){
		fwrite(&forNode->data, sizeof(DATA), 1, fp);
		fflush(fp); // �ͷ��ļ����뻺��   ��֤�ṹ��ĸ�ʽ���� ��ȷ 
		forNode = forNode->next;
	}
	
	return 0;
} 


// ���ļ������� ���� �������� 
int loadListFromHexFile(NODE *nodeHead, char *filePath){
	NODE *forNode = nodeHead->next, *tmpNode=NULL;
	FILE *fp = NULL;
	DATA tmpData;
	
	fp = openFile(filePath, "rb", 0);
	if(fp==NULL) return -2;
	
	do{
		fread(&tmpData, sizeof(DATA), 1, fp);
		insertNodeByEnd(nodeHead, tmpData);
		if(feof(fp)) break;
	}while(1);
	
	// �����һ���ڵ� �ͷŵ�
	tmpNode = returnFrontEndNode(nodeHead);
	free(tmpNode->next); 
	tmpNode->next = NULL;
	
	return 0;
}

// ���� ���һ���ڵ� ��ǰһ���ڵ� 
NODE *returnFrontEndNode(NODE *nodeHead){
	NODE *forNode = nodeHead; 
	
	if(listIsNull(nodeHead)) return NULL;
	
	while(forNode->next->next != NULL){
		forNode = forNode->next;
	}
	
	return forNode;
}

// �ͷ����� 
int freeList(NODE *nodeHead){
	NODE *forNode = NULL;
	
	if(listIsNull(nodeHead)) return -1;
	
	do{
		forNode = returnFrontEndNode(nodeHead);
		if(forNode == NULL) break;
		forNode->next = NULL;
		free(forNode);
	}while(1);
	
	return 0;
}

// ���������㷨����ѡ�� 
int listSortFunc(NODE *nodeHead){
	NODE *endP = returnFrontEndNode(nodeHead)->next;
	NODE *moveP = nodeHead->next, *baseP=nodeHead->next, *standP=nodeHead;
	DATA tmpData;
	
	if(listIsNull(nodeHead)) return -1; 
	
	while(baseP!=endP){
	
		moveP = baseP;
		
		standP = moveP;
		moveP = moveP->next;
		
		while(1){
			
			if(standP->data.num>moveP->data.num){
				tmpData = standP->data;
				standP->data = moveP->data;
				moveP->data = tmpData;
			}
			
			moveP = moveP->next;
			if(moveP==NULL) break;
		}
		
		baseP = baseP->next; 
	}
	return 0;
}




