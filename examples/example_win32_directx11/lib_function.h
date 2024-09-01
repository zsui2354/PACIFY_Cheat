//#pragma once

#ifndef LIB_FUNCTION_H
#define LIB_FUNCTION_H

#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <exception>
#include <psapi.h>


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

LONG_PTR GetPID(const TCHAR* processName);//��ȡ����PID

LONG_PTR GetModuleBase(const TCHAR* moduleName, HANDLE handle);//��ȡģ����  ___����

ImVec4 color_Changes(int value);    //�ж���ֵ���ض�Ӧ��ɫ

#endif // ADDRESS_OFFSET_H
