// data_precess.cpp : ���ݴ�����ʽת����
//

#include "stdafx.h"


void Precess(LIST *plist, DATASPACE *space,char *pWorkspace_dir)
{
	__int64 time[10000];		//��ʱ�洢��
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

	p = plist->head;		//�ƶ��ڵ�
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
	//	printf("���ݴ������λ��data_precess.cpp");
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
		printf("\n�������ļ������޷��������ļ���");

	freopen_s(&fplog, "D:/1234/output.txt", "w", stdout);
	for (i = 0; i < plist->nodesize; i++)
	{
		printf("%5d		%lld\n", space->channel[i], space->time[i]);
	}
	fflush(fplog);
	fclose(fplog);

	return;
}

void Precess0(LIST *plist, DATASPACE *space, char *pWorkspace_dir)//û������İ汾
{
	__int64 time[10000];		//��ʱ�洢��
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

	p = plist->head;		//�ƶ��ڵ�

	while (p != NULL)
	{
		space->channel[j] = p->item.num;
		space->time[j] = p->item.timeps;
		j++;
		p = p->next;
		

	}
	//if (i != plist->nodesize )
	//{
	//	printf("���ݴ������λ��data_precess.cpp");
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
		printf("\n�������ļ������޷��������ļ���");
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
//	p = plist->head;		//�ƶ��ڵ�
//	p0 = plist->head;		//�����ƶ��ڵ��ǰһ�ڵ�
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