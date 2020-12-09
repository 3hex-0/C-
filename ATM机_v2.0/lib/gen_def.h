#ifndef _GEN_DEF_H_
#define _GEN_DEF_H_

/* 
	filename : gen_def.h (ͨ��ͷ�ļ�)
 	version  : v1.0
 	content  : ���峣�õĺ궨�塢���κ�� ���ö��� 
 	author   : 3hex
 	date     : 2020-10-27 
*/ 

// 0.Ĭ�ϲ���

// 1.�������Ͷ���
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef uchar byte;
typedef long double ldouble;

// 2.��������
// ...

// 3.����ǿת
#define DOU(x) ((double)(x))
#define FLOAT(x) ((float)(x))
#define INT(x) ((int)(x))
#define UINT(x) ((uint)(x))
#define LONG(x) ((long)(x))
#define ULONG(x) ((ulong)(x))
#define UCHAR(x) ((uchar)(x))
#define BYTE(x) ((byte)(x))

// 4.�����вκ궨��
// func:����x,y��ֵ 
#define SWAP(x,y) ((x)^=(y),(y)^=(x),(x)^=(y)) 
// func:�κ��������� תΪ���� (֧��double) 
#define NUM_TO_POS(x)  (DOU(x)<0.0? DOU(-(x)):DOU((x)))
// func:���������������ֵ (֧��double) 
#define NUM_MAX_2(x,y)  (DOU(x)>DOU(y)? DOU((x)):DOU((y)))
// func:���������������ֵ (֧��double) 
#define NUM_MIN_2(x,y)  (DOU(x)<DOU(y)? DOU((x)):DOU((y)))
// func:�ж��������ǲ������ (֧��double)
#define NUM_EQUAL(x,y) ((NUM_TO_POS((x)-(y))<1E-7)? 1.0:0.0) 

#endif
