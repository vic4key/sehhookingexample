#include <windows.h>
#include "memoryHook.h"


void MessageBoxAHook(PCONTEXT ctx)
{
	char* text = (char*)*memoryHook::getArg(ctx, 1);
	char* caption = (char*)*memoryHook::getArg(ctx, 2);
	printf("MessageBoxA [ %s: %s ]\n", caption, text);

	DWORD returnAddress = (DWORD)*memoryHook::getReturnAddress(ctx);
	__asm
	{
		JMP [returnAddress]
	}
}

DWORD WINAPI startUpThread(LPVOID args)
{
	DWORD MessageBoxA = (DWORD)GetProcAddress(GetModuleHandleA("User32.dll"), "MessageBoxA");
	
	if (MessageBoxA)
		memoryHook::add(MessageBoxA, MessageBoxAHook);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(NULL, 0, startUpThread, NULL, 0, NULL);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
	}
	return TRUE;
}

