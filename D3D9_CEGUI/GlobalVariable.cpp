#include "GlobalVariable.h"
#include "Martin.h"
#include "Base.h"


cLua*                   g_pClua = new cLua;
HANDLE                  g_hLuaThread = NULL;    // ִ�нű��� Lua �߳̾��
BOOL                    g_isWork = FALSE;
std::string             g_strEventHandle = "";

std::string BossName[] = { "������", "����", "������", "����", "�����", "β��Ы", "ѩʨ����", \
"һ����", "������", "�϶���", "������з", "ɳ����", "�����", "����", "��ë����", "������з", \
"����", "ɳ����", "������", "������", "�ƻ���", "��ë����", "ɳ����", "�����", "��������", \
"��������", "��������", "��Ұ����", "Ұ����", "������", "������", "������", "" };