//#define _CRT_SECURE_NO_WARNINGS

#include "EventLog.pb.h"

#include "templates.h"

#include "settings.h"
#include "loading_page.h"
#include "device_prop.h"
#include "mainform.h"
#include "mapform.h"
#include <Psapi.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;
using namespace Evrika;

ref class Worker {
	static loading_page^ ldwnd;
	static Thread^ loadthrd;

public:
	Worker() {
	}

	static void Work() {
		loadthrd = gcnew Thread(gcnew ThreadStart(showload));
		loadthrd->IsBackground = true;
		loadthrd->Start();

		mainform^ mainwnd = gcnew mainform();
		Application::Run(mainwnd);
	}
	static void showload() {
		ldwnd = gcnew loading_page();
		Application::Run(ldwnd);
	}

};

[STAThreadAttribute]
void Main(cli::array<String^>^ args) {
	//Kill other "Evrika.exe"
	{	
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		HANDLE hProcess;
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
			MessageBoxA(0, "EnumProcesses", "err", 0);
		}
		cProcesses = cbNeeded / sizeof(DWORD);
		DWORD myPID = GetCurrentProcessId();
		for (DWORD i = 0; i < cProcesses; i++) {
			if (aProcesses[i] != 0) {
				wchar_t szProcessName[MAX_PATH] = TEXT("<unknown>");
				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
				if (hProcess != NULL) {
					HMODULE hMod;
					DWORD cbNeedeb2;
					if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeedeb2)) {
						GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
						String^ str = gcnew String(szProcessName);
						if (str == "Evrika.exe") {
							if (aProcesses[i] == myPID) {
								;
							}
							else {
								if (!TerminateProcess(hProcess, 0)) {
									MessageBoxA(0, "TerminateProcess", "err", 0);
								}
							}
						}
					}
				}
				CloseHandle(hProcess);
			}
		}
	}
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	try {
		Worker^ w = gcnew Worker();
		w->Work();
	}
	catch (Exception ^e) {
		MessageBoxA(0, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(e->Message), "Exception", 0);
	}
}
