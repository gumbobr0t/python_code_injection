#include <Windows.h>
#include <iostream>
#include <fstream>
#include "py/Python.h"
#include <string>

DWORD WINAPI MainThread(HMODULE hModule, std::string path)
{
    Py_Initialize();

    if (!Py_IsInitialized()) {
        fprintf(stderr, "Error initializing Python interpreter\n");
        return 1;
    }

    std::ifstream file(path);

    std::string data;
    getline(file, data, '\0');

    file.close();

    PyRun_SimpleString(data.c_str());
    
    Py_Finalize();

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    std::string path = "injection.txt";

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread(hModule, path), hModule, 0, 0));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}