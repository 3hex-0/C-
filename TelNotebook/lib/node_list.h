#ifndef _NODE_LIST_H_
#define _NODE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "file_handler.h"
 
// ���ݽṹ�� 
typedef struct _data{
	// �û��Զ��� 
	char name[15];		/*����*/
	char city[10];		/*����*/
	char province[10];	/*ʡ*/
	char state[10];		/*����*/
	char tel[15];		/*�绰*/
}DATA;

#define PF_TITLE "Name", "City", "Province", "State", "Tel"
#define PF_DEV "\t----------------------------------------------------------------"
#define DATA_FROMATE forNode->data.name, forNode->data.city, forNode->data.province, forNode->data.state, forNode->data.tel
#define PF_DATA "\t| %-10s| %-10s| %-10s| %-10s| %-10s\n"

// ����ڵ� 
typedef struct _node{
	DATA data;
	struct _node *next;
}NODE; 


NODE *createNullList(void);
NODE *createNewNode(DATA tmpData);
// insert
void insertNodeByHead(NODE *headNode, DATA tmpData);
void insertNodeByEnd(NODE *headNode, DATA tmpData);
void insertNodeByPosDataInt(NODE *headNode, int dataId, DATA tmpData);
void insertNodeByPosDataStr(NODE *headNode, char *dataStrId, DATA tmpData);
// delete
int delNodeByPosIndex(NODE *headNode, int posIndex);
int delNodeByPosDataInt(NODE *headNode, int dataId);
int delNodeByPosDataStr(NODE *headNode, char *dataStrId);
int delNodeByPosDataStrRe(NODE *headNode, char *dataStrId);
// update
int updateNodeByPosDataInt(NODE *headNode, int dataId, DATA tmpData);
int updataNodeByPosIndex(NODE *headNode, int posIndex, DATA tmpData);
// search
int searchNodeByPosDataInt(NODE *headNode, int dataId);
int searchNodeByPosDataStr(NODE *headNode, char *dataStrId);
int searchNodeByPosIndex(NODE *headNode, int posIndex);
// printall
int printList(NODE *headNode, int mode);

// tools 
NODE *returnFrontEndNode(NODE *headNode);
int freeList(NODE *headNode);
int listIsNull(NODE *headNode);
int listLength(NODE *headNode);
void printFormatInfo(NODE *forNode);

int saveListToHexFile(NODE *headNode, char *filePath);
int loadListFromHexFile(NODE *headNode, char *filePath);

// sort
int listSortFunc(NODE *headNode);

// rand
DATA randNodeData(void);

#endif 
