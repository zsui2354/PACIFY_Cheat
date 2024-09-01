//#pragma once
#ifndef ADDRESS_OFFSET_H
#define ADDRESS_OFFSET_H 

#include <Windows.h>
#include <vector>
#include <tlhelp32.h>



extern DWORD_PTR roomLimit_baseAddressOffset;				//��������
extern std::vector<DWORD> roomLimit_offsets;
extern DWORD_PTR roomLimit_finalAddress;
extern int roomLimit;

extern DWORD_PTR Flying_baseAddressOffset;                  //����״̬ 1���� 5����
extern std::vector<DWORD> Flying_offsets;
extern DWORD_PTR Flying_finalAddress;
extern int Flying;

extern DWORD_PTR Unlimitedpower_baseAddressOffset;          //�����ص���
extern std::vector<DWORD> Unlimitedpower_offsets;
extern DWORD_PTR Unlimitedpower_finalAddress;
extern int Unlimitedpower;

extern DWORD_PTR Zpos_baseAddressOffset;					//Zpos ����
extern std::vector<DWORD> Zpos_offsets;
extern DWORD_PTR Zpos_finalAddress;
extern float Zpos;

extern DWORD_PTR Xpos_baseAddressOffset;					//Xpos ����
extern std::vector<DWORD> Xpos_offsets;
extern DWORD_PTR Xpos_finalAddress;
extern float Xpos;

extern DWORD_PTR Ypos_baseAddressOffset;					//Ypos ����
extern std::vector<DWORD> Ypos_offsets;
extern DWORD_PTR Ypos_finalAddress;
extern float Ypos;

extern DWORD_PTR witch_BaseAddress;							//���� Ů�װ�����˿	�����Դ 
extern std::vector<DWORD> witch_offsets;
extern DWORD_PTR witch_finalAddress;
extern int witch;

extern DWORD_PTR Joey_BaseAddress;							//���� ����			�����Դ
extern std::vector<DWORD> Joey_offsets;
extern DWORD_PTR Joey_finalAddress;
extern int Joey;

extern DWORD_PTR Karen_BaseAddress;							//���� ����			�����Դ
extern std::vector<DWORD> Karen_offsets;
extern DWORD_PTR Karen_finalAddress;
extern int Karen;

extern DWORD_PTR Quinn_BaseAddress;							//���� ����			�����Դ
extern std::vector<DWORD> Quinn_offsets;
extern DWORD_PTR Quinn_finalAddress;
extern int Quinn;

extern DWORD_PTR Kit_BaseAddress;							//���� ����			�����Դ
extern std::vector<DWORD> Kit_offsets;
extern DWORD_PTR Kit_finalAddress;
extern int Kit;

extern DWORD_PTR Amelia_BaseAddress;						//���� ��������		�����Դ
extern std::vector<DWORD> Amelia_offsets;
extern DWORD_PTR Amelia_finalAddress;
extern int Amelia;

extern DWORD_PTR Bouli_BaseAddress;							//���� ����			�����Դ
extern std::vector<DWORD> Bouli_offsets;
extern DWORD_PTR Bouli_finalAddress;
extern int Bouli;

extern DWORD_PTR Venusin_BaseAddress;						//���� ά����		�����Դ
extern std::vector<DWORD> Venusin_offsets;
extern DWORD_PTR Venusin_finalAddress;
extern int Venusin;

extern DWORD_PTR incinerator_BaseAddress;					//����¯��Դ
extern std::vector<DWORD> incinerator_offsets;
extern DWORD_PTR incinerator_finalAddress;
extern int incinerator;

extern DWORD_PTR unit1_BaseAddress;							//С��Ԫ��Դ1
extern std::vector<DWORD> unit1_offsets;
extern DWORD_PTR unit1_finalAddress;
extern int unit1;

extern DWORD_PTR unit2_BaseAddress;							//С��Ԫ��Դ2
extern std::vector<DWORD> unit2_offsets;
extern DWORD_PTR unit2_finalAddress;
extern int unit2;


	/// <summary>
	/// ��¥��Դ
	/// </summary>
extern DWORD_PTR hall_BaseAddress;							//������Դ
extern std::vector<DWORD> hall_offsets;
extern DWORD_PTR hall_finalAddress;
extern int hall;

extern DWORD_PTR toilet_BaseAddress;						//�������Դ
extern std::vector<DWORD> toilet_offsets;
extern DWORD_PTR toilet_finalAddress;
extern int toilet;

extern DWORD_PTR diversion_BaseAddress;						//���ַ���Դ
extern std::vector<DWORD> diversion_offsets;
extern DWORD_PTR diversion_finalAddress;
extern int diversion;

extern DWORD_PTR Officearea1_BaseAddress;					//�칫��1��Դ
extern std::vector<DWORD> Officearea1_offsets;
extern DWORD_PTR Officearea1_finalAddress;
extern int Officearea1;

extern DWORD_PTR Officearea2_BaseAddress;					//�칫��2��Դ
extern std::vector<DWORD> Officearea2_offsets;
extern DWORD_PTR Officearea2_finalAddress;
extern int Officearea2;

extern DWORD_PTR Officearea3_BaseAddress;					//�칫��3��Դ
extern std::vector<DWORD> Officearea3_offsets;
extern DWORD_PTR Officearea3_finalAddress;
extern int Officearea3;

extern DWORD_PTR warehouse_BaseAddress;						//�ֿ��Դ
extern std::vector<DWORD> warehouse_offsets;
extern DWORD_PTR warehouse_finalAddress;
extern int warehouse;

extern DWORD_PTR Ghosthouse_BaseAddress;					//����Դ
extern std::vector<DWORD> Ghosthouse_offsets;
extern DWORD_PTR Ghosthouse_finalAddress;
extern int Ghosthouse;

extern DWORD_PTR Undergroundpassage_BaseAddress;			//����ͨ����Դ
extern std::vector<DWORD> Undergroundpassage_offsets;
extern DWORD_PTR Undergroundpassage_finalAddress;
extern int Undergroundpassage;

extern DWORD_PTR cleanchannel_BaseAddress;					//����ͨ����Դ
extern std::vector<DWORD> cleanchannel_offsets;
extern DWORD_PTR cleanchannel_finalAddress;
extern int cleanchannel;


extern DWORD_PTR GetModuleBaseAddress(DWORD pid, const wchar_t* moduleName);    // ��ȡģ�����ַ

extern DWORD_PTR ReadMultiLevelPointer(HANDLE hProcess, DWORD_PTR baseAddress, const std::vector<DWORD>& offsets);  // ��ȡ�༶ָ���ֵ

#endif // ADDRESS_OFFSET_H
