#pragma once
#include <windows.h>

//��ַ
const DWORD BASE_GAME = 0x02582944;   // ��Ϸ��ַ   ��ַ: 55D4A0
const DWORD BASE_TASK = 0x02582CD0;   // �����ַ   ��ַ: 535334
const DWORD BASE_KEYBOARD_HANDLER = 0x0208C0B4;   // �����������ַ   ��ַ: 6B255B
const DWORD BASE_CAMERA = 0x0231A698;   // �������ػ�ַ   ��ַ: 1578C26
const DWORD BASE_LOADING_FLAG = 0x020FA884;   // ���ڹ�ͼ��־��0�����ڹ�ͼ��1:���ڹ�ͼ����   ��ַ: 75C133
const DWORD BASE_CURRENT_MAP_OBJECTS = 0x0208C0F0;   // ��ǰ��ͼ�е����ж��������ַ   ��ַ: 6AD7FD
const DWORD BASE_CURRENT_MAP_OBJECTS2 = 0x0257A028;   // ��ǰ��ͼ�е����ж������2��ַ   ��ַ: 1C1D134
const DWORD BASE_AUCTION = 0x02582C34;   // ���������ݻ�ַ   ��ַ: 46E960
const DWORD BASE_SUPPLY_BOX = 0x0208C168;   // �������ַ   ��ַ: 6AD9D5
//����
const DWORD CALL_VALUE_DECRYPT = 0x0560FA0;   // ����ֵ���ܺ���   ��ַ: 55D4E0
const DWORD CALL_KEYBOARD_EVENT_HANDLE = 0x0172E980;   // ������Ϣ����   ��ַ: 172ED2E
const DWORD CALL_TELESPORT = 0x0935390;   // ˲��CALL   ��ַ: 94D5A3
const DWORD CALL_SEND_PACKET = 0x0697460;   // ����CALL��ȡ��ߵ�ֵ��   ��ַ: 697460
const DWORD CALL_INJURE = 0x01395D40;   // �����˺�CALL   ��ַ: 158269A
const DWORD CALL_COMMON_FUNCTION = 0x01343230;   // ͨ�õ��ú���   ��ַ: 134635C
const DWORD CALL_SWITCH_REGION = 0x013DDB70;   // ˳ͼ   ��ַ: 13FB09F
const DWORD CALL_COLLECTING = 0x05EDD00;   // �ɼ���Ʒ   ��ַ: 61CD98
const DWORD CALL_COLLECTING2 = 0x01BEF910;   // �ɼ���Ʒ2   ��ַ: 5EE9E5
const DWORD CALL_MOVE_INVENTORY_ITEM = 0x05FE660;   // ��������Ʒ����ֿ�   ��ַ: 54772B
const DWORD CALL_GET_OBJECT_IDLE_STATE = 0x0169E3B0;   // ��ȡ������б�ʶ��1�����У�0����æ��   ��ַ: 15AA410
const DWORD CALL_ATTACK = 0x0150C2E0;   // �������CALL��ȡ��ߵ�ֵ��   ��ַ: 150C2E0
const DWORD CALL_GET_GLOBAL_VARIABLE = 0x076EDB0;   // �������ƻ�ȡ��Ϸ�е�ȫ�ֱ���   ��ַ: 441779
const DWORD CALL_GET_ROLE_LIST_INFO = 0x013FC020;   // ��ȡ��ɫ�б���ص�ָ��   ��ַ: 51BED2
//ƫ��
const DWORD OFFSET_ROLE_INFO_1 = 0x0C8;   // ��ǰ����ָ��ƫ��1   ��ַ: 55D4A6
const DWORD OFFSET_ROLE_INFO_2 = 0x028;   // ��ǰ����ָ��ƫ��2(ȡbyte)   ��ַ: 55D4AC
const DWORD OFFSET_ROLE_INFO_3 = 0x0A8;   // ��ǰ����ָ��ƫ��3   ��ַ: 45F1A2
const DWORD OFFSET_ROLE_INFO_4 = 0x0214;   // ��ǰ����ָ��ƫ��4   ��ַ: 62A3B2
const DWORD OFFSET_ROLE_LEVEL = 0x0434;   // ����ȼ�������ֵƫ��   ��ַ: 55D568
const DWORD OFFSET_GET_ROLE_NAME = 0x0B0;   // ��ȡ�������Ƶ�CALL�����HandlerTable��ƫ��   ��ַ: 55D84E
const DWORD OFFSET_ROLE_HP = 0x04DC;   // ����Ѫ��ƫ��   ��ַ: 55DF1C
const DWORD OFFSET_NEARBY_OBJECT = 0x050;   // ��Χ�������ƫ��(ȡbyte)   ��ַ: 9510DB
const DWORD OFFSET_NEARBY_OBJECT_ROOT = 0x09C;   // ��Χ��������ĸ�ƫ��   ��ַ: 929023
const DWORD OFFSET_COOR = 0x060;   // ��������ڶ���ָ���ƫ�ƣ�ȡbyte��   ��ַ: 1C85DA8
const DWORD OFFSET_ROLE_ENDURE = 0x0576;   // �����������   ��ַ: 55D519
const DWORD OFFSET_ROLE_CURHP = 0x04D4;   // ���ﵱǰѪ��   ��ַ: 55D4FA
const DWORD OFFSET_ROLE_CURENDURE = 0x056E;   // ���ﵱǰ����   ��ַ: 55D538
const DWORD OFFSET_KEYBOARD_HANDLER = 0x048;   // ����������ƫ�ƣ�ȡbyte��   ��ַ: 1728035
const DWORD OFFSET_CAREMA_1 = 0x0D0;   // �������ƫ��1   ��ַ: 1578C2C
const DWORD OFFSET_CAREMA_2 = 0x05C;   // �������ƫ��2��ȡbyte��   ��ַ: 1578C32
const DWORD OFFSET_CAREMA_ANGLE = 0x0160;   // ��������ӽ�ƫ��   ��ַ: 14048F1
const DWORD OFFSET_SEND_PACKET_ECX_1 = 0x042F4;   // ����ECXƫ��1   ��ַ: 546A3E
const DWORD OFFSET_SEND_PACKET_ECX_2 = 0x0F8;   // ����ECXƫ��2   ��ַ: 5FD75C
const DWORD OFFSET_SEND_PACKET_ECX_3 = 0x01C;   // ����ECXƫ��3��ȡbyte��   ��ַ: 62EF7B
const DWORD OFFSET_CITY_FLAG_1 = 0x042F4;   // �����ʶƫ��1   ��ַ: 547106
const DWORD OFFSET_CITY_FLAG_2 = 0x0F8;   // �����ʶƫ��2   ��ַ: 5FF63E
const DWORD OFFSET_CITY_FLAG_3 = 0x01C;   // �����ʶƫ��3(ȡbyte)   ��ַ: 62EE87
const DWORD OFFSET_CITY_FLAG_4 = 0x024;   // �����ʶƫ��4(ȡbyte)   ��ַ: 697465
const DWORD OFFSET_CITY_FLAG_5 = 0x088;   // �����ʶƫ��5   ��ַ: 69756B
const DWORD OFFSET_SELECT_COPY = 0x0174;   // ѡ�񸱱�ƫ��   ��ַ: 1396D37
const DWORD OFFSET_ATTACK = 0x01A2A;   // ��ɫ������ƫ��   ��ַ: 55D4CE
const DWORD OFFSET_GET_TELESPORT_PTR = 0x080;   // ��ȡ˲��д�����ݵ�ָ��   ��ַ: 157F69E
const DWORD OFFSET_GET_SWITCH_REGION_ECX = 0x0178;   // ��ȡ˳ͼ��ECX   ��ַ: 150C266
const DWORD OFFSET_CURRENT_MAP_OBJECTS2 = 0x074;   // ��ǰ��ͼ�е����ж������2ƫ�ƣ�ȡBYTE��   ��ַ: 465A84
const DWORD OFFSET_COLLECTING_PARAM_1 = 0x09C;   // �ɼ�CALL�Ĳ���ƫ��1   ��ַ: 465B6E
const DWORD OFFSET_COLLECTING_PARAM_2 = 0x064;   // �ɼ�CALL�Ĳ���ƫ��2(ȡbyte)   ��ַ: 465B74
const DWORD OFFSET_COLLECTING_ACTION = 0x0204C;   // ��ǰ���ڽ��вɼ��Ķ�����Ϣ   ��ַ: 1C452CB
const DWORD OFFSET_GET_OBJECT_DETAIL = 0x025C;   // ���ݶ���ָ���ȡ��������ָ��   ��ַ: 157AEB7
const DWORD OFFSET_CURRENT_MAP_ENTITY_COUNT = 0x0600C0;   // ��ǰ��ͼ�еĶ�������ƫ��   ��ַ: 9289B7
const DWORD OFFSET_CURRENT_MAP_ENTITY_ARRAY = 0x05C;   // ��ǰ��ͼ�еĶ��������׵�ַƫ�ƣ�ȡBYTE��   ��ַ: 9289C6
const DWORD OFFSET_OBJECT_ENG_NAME = 0x0EC;   // ����Ӣ����ƫ��   ��ַ: 92B29A
const DWORD OFFSET_WEAPON = 0x01440;   // ���ﵱǰ�ֳ�������Keyƫ��   ��ַ: 13C042A
const DWORD OFFSET_ROLE_IDLE_STATE_1 = 0x01B80;   // �����Ƿ����ƫ��1   ��ַ: 13E0F9D
const DWORD OFFSET_ROLE_IDLE_STATE_2 = 0x024;   // �����Ƿ����ƫ��2��ȡbyte��   ��ַ: 1572A12
const DWORD OFFSET_ROLE_IDLE_STATE_3 = 0x0135C;   // �����Ƿ����ƫ��3   ��ַ: 1573622
const DWORD OFFSET_ATTACK_PARAM1 = 0x01D90;   // �����������1ƫ��   ��ַ: 13E0FCC
const DWORD OFFSET_ATTACK_PARAM2_1 = 0x0D8;   // �����������2ƫ��1   ��ַ: 152E967
const DWORD OFFSET_ATTACK_PARAM2_2 = 0x031C;   // �����������2ƫ��2   ��ַ: 155E092
const DWORD OFFSET_IS_DEAD = 0x0F4;   // ���������ж�CALL������е�ƫ��   ��ַ: 13C0291
const DWORD OFFSET_ATTACK_PART = 0x048;   // ������λƫ��(ȡbyte)   ��ַ: 138DBDD
const DWORD OFFSET_NO_DELAY_USE_ITEM_PACKET3_PARAM1 = 0x011C;   // ���ӳ�ʹ����Ʒ��3������Ĳ���1ƫ��   ��ַ: 1C4BF58
const DWORD OFFSET_GET_TIMESTAMP = 0x0228;   // ��ȡʱ�������������е�ƫ��   ��ַ: 16C9851
const DWORD OFFSET_GET_COLLECT_ITEM_TYPE = 0x01AC;   // ��ȡ�ɼ������   ��ַ: 465AD5
const DWORD OFFSET_GET_SUPPLY_BOX = 0x0164;   // ��ȡ������ĺ���������е�ƫ��   ��ַ: 63BB54
const DWORD OFFSET_GET_ROLE_LIST = 0x028;   // ��ȡ��ɫ�б�ĺ���������е�ƫ�ƣ�ȡbyte��   ��ַ: 51BEDD
//����
const DWORD SIZE_SALE_ITEM = 0x068;   // �̵���Ʒ��Ϣ�ṹ���С��ȡbyte��   ��ַ: 5164D1
//�ҹ���
const DWORD HOOK_TELESPORT = 0x094D596;   // ˲��Hook��(ȡ��ߵ�ֵ)   ��ַ: 94D596
const DWORD HOOK_INJURE = 0x01582692;   // �˺�������HOOK(ȡ��ߵ�ֵ)   ��ַ: 1582692
const DWORD HOOK_INVINCIBLE = 0x013E3C61;   // ��ǰ��������HOOK(ȡ��ߵ�ֵ)��Nop��6���ֽڿ�ʵ���޵У�   ��ַ: 13E3C61
const DWORD HOOK_SWITCH_REGION = 0x013FB095;   // ˳ͼ�ű�¼��HOOK��   ��ַ: 13FB095