// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#define _USE_MATH_DEFINES //定义在include之前

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
#define DIRECTORY "D:/1234/"			//文件路径（无用）
#define FILENAME_TIMELIST_IN "printttyy.dat"		//数据文件名（要有“”号）	发送接收匹配数据
#define FILENAME_OUT "output.dat"					//处理后的recv_fixed.dat文件
#define FILENAME_ORBIT_IN "input.txt"				//轨道数据
#define SWICH_GPS 5			//	=5：GPS信号不加延时；>5:GPS信号加延时；不允许 <5

#define LEN sizeof(NODE)
#define SIZE1 9//输入文件FILENAME_ORBIT_IN第一项的字符串长度，时间点
#define SIZE2 12//输入文件第二项的字符串长度，时延
//#define INSERTSIZE 10//插值等级：10，100，1000，10000
#define DATASIZE 10000000//		数据条目数量，用于data_precess.cpp
#define UNITTIMEUTCG 1000000000//	定义标准时钟的单位：ms=1;us=1,000;ns=1,000,000;ps=1,000,000,000
#define UNITORBITPRE 1000000000000//定义轨道时间精度：1s=1e12;1ms=1e9


typedef struct {
	char a;//通道号
	__int64 b;//天上（发射）
	__int64 c;//地面（接受）
}ITEM_TIMELIST;		//时间列表格式

typedef struct note0
{
	char timeUTCG[SIZE1];
	char timeps[SIZE2];
}ITEM0;		//ASC文本读取存储空间

typedef struct note
{
	char num;
	__int64 timeUTCG;
	__int64 timeps;
}ITEM;		//二进制数值存储空间
typedef struct node
{
	ITEM item;
	struct node *next;

}NODE;		//二进制数值存储空间的链表节点
typedef struct list
{
	NODE *head;
	int nodesize;
	ITEM head_item;
	int I;			//查找用的关联变量，记录查找到的记录条目数
	NODE *p_pointer;//链表内部指针
	NODE *end;		//尾部节点
}LIST;		//链表表头

typedef struct 
{
	double a;
	double b;
	const double miu;
	const double sigma;
	const double min;
	const double max;
}FACTER;		//插值公式系数，随机数系数存储空间

typedef struct
{
	__int64 time[DATASIZE];
	char channel[DATASIZE];
}DATASPACE;		//用于data_precess.cpp

// TODO:  在此处引用程序需要的其他头文件


void ReceiveTimeList(LIST *plist, char strFilemapping_name[]);
void ReadTimeList(LIST *plist, char pWorkspace_dir[]);
void ReadOrbit(LIST *plist);
void String2BinaryBytesFirst(NODE *p, ITEM0 *p0);
void String2BinaryBytes(NODE *p, ITEM0 *p0, NODE *pFirst);
void InsertNumAndSave(NODE *p0, NODE *p1);//(弃用)
void InsertNumFacter(NODE *p0, NODE *p1, FACTER *abc);
void InsertNum(LIST *plist, LIST *pListTime);
void DoInsertNum(NODE *pmin, NODE *pmax, FACTER *abc, LIST *pListTime);
void Insert(LIST *plist, NODE *p);
int char2byte(char c);
__int64 Time2BinaryBytes(char *timeUTCG);
void Save(LIST *plist);//(弃用)
void InsertUn(LIST *plist, NODE *p);
void Precess(LIST *plist, DATASPACE *space, char *pWorkspace_dir);



double NormalRandom(double miu, double sigma, double min, double max);//正态分布随机
double Normal(double x, double miu, double sigma);
double AverageRandom(double min, double max);
void DoRandom(double miu, double sigma, double min, double max);
void Precess0(LIST *plist, DATASPACE *space, char *pWorkspace_dir);