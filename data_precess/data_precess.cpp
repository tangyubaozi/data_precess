// data_precess.cpp : 数据处理，格式转换等
//

#include "stdafx.h"


void Precess(LIST *plist, DATASPACE *space,char *pWorkspace_dir)
{
	__int64 time[10000];		//临时存储器
	__int64 i = 0;
	__int64 j = 0;

	NODE *p;
	FILE *fp, *fplog;
	errno_t err;
	char string[100];
	sprintf_s(string,"%s" FILENAME_OUT, pWorkspace_dir);
	memset(space->time, 0, plist->nodesize);
	memset(space->channel, 0, plist->nodesize);
	memset(time, 0, 1000);

	p = plist->head;		//移动节点
	while (p->next->next != NULL)
	{
		if (p->next->item.num == 5)
		{
			time[j] = p->next->item.timeps;
			p->next = p->next->next;
			j++;
		}
		p = p->next;
	}
	p = plist->head;
	
	space->time[i] = time[0];
	space->channel[i] = 5;
	i++;
	j = 1;
	while (p != NULL)
	{
		if ((time[j] >= space->time[i - 1]) && (time[j] < p->item.timeps))
			{
				space->time[i] = time[j];
				space->channel[i] = 5;
				i++;
				j++;
			
			}
		else
		{
			space->time[i] = p->item.timeps;
			space->channel[i] = p->item.num;
			i++;
			p = p->next;
		}
				
	}
	//if (i != plist->nodesize )
	//{
	//	printf("数据处理出错，位于data_precess.cpp");
	//}

	if ((err = fopen_s(&fp, string, "wb")) == 0)
	{

		for (i = 0; i < plist->nodesize;i++)
		{
			fwrite(&space->channel[i], 1, 1, fp);
			fwrite(&space->time[i], 8, 1, fp);
		}
		fclose(fp);
	}
	else
		printf("\n！保存文件出错：无法打开数据文件！");

	freopen_s(&fplog, "D:/1234/output.txt", "w", stdout);
	for (i = 0; i < plist->nodesize; i++)
	{
		printf("%5d		%lld\n", space->channel[i], space->time[i]);
	}
	fflush(fplog);
	fclose(fplog);

	return;
}

void Precess0(LIST *plist, DATASPACE *space, char *pWorkspace_dir)//没有排序的版本
{
	__int64 time[10000];		//临时存储器
	__int64 i = 0;
	__int64 j = 0;

	NODE *p;
	FILE *fp;
	errno_t err;
	char string[100];
	sprintf_s(string, "%s" FILENAME_OUT, pWorkspace_dir);
	memset(space->time, 0, plist->nodesize);
	memset(space->channel, 0, plist->nodesize);
	memset(time, 0, 1000);

	p = plist->head;		//移动节点

	while (p != NULL)
	{
		space->channel[j] = p->item.num;
		space->time[j] = p->item.timeps;
		j++;
		p = p->next;
		

	}
	//if (i != plist->nodesize )
	//{
	//	printf("数据处理出错，位于data_precess.cpp");
	//}

	if ((err = fopen_s(&fp, string, "wb")) == 0)
	{

		for (i = 0; i < plist->nodesize; i++)
		{
			fwrite(&space->channel[i], 1, 1, fp);
			fwrite(&space->time[i], 8, 1, fp);
		}
		fclose(fp);
	}
	else
		printf("\n！保存文件出错：无法打开数据文件！");
	return;
}


//void Precess(LIST *plist)
//{
//	__int64 time[DATASIZE];
//	char channel[DATASIZE];
//	__int64 i = 0;
//
//	NODE *p, *p0, *p1;
//
//	memset(time, 0, plist->nodesize);
//	memset(channel, 0, plist->nodesize);
//
//	p = plist->head;		//移动节点
//	p0 = plist->head;		//定义移动节点的前一节点
//	if (p->item.num == 5)
//	{
//		time[i] = p->item.timeps;
//		i++;
//		plist->head = p->next;
//		//		free(p);
//	}
//	p = p->next;
//	while (p != NULL)
//	{
//		if (p->item.num == 5)
//		{
//			time[i] = p->item.timeps;
//			i++;
//			p0->next = p->next;
//			free(p);
//			p = p0->next;
//		}
//		else
//		{
//			p = p->next;
//			p0 = p0->next;
//		}
//	}
//
//}