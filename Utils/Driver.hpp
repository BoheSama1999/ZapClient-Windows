/*
* 
*		This is Kernel driver api to use the Driver
*		You should rewrite here for ur own driver works
* 
* 
*/
#pragma once
#include <windows.h>
#include <string>
#include <iostream>

// ��ʼ������ 	����true �ɹ� false ʧ��  
EXTERN_C typedef BOOL(WINAPI* pInitDriver)(std::string key);
// ���ڴ�		����Ķ��Ƿ��� 0 �ɹ� ����ֵʧ��
EXTERN_C typedef ULONG(WINAPI* pReadProcessMemory)(ULONG pid, ULONG64 address, PVOID buffer, ULONG size);
// д�ڴ�
EXTERN_C typedef ULONG(WINAPI* pWriteProcessMemory)(ULONG pid, ULONG64 address, PVOID buffer, ULONG size);
// ��ȡ����ģ����Ϣ
EXTERN_C typedef ULONG(WINAPI* pGetProcessModule)(ULONG pid, PCHAR buffer, ULONG64& modulebase, ULONG& modulesize);
// αװ����		����1 �Լ�pid ����2 αװ���Ǹ����̵�pid
EXTERN_C typedef ULONG(WINAPI* pPakeProcess)(ULONG pid, ULONG fakePid);
// ��������		����1 �������pid ����2 true ���� false ȥ������
EXTERN_C typedef ULONG(WINAPI* pProtectProcess)(ULONG pid, BOOL isProctect);
// ��������
EXTERN_C typedef ULONG(WINAPI* pProtectWindow)(ULONG hwnd);
// ����ͼ
EXTERN_C typedef ULONG(WINAPI* pAntiSnapshot)(ULONG hwnd);
// dll��ģ��ע��  ����1 ��ע��Ľ���pid  ����2 dll����·�� ����3 0 �����߳� 1 �ٳ��߳�  2 ��APC  ����4 �Ƿ�����ۼ� ��0.5���ӳ�
EXTERN_C typedef ULONG(WINAPI* pDllInject)(ULONG pid, PCHAR dllpath, UCHAR type, bool isClean);
// �޸��������ڴ� ����1 Ҫ�����ڴ�Ľ���pid  ����2 ��������ֽ�  ����3 �������뵽���ڴ��ַ ����4 0 �޸��������ڴ�  1 ��ȡ���뵽���ڴ��ַ(���0ʹ��) 3 �ں����������ڴ�
EXTERN_C typedef ULONG(WINAPI* pGetAllocateProcessMem)(ULONG pid, ULONG memSize, PULONG64 AllocatedAddr, BOOL type);
// peתshellcodeע�� ������ ����ǰ��������pe ����3 0 �����߳�  1 �ٳ��߳�  2 APC����  ����4 �Ƿ�����ۼ� ��0.5���ӳ� Ƶ�����ò������� ���Ե�Զ��callʹ��
EXTERN_C typedef ULONG(WINAPI* pPEShellocdeInject)(ULONG pid, PCHAR dllFilePath, UCHAR type, bool isClean);
// �ں���������	������ FeatureCodes(pid, "ģ����", "\x00\x00\x00\x00","xxxx", &addr); //�����ѵ��ĵ�ַ
EXTERN_C typedef ULONG(WINAPI* pFeatureCodes)(ULONG pid, PCHAR moduleName, const char* pattern, const char* mask, PULONG64 addr);
// ģ������ƶ�		����3 0 ����ƶ� 1�����ƶ�
EXTERN_C typedef ULONG(WINAPI* pMouseMove)(ULONG dx, ULONG dy, USHORT Flags);
// ģ����̰���
EXTERN_C typedef ULONG(WINAPI* pKeyboardButton)(USHORT VirtualKey, USHORT Flags);
// ģ�������
EXTERN_C typedef ULONG(WINAPI* pMouseRughtButton)(USHORT Flags);
// ǿɾ�ļ� 
EXTERN_C typedef ULONG(WINAPI* pForceDeleteFile)(PWCHAR filepath);
// ����������
EXTERN_C typedef ULONG(WINAPI* pBezierMov)(float x, float y, ULONG w, ULONG h, float speed);
// ��ȡcr3  ����2 ����cr3  ����3  0 ���ܻ�ȡ  1 �����ȡ
EXTERN_C typedef ULONG(WINAPI* pGetCr3Bypass)(ULONG pid, PULONG64 dir_base, ULONG type);

pInitDriver gInitDriver = 0;
pReadProcessMemory gReadProcessMemory = 0;
pWriteProcessMemory gWriteProcessMemory = 0;
pGetProcessModule gGetProcessModule = 0;
pPakeProcess gPakeProcess = 0;
pProtectProcess gProtectProcess = 0;
pProtectWindow gProtectWindow = 0;
pAntiSnapshot gAntiSnapshot = 0;
pDllInject gDllInject = 0;
pGetAllocateProcessMem gGetAllocateProcessMem = 0;
pPEShellocdeInject gPEShellocdeInject = 0;
pFeatureCodes gFeatureCodes = 0;
pKeyboardButton gKeyboardButton = 0;
pMouseRughtButton gMouseRughtButton = 0;
pMouseMove gMouseMove = 0;
pForceDeleteFile gForceDeleteFile = 0;
pBezierMov gBezierMov = 0;
pGetCr3Bypass gGetCr3Bypass = 0;

extern HMODULE hModule;

bool DInit(std::string key,HMODULE hModule) {

	if (!hModule)
	{
		printf("loadLibrary error\n");
		return false;
	}

	gInitDriver = (pInitDriver)GetProcAddress(hModule, "gInitDriver");
	gReadProcessMemory = (pReadProcessMemory)GetProcAddress(hModule, "gReadProcessMemory");
	gWriteProcessMemory = (pWriteProcessMemory)GetProcAddress(hModule, "gWriteProcessMemory");
	gGetProcessModule = (pGetProcessModule)GetProcAddress(hModule, "gGetProcessModule");
	gPakeProcess = (pPakeProcess)GetProcAddress(hModule, "gPakeProcess");
	gProtectProcess = (pProtectProcess)GetProcAddress(hModule, "gProtectProcess");
	gProtectWindow = (pProtectWindow)GetProcAddress(hModule, "gProtectWindow");
	gAntiSnapshot = (pAntiSnapshot)GetProcAddress(hModule, "gAntiSnapshot");
	gDllInject = (pDllInject)GetProcAddress(hModule, "gDllInject");
	gGetAllocateProcessMem = (pGetAllocateProcessMem)GetProcAddress(hModule, "gGetAllocateProcessMem");
	gPEShellocdeInject = (pPEShellocdeInject)GetProcAddress(hModule, "gPEShellocdeInject");
	gKeyboardButton = (pKeyboardButton)GetProcAddress(hModule, "gKeyboardButton");
	gMouseRughtButton = (pMouseRughtButton)GetProcAddress(hModule, "gMouseRughtButton");
	gGetCr3Bypass = (pGetCr3Bypass)GetProcAddress(hModule, "gGetCr3Bypass");
	gFeatureCodes = (pFeatureCodes)GetProcAddress(hModule, "gFeatureCodes");
	gMouseMove = (pMouseMove)GetProcAddress(hModule, "gMouseMove");
	gForceDeleteFile = (pForceDeleteFile)GetProcAddress(hModule, "gForceDeleteFile");
	gBezierMov = (pBezierMov)GetProcAddress(hModule, "gBezierMov");

	if (gInitDriver(key)) // key to init TK0P58DYEG76HS2AS0EMPGLZ8IV9N1LR
	{
		return true;
	}
	else
	{
		return false;
	}

}