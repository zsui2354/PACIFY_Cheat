#include <iostream>
#include <vector>
#include <Windows.h>
#include "lib_function.h"
#include "addressOffset.h"





#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

/// <summary>
/// ��ȡ����PID
/// </summary>
/// <param name="processName"></param>
/// <returns></returns>
LONG_PTR GetPID(const TCHAR* processName)
{
    bool success;  // ������������ success
    PROCESSENTRY32 pe = { sizeof(pe) };
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE)  // ���� snapshot �ж�����
        return 1;
        //std::cout << "��������ʧ��";
        //throw std::exception("��������ʧ��");
        //std::cout << "��������ʧ��";
    

    success = Process32First(snapshot, &pe);
    if (_tcscmp(processName, pe.szExeFile) == 0)
    {
        CloseHandle(snapshot);
        return pe.th32ProcessID;
    }

    while (success)
    {
        success = Process32Next(snapshot, &pe);
        if (_tcscmp(processName, pe.szExeFile) == 0)
        {
            CloseHandle(snapshot);
            return pe.th32ProcessID;
        }
    }

    CloseHandle(snapshot);
    return NULL;
}


/// <summary>
/// ��ȡģ���ַ����		//�����ü�������
/// </summary>
/// <param name="moduleName"></param>
/// <param name="handle"></param>
/// <returns></returns>
LONG_PTR GetModuleBase(const TCHAR* moduleName, HANDLE handle)
{
	HMODULE hmodules[1024];
	DWORD size;
	EnumProcessModules(handle, hmodules, sizeof(hmodules), &size);
	for (size_t i = 0; i < size; i++)
	{
		HMODULE mod = hmodules[i];
		TCHAR name[MAX_PATH];
		GetModuleBaseName(handle, mod, name, MAX_PATH);
		if (_tcscmp(moduleName, name) == 0)
		{
			return (LONG_PTR)mod;
		}
	}
	return NULL;
}


ImVec4 color_Changes(int value) { 
    ImVec4 color;
    if (value > 75) {

        return color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);  // ��ɫ
    }
    else if (value > 25) {
        return color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);  // ��ɫ
    }
    else {
        return color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);  // ��ɫ
    }
}
