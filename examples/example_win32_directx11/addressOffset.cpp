#include <iostream>
#include <Windows.h>
#include <vector>
#include <tlhelp32.h>
#include "lib_function.h"


DWORD_PTR roomLimit_baseAddressOffset           = 0x036840F0;									//����������ַ
std::vector<DWORD> roomLimit_offsets            = { 0x8, 0xA8, 0x170, 0x1F8, 0x2FC };
DWORD_PTR roomLimit_finalAddress;
int roomLimit                                   =0;

DWORD_PTR Flying_baseAddressOffset              = 0x03625870;                                   //����״̬
std::vector<DWORD> Flying_offsets               = { 0x8, 0x110, 0x280, 0x168 };
DWORD_PTR Flying_finalAddress;
int Flying                                      = 0;

DWORD_PTR Unlimitedpower_baseAddressOffset      = 0x03676480;                                   //�����ص���
std::vector<DWORD> Unlimitedpower_offsets       = { 0x30, 0x2B0, 0xE30, 0xA90 };
DWORD_PTR Unlimitedpower_finalAddress;
int Unlimitedpower                              = 0;

/// <summary>
/// �����������
/// </summary>
DWORD_PTR Zpos_baseAddressOffset                = 0x03625880;									//Zpos ���� Float
std::vector<DWORD> Zpos_offsets                 = { 0x0, 0x110, 0x130, 0x1D8};
DWORD_PTR Zpos_finalAddress;
float Zpos                                        =0.0;

DWORD_PTR Xpos_baseAddressOffset                = 0x03625880;									//Xpos ���� Float
std::vector<DWORD> Xpos_offsets                 = { 0x0, 0x110, 0x130, 0x1D4 };
DWORD_PTR Xpos_finalAddress;
float Xpos                                        =0.0;

DWORD_PTR Ypos_baseAddressOffset                = 0x03625880;									//Ypos ���� Float
std::vector<DWORD> Ypos_offsets                 = { 0x0, 0x110, 0x130, 0x1D0 };
DWORD_PTR Ypos_finalAddress;
float Ypos                                        =0.0;


/// <summary>
/// ���µ�Դ
/// </summary>
DWORD_PTR witch_BaseAddress                     = 0x03267D40;									//���� Ů�װ�����˿	�����Դ 
std::vector<DWORD> witch_offsets                = { 0x0, 0x20, 0xE8, 0x3F0, 0x294 };
DWORD_PTR witch_finalAddress;
int witch                                       =0;

DWORD_PTR Joey_BaseAddress                      = 0x03267D40;									//���� ����			�����Դ
std::vector<DWORD> Joey_offsets                 = { 0x0, 0x20, 0xE8, 0x3E0, 0x294 };
DWORD_PTR Joey_finalAddress;
int Joey                                        =0;

DWORD_PTR Karen_BaseAddress                     = 0x03267D40;									//���� ����			�����Դ
std::vector<DWORD> Karen_offsets                = { 0x0, 0x20, 0xE8, 0x3D8, 0x294 };
DWORD_PTR Karen_finalAddress;
int Karen                                       =0;

DWORD_PTR Quinn_BaseAddress                     = 0x03267D40;									//���� ����			�����Դ
std::vector<DWORD> Quinn_offsets                = { 0x0, 0x20, 0xE8, 0x3E8, 0x294 };
DWORD_PTR Quinn_finalAddress;
int Quinn                                       =0;

DWORD_PTR Kit_BaseAddress                       = 0x03267D40;									//���� ����			�����Դ
std::vector<DWORD> Kit_offsets                  = { 0x0, 0x20, 0xE8, 0x3C0, 0x294 };
DWORD_PTR Kit_finalAddress;
int Kit                                         =0;

DWORD_PTR Amelia_BaseAddress                    = 0x03267D40;									//���� ��������		�����Դ
std::vector<DWORD> Amelia_offsets               = { 0x0, 0x20, 0xE8, 0x3D0, 0x294 };
DWORD_PTR Amelia_finalAddress;
int Amelia                                      =0;

DWORD_PTR Bouli_BaseAddress                     = 0x03267D40;									//���� ����			�����Դ
std::vector<DWORD> Bouli_offsets                = { 0x0, 0x20, 0xE8, 0x3C8, 0x294 };
DWORD_PTR Bouli_finalAddress;
int Bouli                                       =0;

DWORD_PTR Venusin_BaseAddress                   = 0x03267D40;									//���� ά����		�����Դ
std::vector<DWORD> Venusin_offsets              = { 0x0, 0x20, 0xE8, 0x3B8, 0x294 };
DWORD_PTR Venusin_finalAddress;
int Venusin                                     =0;

DWORD_PTR incinerator_BaseAddress               = 0x035AEDE8;								    //����¯��Դ
std::vector<DWORD> incinerator_offsets          = { 0x30, 0x98, 0x10, 0xCC0, 0x294 };
DWORD_PTR incinerator_finalAddress;
int incinerator                                 =0;

DWORD_PTR unit1_BaseAddress                     = 0x03267D40;									//С��Ԫ��Դ1
std::vector<DWORD> unit1_offsets                = { 0x0, 0x20, 0xE8, 0x360, 0x294 };
DWORD_PTR unit1_finalAddress;
int unit1;

DWORD_PTR unit2_BaseAddress                     = 0x03267D40;									//С��Ԫ��Դ2
std::vector<DWORD> unit2_offsets                = { 0x0, 0x20, 0xE8, 0x368, 0x294 };
DWORD_PTR unit2_finalAddress;
int unit2                                       =0;


/// <summary>
/// ��¥��Դ
/// </summary>
DWORD_PTR hall_BaseAddress                      = 0x0326A080;									//������Դ
std::vector<DWORD> hall_offsets                 = { 0x0, 0x1F8, 0x4E0, 0x20, 0x294 };
DWORD_PTR hall_finalAddress;
int hall                                        =0;

DWORD_PTR toilet_BaseAddress                    = 0x0326A080;									//�������Դ
std::vector<DWORD> toilet_offsets               = { 0x0, 0x1F8, 0x4C0, 0x20, 0x294 };
DWORD_PTR toilet_finalAddress;
int toilet                                      =0;

DWORD_PTR diversion_BaseAddress                 = 0x0326A080;									//���ַ���Դ
std::vector<DWORD> diversion_offsets            = { 0x0, 0x1F8, 0x4F0, 0x20, 0x294 };
DWORD_PTR diversion_finalAddress;
int diversion                                   =0;

DWORD_PTR Officearea1_BaseAddress               = 0x0326A080;									//�칫��1��Դ
std::vector<DWORD> Officearea1_offsets          = { 0x0, 0x1F8, 0x578, 0x20, 0x294 };
DWORD_PTR Officearea1_finalAddress;
int Officearea1                                 =0;

DWORD_PTR Officearea2_BaseAddress               = 0x0326A080;									//�칫��2��Դ
std::vector<DWORD> Officearea2_offsets          = { 0x0, 0x1F8, 0x520, 0x20, 0x294 };
DWORD_PTR Officearea2_finalAddress;
int Officearea2                                 =0;

DWORD_PTR Officearea3_BaseAddress               = 0x0326A080;									//�칫��3��Դ
std::vector<DWORD> Officearea3_offsets          = { 0x0, 0x1F8, 0x540, 0x20, 0x294 };
DWORD_PTR Officearea3_finalAddress;
int Officearea3                                 =0;

DWORD_PTR warehouse_BaseAddress                 = 0x0326A080;									//�ֿ��Դ
std::vector<DWORD> warehouse_offsets            = { 0x0, 0x1F8, 0x570, 0x20, 0x294 };
DWORD_PTR warehouse_finalAddress;
int warehouse                                   =0;

DWORD_PTR Ghosthouse_BaseAddress                = 0x0326A080;									//����Դ
std::vector<DWORD> Ghosthouse_offsets           = { 0x0, 0x1F8, 0x560, 0x20, 0x294 };
DWORD_PTR Ghosthouse_finalAddress;
int Ghosthouse                                  =0;

DWORD_PTR Undergroundpassage_BaseAddress        = 0x0326A080;								    //����ͨ����Դ
std::vector<DWORD> Undergroundpassage_offsets   = { 0x0, 0x1F8, 0x598, 0x20, 0x294 };
DWORD_PTR Undergroundpassage_finalAddress;
int Undergroundpassage                          =0;

DWORD_PTR cleanchannel_BaseAddress              = 0x0326A080;									//����ͨ����Դ
std::vector<DWORD> cleanchannel_offsets         = { 0x0, 0x1F8, 0x5D8, 0x20, 0x294 };
DWORD_PTR cleanchannel_finalAddress;
int cleanchannel                                =0;




DWORD_PTR GetModuleBaseAddress(DWORD pid, const wchar_t* moduleName) {
    DWORD_PTR baseAddress = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32W moduleEntry;
        moduleEntry.dwSize = sizeof(MODULEENTRY32W);
        if (Module32FirstW(hSnapshot, &moduleEntry)) {
            do {
                if (_wcsicmp(moduleEntry.szModule, moduleName) == 0) {
                    baseAddress = (DWORD_PTR)moduleEntry.modBaseAddr;
                    break;
                }
            } while (Module32NextW(hSnapshot, &moduleEntry));
        }
        CloseHandle(hSnapshot);
    }
    return baseAddress;
}



DWORD_PTR ReadMultiLevelPointer(HANDLE hProcess, DWORD_PTR baseAddress, const std::vector<DWORD>& offsets) {
    DWORD_PTR address = baseAddress;
    for (size_t i = 0; i < offsets.size(); ++i) {
        if (!ReadProcessMemory(hProcess, (BYTE*)address, &address, sizeof(address), nullptr)) {
            std::cerr << "��ȡ�ڴ��ַʧ��: 0x" << std::hex << address << std::endl;
            return 0;
        }
        address += offsets[i];
        std::cout << "�����õ� " << i + 1 << " ��: ��ַ = 0x" << std::hex << address << std::endl;
    }
    return address;
}
