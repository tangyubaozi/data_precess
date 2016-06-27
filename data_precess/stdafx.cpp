// stdafx.cpp : 只包括标准包含文件的源文件
// data_precess.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息
// 定义主要的基本运行函数
//

#include "stdafx.h"
#define SREACHENTRY item.timeUTCG//排序项

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用

void ReceiveTimeList(LIST *plist, char strFilemapping_name[])
{
	ITEM *p0;
	NODE *p1;
	FILE *fp;
	errno_t err;
	HANDLE hFileMapping; 
	LPVOID lpShareMemory;
	ITEM *p;
	

	hFileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,
		strFilemapping_name);
	lpShareMemory = MapViewOfFile(hFileMapping,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);
	p = (ITEM *)lpShareMemory;
	p0 = p;
	p++;
		p1 = (NODE *)malloc(sizeof(NODE));
		plist->head_item = *p0;
		p1->item = *p0;
		plist->head = p1;
		plist->end = p1;
		plist->p_pointer = p1;
		while (1)
		{
			p0 = p;
			if (p0->timeps == NULL && p0->timeUTCG == NULL)	break;
			p++;
			p1 = (NODE *)malloc(sizeof(NODE));
			p1->item = *p0;
			InsertUn(plist, p1);						
		};
	UnmapViewOfFile(lpShareMemory);
	CloseHandle(hFileMapping);
	return;
}
void ReadTimeList(LIST *plist, char pWorkspace_dir[])
{
	ITEM *p0;
	NODE *p1;
	FILE *fp;
	errno_t err;
	char string[100];
	sprintf_s(string, "%s%s", pWorkspace_dir, FILENAME_TIMELIST_IN);
	if ((err = fopen_s(&fp, string, "rb")) == 0)
	{
		//		fscanf(fp,"%d",&n);					/*读出记录总数量*/

		p0 = (ITEM *)malloc(sizeof(ITEM));
		p1 = (NODE *)malloc(sizeof(NODE));
		fread(p0, sizeof(ITEM), 1, fp);
		plist->head_item = *p0;
		p1->item = *p0;
		plist->head = p1;
		plist->end = p1;
		plist->p_pointer = p1;
		while (1)
		{
			p0 = (ITEM *)malloc(sizeof(ITEM));
			p1 = (NODE *)malloc(sizeof(NODE));
			fread(p0, sizeof(ITEM), 1, fp);
			if (feof(fp))	break;
			p1->item = *p0;
			InsertUn(plist, p1);
			free(p0);

		};
		fclose(fp);
		return;
	}
	else
	{
		printf("\n！导入文件出错：无法打开数据文件！");
		return;
	}
}
void ReadOrbit(LIST *plist)
{
	ITEM0 *p0;
	NODE *p1,*pFirst;
	FILE *fp;
	errno_t err;
	srand(GetTickCount());		//随机数种子
	if ((err = fopen_s(&fp, "C:/Users/Ttyy/Documents/Visual Studio 2015/Projects/data_precess/Debug/" FILENAME_ORBIT_IN, "r")) == 0)
	{
		//		fscanf(fp,"%d",&n);					/*读出记录总数量*/
		pFirst = (NODE *)malloc(sizeof(NODE));
		p0 = (ITEM0 *)malloc(sizeof(ITEM0));
		p1 = (NODE *)malloc(sizeof(NODE));
		fread(p0, sizeof(ITEM0), 1, fp);
		String2BinaryBytesFirst(pFirst, p0);//读出初始值；
		String2BinaryBytes(p1, p0, pFirst);//归一化读取；
		free(p0);
		Insert(plist, p1);
		while (1)
		{
			p0 = (ITEM0 *)malloc(sizeof(ITEM0));
			p1 = (NODE *)malloc(sizeof(NODE));
			fread(p0, sizeof(ITEM0), 1, fp);
			if (feof(fp))	break;
			String2BinaryBytes(p1, p0 ,pFirst);//归一化读取；
			free(p0);
			//			p1->item.num = 0;//##################暂未使用###############
			if (p1->item.timeUTCG % UNITORBITPRE == 0)
			{
				p1->item.timeps += (int)(NormalRandom(0, 200, -1000, 1000) * 100);//在这里加了入了轨道噪声
//###########################################轨道噪声##########################################
				Insert(plist, p1);
			}
			

		}// while (!feof(fp));
		fclose(fp);
		free(pFirst);
		return;
	}
	else
	{
		printf("\n！导入文件出错：无法打开数据文件！");
		return;
	}
}
//*********************数据线性插值****************************
void InsertNum(LIST *plist,LIST *pListTime)
{
	NODE *p, *p0, *p1;
	FACTER abc_data = { 0,0,0,20000,-100000,100000 }, *abc;
	FILE *fp;
	errno_t err;
	abc = &abc_data;
	
//	abc = (FACTER *)malloc(sizeof(FACTER));
	p = plist->head;

	do
	{
		p0 = p;
		p1 = p->next;
		p = p->next;
		srand(GetTickCount());		//随机数种子
		InsertNumFacter(p0, p1, abc);
		DoInsertNum(p0, p1, abc, pListTime);
		if (pListTime->p_pointer == NULL)
			break;

	} while (p->next != NULL);
	
	return;
}

void InsertUn(LIST *plist, NODE *p)				/*直接链表插入*/
{
//	NODE  *p1;
	p->next = NULL;
	plist->end->next = p;
	plist->end = p;	
	plist->nodesize++;				/*节点数量+1*/
	return;
}

void Insert(LIST *plist, NODE *p)				/*有序链表插入*/
{
	NODE *p0 = NULL, *p1;

	if (plist->head == NULL)
	{
		plist->head = p;
		plist->p_pointer = p;
		p->next = NULL;
		plist->nodesize++;
		return;
	}
	if (p->SREACHENTRY < plist->head->SREACHENTRY)
	{
		p->next = plist->head;
		plist->head = p;
		plist->p_pointer = p;
		plist->nodesize++;
		return;
	}
	p1 = plist->head;
	while ((p->SREACHENTRY > p1->SREACHENTRY) && (p1->next != NULL))
	{
		p0 = p1;
		p1 = p1->next;
	}
	if (p->SREACHENTRY < p1->SREACHENTRY)
	{
		p->next = p1;
		p0->next = p;
	}
	else
	{
		p1->next = p;
		p->next = NULL;
	}
	plist->nodesize++;				/*节点数量+1*/
	plist->end = p;
	return;
}

void Save(LIST *plist)//(弃用)
{
	NODE *p;
	FILE *fp;
	errno_t err;
	p = plist->head;
	if ((err = fopen_s(&fp, DIRECTORY FILENAME_OUT, "wb")) == 0)
	{
		
		while (p != NULL)
		{	
			
			fwrite(&p->item, sizeof(ITEM), 1, fp);
			p = p->next;
		} 
		fclose(fp);
	}
	else
		printf("\n！保存文件出错：无法打开数据文件！");
}
