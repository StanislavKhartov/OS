#define _CRT_SECURE_NO_WARNINGS //для strpy в ручном режиме

#include <Windows.h>
#include <windef.h>
#include <handleapi.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <iostream>
#include <regex>

void endProcByName(std::string str) {
	std::vector<DWORD> pids;
	std::wstring targetProcessName(str.begin(), str.end());
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes
	PROCESSENTRY32W entry; //current process
	entry.dwSize = sizeof entry;

	if (!Process32FirstW(snap, &entry)) { //start with the first in snapshot
		return;
	}

	do {
		if (std::wstring(entry.szExeFile) == targetProcessName) {
			pids.emplace_back(entry.th32ProcessID); //name matches; add to list
		}
	} while (Process32NextW(snap, &entry)); //keep going until end of snapshot

	for (int i(0); i < pids.size(); ++i) {
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pids[i]);
		TerminateProcess(processHandle, 1);
		CloseHandle(processHandle);
	}
}


int main(int argc, char* argv[])
{
	int mode = 3;
	std::string str;
	//std::cin >> mode >> str;
	wchar_t wcstr[1000];
	GetEnvironmentVariable(L"PROC_TO_KILL", wcstr, sizeof(wcstr));
	std::wstring ws(wcstr);
	std::string str1(ws.begin(), ws.end());
	std::regex regex{ R"([,]+)" }; // split on space and comma
	std::sregex_token_iterator it{ str1.begin(), str1.end(), regex, -1 };
	std::vector<std::string> names{ it, {} };
	for (auto i : names) {
		endProcByName(i);
	}
	//int mode = atoi(argv[1]);
	if (mode == 1) {

		int n = str.length();
		char char_array[100 + 1];
		strcpy(char_array, str.c_str());

		DWORD procID = atoi(char_array);
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
		TerminateProcess(processHandle, 1);
		CloseHandle(processHandle);
		return 0;
	}
	if (mode == 2) {
		endProcByName(str);
	}
	return 0;
}
