#ifdef _UNICODE
#define SetConsoleTitle SetConsoleTitleW
#else
#define SetConsoleTitle SetConsoleTitleA
#endif

#include <Windows.h>
#include <iostream>

int main()
{
    SetEnvironmentVariable(L"PROC_TO_KILL", L"Telegram.exe,notepad.exe,chrome.exe");
    STARTUPINFO startupinfo = { sizeof startupinfo };
    PROCESS_INFORMATION processInformation = { 0 };
    std::wstring ws(L"/HELP /NAME Telegram.exe /PID 21868 /ENVV /EXIT");
    CreateProcess(L"..\\..\\ProcessKiller\\x64\\Debug\\ProcessKiller.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startupinfo,&processInformation);
}