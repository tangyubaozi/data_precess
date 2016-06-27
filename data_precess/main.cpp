// main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//int main1()
//{
//	LIST *pListTime = NULL;				//定点数据
//	LIST *pListOrbit = NULL;			//轨道数据
//	DATASPACE *space;
//	space = (DATASPACE *)malloc(sizeof(DATASPACE));
//	pListTime = (LIST *)malloc(sizeof(LIST));
//	pListOrbit = (LIST *)malloc(sizeof(LIST));
//	pListTime->head = NULL;
//	pListOrbit->head = NULL;
//	pListTime->p_pointer = NULL;
//	pListOrbit->p_pointer = NULL;
//	pListTime->nodesize = 0;		
//	pListOrbit->nodesize = 0;
//
//	ReadTimeList(pListTime);
//	ReadOrbit(pListOrbit);
//	InsertNum(pListOrbit, pListTime);
////	Save(pListTime);
//	Precess(pListTime,space);
//	printf("OK");
//	getchar();		//为了停留在命令窗口
////==================================================================================
//	HANDLE   hth1;
//	unsigned  uiThread1ID;
//
//	hth1 = (HANDLE)_beginthreadex(NULL,         // security
//		0,            // stack size
//		(unsigned int(__stdcall *)(void *))MainThread,
//		NULL,           // arg list
//		CREATE_SUSPENDED,  // so we can later call ResumeThread()
//		&uiThread1ID);
//
//	if (hth1 == 0)
//		printf("Failed to create thread 1\n");
//
//	DWORD   dwExitCode;
//
//	GetExitCodeThread(hth1, &dwExitCode);  // should be STILL_ACTIVE = 0x00000103 = 259
//
//
//
//
//	o1->threadName = "t1";
//
//	ThreadX * o2 = new ThreadX(0, 1, -10000, 10000);
//
//	HANDLE   hth2;
//	unsigned  uiThread2ID;
//
//	hth2 = (HANDLE)_beginthreadex(NULL,         // security
//		0,            // stack size
//		(unsigned int(__stdcall *)(void *))ThreadFUN1,
//		o2,           // arg list
//		CREATE_SUSPENDED,  // so we can later call ResumeThread()
//		&uiThread2ID);
//
//	if (hth2 == 0)
//		printf("Failed to create thread 2\n");
//	STILL_ACTIVE
//	GetExitCodeThread(hth2, &dwExitCode);  // should be STILL_ACTIVE = 0x00000103 = 259
//	printf("initial thread 2 exit code = %u\n", dwExitCode);
//	output << "initial thread 2 exit code = " << dwExitCode << endl;
//
//	o2->threadName = "t2";
//
//	// If we hadn't specified CREATE_SUSPENDED in the call to _beginthreadex()
//	// we wouldn't now need to call ResumeThread().
//
//	ResumeThread(hth1);   // serves the purpose of Jaeschke's t1->Start()
//
//	ResumeThread(hth2);
//
//	// In C++/CLI the process continues until the last thread exits.
//	// That is, the thread's have independent lifetimes. Hence
//	// Jaeschke's original code was designed to show that the primary
//	// thread could exit and not influence the other threads.
//
//	// However in C++ the process terminates when the primary thread exits
//	// and when the process terminates all its threads are then terminated.
//	// Hence if you comment out the following waits, the non-primary
//	// threads will never get a chance to run.
//
//	WaitForSingleObject(hth1, INFINITE);
//	WaitForSingleObject(hth2, INFINITE);
//
//	GetExitCodeThread(hth1, &dwExitCode);
//	printf("thread 1 exited with code %u\n", dwExitCode);
//	output << "thread 1 exited with code " << dwExitCode << endl;
//
//	GetExitCodeThread(hth2, &dwExitCode);
//	printf("thread 2 exited with code %u\n", dwExitCode);
//	output << "thread 2 exited with code " << dwExitCode << endl;
//	// The handle returned by _beginthreadex() has to be closed
//	// by the caller of _beginthreadex().
//
//	CloseHandle(hth1);
//	CloseHandle(hth2);
//
//	delete o1;
//	o1 = NULL;
//
//	delete o2;
//	o2 = NULL;
//
//	printf("Primary thread terminating.\n");
//	output << "Primary thread terminating." << endl;
//	getchar();
//	
//    return 0;
//}

int main(int argc, char *argv[])//第一个参数是序号，第二个参数是工作路径；
{
	char strFilemapping_name[20];
	char *pWorkspace_dir;
	sprintf_s(strFilemapping_name, "FileID%s", argv[1]);
	pWorkspace_dir = argv[2];
	LIST *pListTime = NULL;				//定点数据
	LIST *pListOrbit = NULL;			//轨道数据
	DATASPACE *space;
	space = (DATASPACE *)malloc(sizeof(DATASPACE));
	pListTime = (LIST *)malloc(sizeof(LIST));
	pListOrbit = (LIST *)malloc(sizeof(LIST));
	pListTime->head = NULL;
	pListOrbit->head = NULL;
	pListTime->p_pointer = NULL;
	pListOrbit->p_pointer = NULL;
	pListTime->nodesize = 0;
	pListOrbit->nodesize = 0;
	//*************************************************
	/*HANDLE hFileMapping;
	hFileMapping = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		0x10000,
		strFilemapping_name);*/
	//**************************************************

	ReadTimeList(pListTime, pWorkspace_dir);//需要设置命令行参数
//	ReceiveTimeList(pListTime,strFilemapping_name);//内存共享版本
	ReadOrbit(pListOrbit);
	InsertNum(pListOrbit, pListTime);
	//	Save(pListTime);
	Precess(pListTime, space, pWorkspace_dir);
//	Precess0(pListTime, space, pWorkspace_dir);
	printf("OK");
	return 0;
}


