#include "GlobalVariable.h"
#include "Martin.h"
#include "Base.h"


cLua*                   g_pClua = new cLua;
HANDLE                  g_hLuaThread = NULL;    // ִ�нű��� Lua �߳̾��
BOOL                    g_isWork = FALSE;
std::string             g_strEventHandle = "";
std::string             g_strServerExePath = ""; // �����������̨ EXE ·��
int                     g_nCountOfGlowingArticle = 0;
CSocketClient*          g_pSocketClient = nullptr;

std::string BossName[] = { "ս��������", "����Ĵƻ���", "���ֺ�����", "�����������㹽��", "�����㹽��", "������", "����", "������", "����", "�����", "β��Ы", "ѩʨ����", \
"һ����", "������", "�϶���", "������з", "ɳ����", "�����", "����", "��ë����", "������з", \
"����", "ɳ����", "������", "������", "�ƻ���", "��ë����", "ɳ����", "�����", "��������", \
"��������", "��������", "��Ұ����", "Ұ����", "������", "������", "������", "" };