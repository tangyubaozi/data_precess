// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once
#define _USE_MATH_DEFINES //������include֮ǰ

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <assert.h> 
#include <iostream> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <Windows.h>
#include <math.h>
#include <process.h>



#define PI 3.1415926535898
#define DIRECTORY "D:/1234/"			//�ļ�·�������ã�
#define FILENAME_TIMELIST_IN "printttyy.dat"		//�����ļ�����Ҫ�С����ţ�	���ͽ���ƥ������
#define FILENAME_OUT "output.dat"					//������recv_fixed.dat�ļ�
#define FILENAME_ORBIT_IN "input.txt"				//�������
#define SWICH_GPS 5			//	=5��GPS�źŲ�����ʱ��>5:GPS�źż���ʱ�������� <5

#define LEN sizeof(NODE)
#define SIZE1 9//�����ļ�FILENAME_ORBIT_IN��һ����ַ������ȣ�ʱ���
#define SIZE2 12//�����ļ��ڶ�����ַ������ȣ�ʱ��
//#define INSERTSIZE 10//��ֵ�ȼ���10��100��1000��10000
#define DATASIZE 10000000//		������Ŀ����������data_precess.cpp
#define UNITTIMEUTCG 1000000000//	�����׼ʱ�ӵĵ�λ��ms=1;us=1,000;ns=1,000,000;ps=1,000,000,000
#define UNITORBITPRE 1000000000000//������ʱ�侫�ȣ�1s=1e12;1ms=1e9


typedef struct {
	char a;//ͨ����
	__int64 b;//���ϣ����䣩
	__int64 c;//���棨���ܣ�
}ITEM_TIMELIST;		//ʱ���б��ʽ

typedef struct note0
{
	char timeUTCG[SIZE1];
	char timeps[SIZE2];
}ITEM0;		//ASC�ı���ȡ�洢�ռ�

typedef struct note
{
	char num;
	__int64 timeUTCG;
	__int64 timeps;
}ITEM;		//��������ֵ�洢�ռ�
typedef struct node
{
	ITEM item;
	struct node *next;

}NODE;		//��������ֵ�洢�ռ������ڵ�
typedef struct list
{
	NODE *head;
	int nodesize;
	ITEM head_item;
	int I;			//�����õĹ�����������¼���ҵ��ļ�¼��Ŀ��
	NODE *p_pointer;//�����ڲ�ָ��
	NODE *end;		//β���ڵ�
}LIST;		//�����ͷ

typedef struct 
{
	double a;
	double b;
	const double miu;
	const double sigma;
	const double min;
	const double max;
}FACTER;		//��ֵ��ʽϵ���������ϵ���洢�ռ�

typedef struct
{
	__int64 time[DATASIZE];
	char channel[DATASIZE];
}DATASPACE;		//����data_precess.cpp

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�


void ReceiveTimeList(LIST *plist, char strFilemapping_name[]);
void ReadTimeList(LIST *plist, char pWorkspace_dir[]);
void ReadOrbit(LIST *plist);
void String2BinaryBytesFirst(NODE *p, ITEM0 *p0);
void String2BinaryBytes(NODE *p, ITEM0 *p0, NODE *pFirst);
void InsertNumAndSave(NODE *p0, NODE *p1);//(����)
void InsertNumFacter(NODE *p0, NODE *p1, FACTER *abc);
void InsertNum(LIST *plist, LIST *pListTime);
void DoInsertNum(NODE *pmin, NODE *pmax, FACTER *abc, LIST *pListTime);
void Insert(LIST *plist, NODE *p);
int char2byte(char c);
__int64 Time2BinaryBytes(char *timeUTCG);
void Save(LIST *plist);//(����)
void InsertUn(LIST *plist, NODE *p);
void Precess(LIST *plist, DATASPACE *space, char *pWorkspace_dir);



double NormalRandom(double miu, double sigma, double min, double max);//��̬�ֲ����
double Normal(double x, double miu, double sigma);
double AverageRandom(double min, double max);
void DoRandom(double miu, double sigma, double min, double max);
void Precess0(LIST *plist, DATASPACE *space, char *pWorkspace_dir);