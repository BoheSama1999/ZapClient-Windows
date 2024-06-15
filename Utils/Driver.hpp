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

// 初始化驱动 	返回true 成功 false 失败  
EXTERN_C typedef BOOL(WINAPI* pInitDriver)(std::string key);
// 读内存		后面的都是返回 0 成功 其他值失败
EXTERN_C typedef ULONG(WINAPI* pReadProcessMemory)(ULONG pid, ULONG64 address, PVOID buffer, ULONG size);
// 写内存
EXTERN_C typedef ULONG(WINAPI* pWriteProcessMemory)(ULONG pid, ULONG64 address, PVOID buffer, ULONG size);
// 获取进程模块信息
EXTERN_C typedef ULONG(WINAPI* pGetProcessModule)(ULONG pid, PCHAR buffer, ULONG64& modulebase, ULONG& modulesize);
// 伪装进程		参数1 自己pid 参数2 伪装的那个进程的pid
EXTERN_C typedef ULONG(WINAPI* pPakeProcess)(ULONG pid, ULONG fakePid);
// 保护进程		参数1 任意进程pid 参数2 true 保护 false 去掉保护
EXTERN_C typedef ULONG(WINAPI* pProtectProcess)(ULONG pid, BOOL isProctect);
// 保护窗口
EXTERN_C typedef ULONG(WINAPI* pProtectWindow)(ULONG hwnd);
// 反截图
EXTERN_C typedef ULONG(WINAPI* pAntiSnapshot)(ULONG hwnd);
// dll无模块注入  参数1 被注入的进程pid  参数2 dll绝对路径 参数3 0 创建线程 1 劫持线程  2 插APC  参数4 是否清理痕迹 有0.5秒延迟
EXTERN_C typedef ULONG(WINAPI* pDllInject)(ULONG pid, PCHAR dllpath, UCHAR type, bool isClean);
// 无附加申请内存 参数1 要申请内存的进程pid  参数2 分配多少字节  参数3 接收申请到的内存地址 参数4 0 无附加申请内存  1 获取申请到的内存地址(配合0使用) 3 内核申请隐藏内存
EXTERN_C typedef ULONG(WINAPI* pGetAllocateProcessMem)(ULONG pid, ULONG memSize, PULONG64 AllocatedAddr, BOOL type);
// pe转shellcode注入 无拉伸 需提前自行拉伸pe 参数3 0 创建线程  1 劫持线程  2 APC启动  参数4 是否清理痕迹 有0.5秒延迟 频繁调用不用清理 可以当远程call使用
EXTERN_C typedef ULONG(WINAPI* pPEShellocdeInject)(ULONG pid, PCHAR dllFilePath, UCHAR type, bool isClean);
// 内核搜特征码	看例子 FeatureCodes(pid, "模块名", "\x00\x00\x00\x00","xxxx", &addr); //接收搜到的地址
EXTERN_C typedef ULONG(WINAPI* pFeatureCodes)(ULONG pid, PCHAR moduleName, const char* pattern, const char* mask, PULONG64 addr);
// 模拟鼠标移动		参数3 0 相对移动 1绝对移动
EXTERN_C typedef ULONG(WINAPI* pMouseMove)(ULONG dx, ULONG dy, USHORT Flags);
// 模拟键盘按键
EXTERN_C typedef ULONG(WINAPI* pKeyboardButton)(USHORT VirtualKey, USHORT Flags);
// 模拟鼠标点击
EXTERN_C typedef ULONG(WINAPI* pMouseRughtButton)(USHORT Flags);
// 强删文件 
EXTERN_C typedef ULONG(WINAPI* pForceDeleteFile)(PWCHAR filepath);
// 贝塞尔自瞄
EXTERN_C typedef ULONG(WINAPI* pBezierMov)(float x, float y, ULONG w, ULONG h, float speed);
// 获取cr3  参数2 接收cr3  参数3  0 解密获取  1 常规获取
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