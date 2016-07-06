//	dataASCtoBytes.cpp : 定义转换用函数
//	实现文件ASC码与二进制之间的转换
//

#include "stdafx.h"



void String2BinaryBytesFirst( NODE *p, ITEM0 *p0)
{
	p->item.num = 0;
	p->item.timeUTCG = Time2BinaryBytes(p0->timeUTCG);
	p->item.timeps = atoll(p0->timeps);

	return;
}

void String2BinaryBytes(NODE *p, ITEM0 *p0 ,NODE *pFirst)
{
	p->item.num = 0;
	p->item.timeUTCG = Time2BinaryBytes(p0->timeUTCG) - pFirst->item.timeUTCG;
	p->item.timeps = atoll(p0->timeps) - pFirst->item.timeps;

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
