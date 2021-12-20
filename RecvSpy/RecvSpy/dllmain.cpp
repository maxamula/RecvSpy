// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "Hook.h"
#include "minhook/minhook.h"
#include <cstdio>


void Main()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    if (MH_Initialize() != MH_OK)
        printf("MH_Initialize failed\n");

    if (MH_CreateHookApi(L"Ws2_32", "recv", DetourRecv, (LPVOID*)&precv) != MH_OK)
        printf("send hook failed\n");

    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        printf("MH_EnableHook failed\n");

    while (true)
    {
        if (GetAsyncKeyState(VK_F1))
        {
            bIntercept = !bIntercept;
        }
        Sleep(10);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

