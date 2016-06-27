//	dataASCtoBytes.cpp : 定义转换用函数
//	实现文件ASC码与二进制之间的转换
//

#include "stdafx.h"



void String2BinaryBytesFirst( NODE *p, ITEM0 *p0)
{
	p->item.num = 0;
	p->item.timeUTCG = Time2BinaryBytes(p0->timeUTCG);
	p->item.timeps = Decimalchar2BinaryBytes(p0->timeps);

	return;
}

void String2BinaryBytes(NODE *p, ITEM0 *p0 ,NODE *pFirst)
{
	p->item.num = 0;
	p->item.timeUTCG = Time2BinaryBytes(p0->timeUTCG) - pFirst->item.timeUTCG;
	p->item.timeps = Decimalchar2BinaryBytes(p0->timeps) - pFirst->item.timeps;

	return;
}
int char2byte(char c)
{
	int n;
	if ((c >= '0') && (c <= '9'))
		n = c - '0';
	else
	{
		n = 10;
	}
	return(n);
}
//*************************格式：XX(分):XX（秒）.XXX	***************************
__int64 Time2BinaryBytes(char *timeUTCG)
{
	int i;
	int n[SIZE1];
	__int64 n0 = 0;

	for (i = 0; i < SIZE1; i++)
	{
		n[i] = char2byte(timeUTCG[i]);
		if (n[i] == 10)
			continue;
		else
		{
			if (i == 3)
			{
				n0 *= 6;
				n0 += n[i];
			}
			else
			{
				n0 *= 10;
				n0 += n[i];
			}
		}
	}
	n0 *= UNITTIMEUTCG;
		return (n0);
}
//**************************十进制字符转二进制数(64位)*************************
__int64	Decimalchar2BinaryBytes(char *c)
{
	int i;
	int n[SIZE2];
	__int64 n0 = 0;
	for (i = 0; i < SIZE2; i++)
	{
		n[i] = char2byte(c[i]);
		if (n[i] == 10)
			continue;
		else
		{
			n0 *= 10;
			n0 += n[i];	
		}
	}
	return (n0);
}

//*********************二进制转字符********************
//void BinaryBytes2Decimalchar(__int64 n)
//{
//	char c[];
//	int i;
//	do {
//		c[i] = (n % 10) + '0';
//		n /= 10;
//		i++;
//	} while (true)
//	{
//
//	}
//}