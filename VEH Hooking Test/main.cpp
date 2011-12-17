#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	LoadLibraryA("VEH Hook.dll");
	Sleep(100);

	MessageBoxA(NULL, "This is a VEH Hooking Test", "MBCaption", MB_OK);

	system("pause");
	return 0;
}

