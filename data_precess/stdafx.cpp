// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// data_precess.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ
// ������Ҫ�Ļ������к���
//

#include "stdafx.h"
#define SREACHENTRY item.timeUTCG//������

// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������

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
		//		fscanf(fp,"%d",&n);					/*������¼������*/

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
		printf("\n�������ļ������޷��������ļ���");
		return;
	}
}
void ReadOrbit(LIST *plist)
{
	ITEM0 *p0;
	NODE *p1,*pFirst;
	FILE *fp;
	errno_t err;
	srand(GetTickCount());		//���������
	if ((err = fopen_s(&fp, "C:/Users/Ttyy/Documents/Visual Studio 2015/Projects/data_precess/Debug/" FILENAME_ORBIT_IN, "r")) == 0)
	{
		//		fscanf(fp,"%d",&n);					/*������¼������*/
		pFirst = (NODE *)malloc(sizeof(NODE));
		p0 = (ITEM0 *)malloc(sizeof(ITEM0));
		p1 = (NODE *)malloc(sizeof(NODE));
		fread(p0, sizeof(ITEM0), 1, fp);
		String2BinaryBytesFirst(pFirst, p0);//������ʼֵ��
		String2BinaryBytes(p1, p0, pFirst);//��һ����ȡ��
		free(p0);
		Insert(plist, p1);
		while (1)
		{
			p0 = (ITEM0 *)malloc(sizeof(ITEM0));
			p1 = (NODE *)malloc(sizeof(NODE));
			fread(p0, sizeof(ITEM0), 1, fp);
			if (feof(fp))	break;
			String2BinaryBytes(p1, p0 ,pFirst);//��һ����ȡ��
			free(p0);
			//			p1->item.num = 0;//##################��δʹ��###############
			if (p1->item.timeUTCG % UNITORBITPRE == 0)
			{
				p1->item.timeps += (int)(NormalRandom(0, 200, -1000, 1000) * 100);//������������˹������
//###########################################�������##########################################
				Insert(plist, p1);
			}
			

		}// while (!feof(fp));
		fclose(fp);
		free(pFirst);
		return;
	}
	else
	{
		printf("\n�������ļ������޷��������ļ���");
		return;
	}
}
//*********************�������Բ�ֵ****************************
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
		srand(GetTickCount());		//���������
		InsertNumFacter(p0, p1, abc);
		DoInsertNum(p0, p1, abc, pListTime);
		if (pListTime->p_pointer == NULL)
			break;

	} while (p->next != NULL);
	
	return;
}

void InsertUn(LIST *plist, NODE *p)				/*ֱ���������*/
{
//	NODE  *p1;
	p->next = NULL;
	plist->end->next = p;
	plist->end = p;	
	plist->nodesize++;				/*�ڵ�����+1*/
	return;
}

void Insert(LIST *plist, NODE *p)				/*�����������*/
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
	plist->nodesize++;				/*�ڵ�����+1*/
	plist->end = p;
	return;
}

void Save(LIST *plist)//(����)
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
		printf("\n�������ļ������޷��������ļ���");
}
