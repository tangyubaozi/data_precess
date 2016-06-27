//	interpolate.cpp : 定义插值函数
//

#include "stdafx.h"

void InsertNumAndSave(NODE *p0, NODE *p1)//(弃用)
{
//	__int64 x0, y0, x1, y1;
	__int64 i;
	double a, b;
	NODE *p, *pp;
	FILE *fp;
	errno_t err;

	pp = p0;

	//x0 = p0->item.timeUTCG;
	//y0 = p0->item.timeps;
	//x1 = p1->item.timeUTCG;
	//y1 = p1->item.timeps;
	a = (p1->item.timeps - p0->item.timeps) / (p1->item.timeUTCG - p0->item.timeUTCG);	//(y1-y0)/(x1-x0)
	b = p0->item.timeps - (a*p0->item.timeUTCG);										//y0-a*x0
	for (i = p0->item.timeUTCG +1; i < p1->item.timeUTCG; i++)
	{
		p = (NODE *)malloc(sizeof(NODE));
		p->item.timeUTCG = i;
		p->item.timeps = a*i + b;
		
		pp->next = p;
		pp = p;
		p->next = p1;
//		printf("%lld	%lld	\n", p->item.timeUTCG, p->item.timeps);//CCCCCCCCCCCCCCCCCCC
	}
	
	pp->next = NULL;

	p = p0;
	

	if ((err = fopen_s(&fp, DIRECTORY FILENAME_OUT, "ab")) == 0)
	{
		do
		{
			
			fwrite(&p->item, sizeof(ITEM), 1, fp);
			pp = p;
//			printf("%lld	%lld	\n", p->item.timeUTCG, p->item.timeps);//CCCCCCCCCCCCCCCCCCC
			p = p->next;
			free(pp);
		} while (p != NULL);
		fclose(fp);
		printf("#");
	}
	else
		printf("\n！保存文件出错：无法打开数据文件！");
	return;
}

void InsertNumFacter(NODE *p0, NODE *p1, FACTER *abc)
{
//	__int64 x0, y0, x1, y1;
	//x0 = p0->item.timeUTCG;
	//y0 = p0->item.timeps;
	//x1 = p1->item.timeUTCG;
	//y1 = p1->item.timeps;
	abc->a = (double)(p1->item.timeps - p0->item.timeps) / (double)(p1->item.timeUTCG - p0->item.timeUTCG);
	abc->b = p0->item.timeps - (abc->a*p0->item.timeUTCG);
	//abc->a = a;
	//abc->b = b;
	return;
}

void DoInsertNum(NODE *pmin, NODE *pmax, FACTER *abc, LIST *pListTime)
{	
	NODE *p;
	__int64 random, addd;
	FILE *fplog;
	p = pListTime->p_pointer;
	freopen_s(&fplog, "D:/1234/add.txt", "at", stdout);
	do
	{

		if (!(p->item.num == SWICH_GPS))//GPS变化
		{
			if ((p->item.timeUTCG - pListTime->head_item.timeUTCG) >= pmin->item.timeUTCG)
				{
					random = NormalRandom(abc->miu, abc->sigma, abc->min, abc->max);
					p->item.timeps = abc->a * p->item.timeUTCG + abc->b + p->item.timeps + random;//	y=a*x+b+y0+random
					addd = random + abc->a * p->item.timeUTCG + abc->b;
					printf("%lld\n", addd);
					if ((p->item.timeUTCG - pListTime->head_item.timeUTCG) >= pmax->item.timeUTCG)
						break;		
				}
		}
		p = p->next;
	} while (p != NULL);
	pListTime->p_pointer = p;
	fflush(fplog);
	fclose(fplog);
	return;
}
