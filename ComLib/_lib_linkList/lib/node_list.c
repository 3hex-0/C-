#include "node_list.h"
#include "string.h"
#include <stdlib.h>

// ����API

/*
	func	: ����һ���յ����� 
	para	: void
	return	: NODE *headNode,����һ��ͷ�ڵ��ַ 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
NODE *createNullList(void){
	int i=0;
	NODE *headNode=NULL;
	headNode = (NODE *)malloc(sizeof(NODE));
	
	headNode->next = NULL;
	
	return headNode;
}

/*
	func	: ����һ���µĽڵ� 
	para	: DATA tmpData, ֵ���� 
	return	: NODE *newNode������һ���½ڵ��ַ 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
NODE *createNewNode(DATA tmpData){
	int i=0;
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	
	newNode->next = NULL;
	
	newNode->data = tmpData;
	
	return newNode;
} 

/*
	func	: ����ڵ� / ͷ�巨  
	para	: Node* headNode,DATA tmpData  ͷ�ڵ㣬DATA�ṹ�� 
	return	: void
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
void insertNodeByHead(NODE *headNode, DATA tmpData){
	NODE *fpNode = headNode->next;
	NODE *newNode = createNewNode(tmpData);
	
	// ��һ�β��� �ڵ� 
	if(fpNode==NULL){
		headNode->next = newNode;
		return;
	}
	
	newNode->next = fpNode->next;
	fpNode->next = newNode;
	return;
}

/*
	func	: ����ڵ� / β�巨 
	para	: Node* headNode,DATA tmpData  ͷ�ڵ㣬DATA�ṹ�� 
	return	: void
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
void insertNodeByEnd(NODE *headNode, DATA tmpData){
	NODE *forNode = headNode;
	NODE *newNode = createNewNode(tmpData);
	
	while(forNode->next != NULL){
		forNode = forNode->next;
	}
	
	forNode->next = newNode;
	return;
}

/*
	func	: ����ڵ� ��ָ���ڵ�� (int��������) 
	para	: Node* headNode,int dataId, DATA tmpData  ͷ�ڵ㣬int������ID��DATA�ṹ�� 
	return	: void
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
void insertNodeByPosDataInt(NODE *headNode, int dataId, DATA tmpData){
	NODE *forNode = headNode;
	NODE *newNode = createNewNode(tmpData);
	
	while(!(forNode->data.num == dataId)){
		forNode = forNode->next;
	}
	
	newNode->next = forNode->next;
	forNode->next = newNode;
	return;
}

/*
	func	: ɾ���ڵ� / ͨ���±�  0Ϊ��һ���ڵ� 
	para	: Node* headNode,int posIndex  ͷ�ڵ㣬�±� 
	return	: int -1:��� -2���±���� 0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int delNodeByPosIndex(NODE *headNode, int posIndex){
	int indexCount=0;
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	if((posIndex-1)>listLength(headNode)) return -2;
	
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

/*
	func	: ɾ���ڵ� / ͨ��ָ������(int��������)  ��ֻɾ����һ�β�ѯ����  
	para	: Node* headNode,int dataId  ͷ�ڵ㣬int������ID 
	return	: int -1:��� 0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int delNodeByPosDataInt(NODE *headNode, int dataId){
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	tmpNode->next = forNode->next;
	free(forNode);
	
	return 0;
}

/*
	func	: ɾ���ڵ� / ͨ��ָ������ ��ɾ�����еĲ�ѯ������  
	para	: Node* headNode,int dataId  ͷ�ڵ㣬int������ID 
	return	: int -1:��� 0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int delNodeByPosDataIntRe(NODE *headNode, int dataId){
	int count=0; 
	NODE *forNode = headNode->next, *tmpNode=headNode;
	NODE *checkNode = forNode;
	if(listIsNull(headNode)) return -1;
	
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

/*
	func	: �������� / ͨ��ָ��������   
	para	: Node* headNode,int dataId,DATA tmpData  ͷ�ڵ㣬int������ID , DATA
	return	: int -1:��� 0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int updateNodeByPosDataInt(NODE *headNode, int dataId, DATA tmpData){
	NODE *forNode = headNode->next, *tmpNode = headNode;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	// update
	forNode->data = tmpData;
	
	return 0;
}

/*
	func	: �������� / ͨ��ָ�����±�  
	para	: Node* headNode,int posIndex,DATA tmpData  ͷ�ڵ㣬�±� , DATA
	return	: int -1:��� -2���±���� 0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int updataNodeByPosIndex(NODE *headNode, int posIndex, DATA tmpData){
	int indexCount=0;
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	if((posIndex-1)>listLength(headNode)) return -2;
	
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

/*
	func	: ��ѯ��ӡ�ڵ� / ͨ��ָ��������(int��������)   
	para	: Node* headNode,int dataId  ͷ�ڵ㣬int������ID 
	return	: int 1:�ɹ�  0��ʧ�� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int searchNodeByPosDataInt(NODE *headNode, int dataId){
	NODE *forNode = headNode->next;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId){
			// print data
			printFormatInfo(forNode);
			return 1; 
		}
		forNode = forNode->next;
	}
	
	printf("[!]δ��ѯ��������¼\n");
	return 0;
}

/*
	func	: ��ѯ��ӡ�ڵ� / ͨ��ָ�����±� 
	para	: Node* headNode,int posIndex  ͷ�ڵ㣬�±�
	return	: int 1:�ɹ�  0��ʧ�� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int searchNodeByPosIndex(NODE *headNode, int posIndex){
	int indexCount=0;
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(indexCount == posIndex) {
			// print data
			printFormatInfo(forNode);
			return 1;
		}
		indexCount++;
	}
	
	return 0;
}

/*
	func	: �ж�����Ϊ�� 
	para	: Node* headNode  ͷ�ڵ�
	return	: int 1:��  0����Ϊ�� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int listIsNull(NODE *headNode){
	NODE *forNode = headNode->next;
	
	if(forNode == NULL) return 1;
	else return 0;
}


/*
	func	: ͳ��������
	para	: Node* headNode  ͷ�ڵ�
	return	: int ���� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int listLength(NODE *headNode){
	int listLen=0; 
 	NODE *forNode = headNode->next;
	
	if(listIsNull(headNode)) return listLen;
	
	while(forNode != NULL){
		listLen++;
		forNode = forNode->next;
	}
	
	return listLen;
} 

/*
	func	: ��ӡ�ڵ����������
	para	: Node* headNode, int mode   ͷ�ڵ㣬mode:0 ��ӡȫ�� mode:1 ��ӡǰ20 
	return	: int -1:���  0���ɹ�  
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int printList(NODE *headNode, int mode){
	NODE *forNode = headNode->next;
	int count=0;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		count++; 
		// print data
		printFormatInfo(forNode);
		
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
 
/*
	func	: �̻� ���ݵ�hex�ļ�(bin) 
	para	: NODE *headNode, char *filePath   ͷ�ڵ㣬�ļ�·�� 
	return	: int -1:���  0���ɹ� -2:�ļ���ʧ�� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/
int saveListToHexFile(NODE *headNode, char *filePath){
	NODE *forNode = headNode->next;
	FILE *fp = NULL;
	
	if(listIsNull(headNode)) return -1;
	
	fp = openFile(filePath, "wb", 1);
	if(fp==NULL) return -2;
	
	while(forNode != NULL){
		fwrite(&forNode->data, sizeof(DATA), 1, fp);
		fflush(fp); // �ͷ��ļ����뻺��   ��֤�ṹ��ĸ�ʽ���� ��ȷ 
		forNode = forNode->next;
	}
	
	return 0;
} 

/*
	func	: ���ļ���bin)������ ���� ��������
	para	: NODE *headNode, char *filePath   ͷ�ڵ㣬�ļ�·�� 
	return	: int -1:���  0���ɹ� -2:�ļ���ʧ�� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/ 
int loadListFromHexFile(NODE *headNode, char *filePath){
	NODE *forNode = headNode->next, *tmpNode=NULL;
	FILE *fp = NULL;
	DATA tmpData;
	
	fp = openFile(filePath, "rb", 0);
	if(fp==NULL) return -2;
	
	do{
		fread(&tmpData, sizeof(DATA), 1, fp);
		insertNodeByEnd(headNode, tmpData);
		if(feof(fp)) break;
	}while(1);
	
	// �����һ���ڵ� �ͷŵ�
	tmpNode = returnFrontEndNode(headNode);
	free(tmpNode->next); 
	tmpNode->next = NULL;
	
	return 0;
}
 
/*
	func	: ���� ���һ���ڵ� ��ǰһ���ڵ�
	para	: NODE *headNode   ͷ�ڵ�
	return	: NODE *forNode , ���һ���ڵ��ǰһ���ڵ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ����
			 ͨ��forNode->next���ɵõ�β�ڵ�  
*/ 
NODE *returnFrontEndNode(NODE *headNode){
	NODE *forNode = headNode; 
	
	if(listIsNull(headNode)) return NULL;
	
	while(forNode->next->next != NULL){
		forNode = forNode->next;
	}
	
	return forNode;
}

/*
	func	: �ͷ����� 
	para	: NODE *headNode   ͷ�ڵ�
	return	: int -1:���  0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/ 
int freeList(NODE *headNode){
	NODE *forNode = NULL;
	
	if(listIsNull(headNode)) return -1;
	
	do{
		forNode = returnFrontEndNode(headNode);
		if(forNode == NULL) break;
		forNode->next = NULL;
		free(forNode);
	}while(1);
	
	return 0;
}

/*
	func	: ���������㷨����ѡ��
	para	: NODE *headNode   ͷ�ڵ�
	return	: int -1:���  0���ɹ� 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���� 
*/ 
int listSortFunc(NODE *headNode){
	NODE *endP = returnFrontEndNode(headNode)->next;
	NODE *moveP = headNode->next, *baseP=headNode->next, *standP=headNode;
	DATA tmpData;
	
	if(listIsNull(headNode)) return -1; 
	
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


/*
	func	: ��ӡ��ʽ������ 
	para	: NODE *headNode   ͷ�ڵ�
	return	: void 
	more	:�Ƿ�����DATA�ṹ���ڲ��������� ���̡̡�
*/ 
void printFormatInfo(NODE *forNode){
	printf(PF_DATA, DATA_FROMATE);
} 



