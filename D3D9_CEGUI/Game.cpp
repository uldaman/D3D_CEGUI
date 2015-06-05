#include "Game.h"
#include "main.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/String.h"


#include <iostream>
#include <CEGUI/RendererModules/Direct3D9/Renderer.h>
#include <CEGUI/InputEvent.h>
#include "Martin.h"
#include "Quest.h"
#include "GlobalVariable.h"
#include "LuaAPI.h"
#include <process.h>
#include "DefMessage.h"
#include "Role.h"
#include "NearObject.h"
#include "BrushZones.h"

CGame theApp;

CGame::CGame(void) {
    m_OrgWndProc = 0;
    m_hGWnd = NULL;
}

CGame::~CGame(void) {

}

LRESULT CGame::CEGUIWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static CQuest quest;
    static CNearObject nearObj;
    static CBrushZones zone;

    switch (message) {
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_HOME:
            if (m_bInit) {
                if (m_root->isVisible()) {
                    m_root->setVisible(false);
                } else {
                    m_root->setVisible(true);
                }
            } else {
                initGui();
            }
            break;
        }
        break;
    case WM_GET_CURRENT_QUEST:
        quest.initUnCompleteQuest();
        for (auto& v : quest.m_unComplete_quest) {
            if (v.strQuestType == "����") {
                *(std::string*)wParam = v.strQuestName;
                break;
            }
        }
        break;
    case WM_GET_QUEST_TABLE:
        *(std::string*)wParam = quest.GetQuestTable();
        break;
    case WM_IS_QUEST_COMPLETE:
        quest.initUnCompleteQuest();
        for (auto& v : quest.m_unComplete_quest) {
            if (v.strQuestType == "����" && *(std::string*)wParam == v.strQuestName) {
                if (v.strQuestStatus == "���") {
                    *(int*)lParam = 1;
                }
                break;
            }
        }
        break;
    case WM_WHERE_ROLE:
        *(int*)wParam = CRole::WhereIsRole();
        break;
    case WM_COMPLETE_QUEST:
        quest.initUnCompleteQuest();
        for (auto& v : quest.m_unComplete_quest) {
            if (v.strQuestType == "����" && *(std::string*)wParam == v.strQuestName) {
                if (v.strQuestStatus == "���") {
                    // ������
                    // 1. �� NPC
                    nearObj.initNear();
                    for (auto& w : nearObj.m_near_object) {
                        if (w.strNpcName == *(std::string*)lParam) { // �ҵ� NPC
                            nearObj.Interactive(w.nNpcID);
                            Sleep(50);
                            break;
                        }
                    }
                    // 2. ������
                    quest.CompleteQuest(v.nQuestID);
                }
                break;
            }
        }
        break;
    case WM_ACCEPT_QUEST:
        quest.initQuestTable();
        for (auto& v : quest.m_questTable_quest) {
            if (*(std::string*)wParam == v.strQuestName) {
                    // ������
                    // 1. �� NPC
                    nearObj.initNear();
                    for (auto& w : nearObj.m_near_object) {
                        if (w.strNpcName == *(std::string*)lParam) { // �ҵ� NPC
                            nearObj.Interactive(w.nNpcID);
                            Sleep(50);
                            break;
                        }
                    }
                    // 2. ������
                    quest.AcceptQuest(v.nQuestID);
                break;
            }
        }
        break;
    case WM_INTERACTIVE_QUEST:
        quest.initUnCompleteQuest();
        for (auto& v : quest.m_unComplete_quest) {
            if (v.strQuestType == "����" && *(std::string*)wParam == v.strQuestName) {
                // ����Ի�
                // 1. �� NPC
                nearObj.initNear();
                for (auto& w : nearObj.m_near_object) {
                    if (w.strNpcName == *(std::string*)lParam) { // �ҵ� NPC
                        nearObj.Interactive(w.nNpcID);
                        Sleep(50);
                        break;
                    }
                }
                // 2. ����Ի�
                quest.InteractiveQuest(v.nQuestID);
                break;
            }
        }
        break;
    case WM_��������̽�:
        quest.��������̽�();
        break;
    case WM_CITY_FLY:
        CRole::CityFly(*(std::string*)wParam);
        break;
    case WM_CHOOSE_FB:
        zone.ChooseFB((int)wParam);
        break;
    case WM_START_FB:
        zone.StartFB((int)wParam);
        break;
    case WM_INTO_FB:
        zone.IntoFB();
        break;
    case WM_UPDATA_BOSS:
        ((CBrushZones*)wParam)->initBoss();
        break;
    case WM_ROLE_ROOM:
        *(int*)wParam = CRole::GetRoleRoom();
        break;
    case WM_BOSS_ROOM:
        zone.initBoss();
        *(int*)wParam = zone.m_nBossRoom;
        break;
    case WM_GET_ZONE:
        *(std::string*)wParam = CRole::GetRoleZone();
        break;
    case WM_GET_MAP:
        *(std::string*)wParam = CRole::GetRoleMap();
        break;
    case WM_GOTO_BOSS:
        zone.GotoBoss();
        break;
    case WM_BY_MAP:
        CRole::ByMap((char*)wParam);
        break;
    case WM_TURN:
        CRole::Turn();
        break;
    case WM_ATTACK_PACK:
        CRole::Attack_Pack((int)wParam);
        break;
    case WM_FORWARD:
        CRole::GoForward(); // ǰ����
        break;
    case WM_STOP:
        CRole::Stop();
        break;
    case WM_ATTACK:
        CRole::Attack();
        break;
    case WM_HAVE_WEAPON:
        *(int*)wParam = CRole::HaveWeapon();
        break;
    case WM_WEAPON:
        CRole::Weapon();
        break;
    }

    if (m_bInit) {
        switch (message) {
        case WM_MOUSEMOVE:
            //ShowCursor(true);
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition((float)(LOWORD(lParam)), (float)(HIWORD(lParam)))) {
                return 0;
            }
            break;

        case WM_LBUTTONDOWN:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton)) {
                return 0;
            }
            break;

        case WM_LBUTTONUP:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton)) {
                return 0;
            }
            break;

        case WM_RBUTTONDOWN:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton)) {
                return 0;
            }
            break;

        case WM_RBUTTONUP:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton)) {
                return 0;
            }
            break;

        case WM_MBUTTONDOWN:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton)) {
                return 0;
            }
            break;

        case WM_MBUTTONUP:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton)) {
                return 0;
            }
            break;
        case WM_LBUTTONDBLCLK:
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton)) {
                return 0;
            }
            break;

        case WM_KEYDOWN:
            //if (CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(ToCEGUISanCode(wParam, lParam))) {
            //    return 0;
            //}
            break;
        }
    }
    return 1;
}

CEGUI::utf8* CGame::AToUtf8(const char* pMbcs) {
    static CEGUI::utf8 g_buf[1024] = { 0 };
    static  wchar_t g_Unicode[1024] = { 0 };
    memset(g_Unicode, 0, sizeof(g_Unicode));
    memset(g_buf, 0, sizeof(g_buf));
    MultiByteToWideChar(CP_ACP, 0, pMbcs, strlen(pMbcs), g_Unicode, 1024);
    WideCharToMultiByte(CP_UTF8, 0, g_Unicode, wcslen(g_Unicode), (char*)g_buf, 1024, 0, 0);
    return g_buf;
}

void CGame::initGui() {
    CEGUI::Direct3D9Renderer::bootstrapSystem(theApp.m_pDevice);
    //-----------------------------------------------------------
    //    ���е�ͬ����������, ����ʼ�� Direct3D9Renderer
    //    Direct3D9Renderer *myRenderer = &CEGUI::Direct3D9Renderer::create(pDevice);
    //    System::create(*myRenderer);
    //-----------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    //    ����Ĭ����Դ·��
    /////////////////////////////////////////////////////////////////////////
    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*> (CEGUI::System::getSingleton().getResourceProvider());
    std::string strPath = martin->GetModulePath(NULL);
    rp->setResourceGroupDirectory("schemes", AToUtf8((strPath + "\\datafiles\\schemes").c_str()));
    rp->setResourceGroupDirectory("imagesets", AToUtf8((strPath + "\\datafiles\\imagesets").c_str()));
    rp->setResourceGroupDirectory("fonts", AToUtf8((strPath + "\\datafiles\\fonts").c_str()));
    rp->setResourceGroupDirectory("layouts", AToUtf8((strPath + "\\datafiles\\layouts").c_str()));
    rp->setResourceGroupDirectory("looknfeels", AToUtf8((strPath + "\\datafiles\\looknfeel").c_str()));
    rp->setResourceGroupDirectory("lua_scripts", AToUtf8((strPath + "\\datafiles\\lua_scripts").c_str()));
    rp->setResourceGroupDirectory("schemas", AToUtf8((strPath + "\\datafiles\\xml_schemas").c_str()));
    rp->setResourceGroupDirectory("animations", AToUtf8((strPath + "\\datafiles\\animations").c_str()));

    martin->add_log("����Ĭ����Դ·��");

    ///////////////////////////////////////////////////////////////////////////
    ////    ����ʹ�õ�ȱʡ��Դ
    ///////////////////////////////////////////////////////////////////////////
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup")) {
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");
    }
    martin->add_log("����ʹ�õ�ȱʡ��Դ");

    ///////////////////////////////////////////////////////////////////////
    //    ���ط���
    ///////////////////////////////////////////////////////////////////////
    // ��������
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    // ��������
    CEGUI::Font& defaultFont = CEGUI::FontManager::getSingleton().createFromFile("STXINGKA.font");
    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(&defaultFont);

    // �������, hook ��Ϸ d3d ʱ��������, ֱ��ʹ����Ϸ�����ģ��
    //System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow"); 

    // �õ����ڹ�����
    CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
    martin->add_log("���ط���");

    /////////////////////////////////////////////////////////////////////////
    //    ��ʼ��ͼ
    /////////////////////////////////////////////////////////////////////////
    // �õ�������, ������
    m_root = static_cast<CEGUI::DefaultWindow*>(winMgr.loadLayoutFromFile("monster.layout"));
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_root);

    // �õ�������
    m_mainWnd = static_cast<CEGUI::FrameWindow*>(m_root->getChild("Demo"));
    m_mainWnd->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
        CEGUI::Event::Subscriber(&CGame::onEventHome, this));

    // �õ���Ʒ����
    m_itemWnd = static_cast<CEGUI::FrameWindow*>(m_root->getChild("Item_Wnd"));
    m_itemWnd->hide();
    m_itemWnd->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
        CEGUI::Event::Subscriber(&CGame::onEventCloseClicked, this));

    m_itemBtn = static_cast<CEGUI::PushButton*>(m_mainWnd->getChild("Item_Btn"));
    m_itemBtn->setText(AToUtf8("��Ʒ����"));
    m_itemBtn->subscribeEvent(CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&CGame::onSkillBtn, this));

    m_questBtn = static_cast<CEGUI::PushButton*>(m_mainWnd->getChild("Quest_Btn"));
    m_questBtn->setText(AToUtf8("�Զ�����"));
    m_questBtn->subscribeEvent(CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&CGame::onQuestBtn, this));

    martin->add_log("\n---------------------\nȫ���������...\n---------------------\n");
    m_bInit = true;

    // ����Ϊ�� CEGUI ����
    martin->ModuleHide(GetModuleHandle("D3D9_CEGUI.dll")); // ���� DLL
    AddLuaFunction(); // ע�� Lua ����
    CBrushZones zone;
    zone.initZonesInfo();
}

bool CGame::onSkillBtn(const CEGUI::EventArgs& args) {
    if (m_itemWnd->isVisible()) {
        m_itemWnd->setVisible(false);
    } else {
        m_itemWnd->setVisible(true);
    }
    return true;
}

bool CGame::onEventCloseClicked(const CEGUI::EventArgs &args) {
    //m_itemWnd->hide();
    static_cast<const CEGUI::WindowEventArgs&>(args).window->hide();
    return true;
}

bool CGame::onEventHome(const CEGUI::EventArgs &args) {
    m_root->setVisible(false);
    return true;
}

bool CGame::onQuestBtn(const CEGUI::EventArgs& args) {
    //while (true) { // 
    //    Sleep(10);
    //}
    /////////////////////////////////////////////////////////////////////////
    //    ���������Ϊ�˲����ǲ��������߳�ִ�е�, ����� while ��
    //    ����������Ϸ����, Ӧ�������߳�
    /////////////////////////////////////////////////////////////////////////


    // ��������
    //CQuest quest;

    //quest.initUnCompleteQuest();
    //martin->add_log("\n---------------------\n��ǰ����...\n---------------------\n");
    //for (auto& v : quest.m_unComplete_quest) {
    //    martin->Debug("������: %s -- ID: %d -- ���: %s -- ״̬: %s -- ������NPC: %s"
    //        , v.strQuestName.c_str()
    //        , v.nQuestID
    //        , v.strQuestType.c_str()
    //        , v.strQuestStatus.c_str());
    //}

    //quest.initCompleteQuest();
    //martin->add_log("\n---------------------\n���������...\n---------------------\n");
    //for (auto& v : quest.m_complete_quest) {
    //    martin->Debug("������: %s -- ID: %d -- ���: %s -- ״̬: %s"
    //        , v.strQuestName.c_str()
    //        , v.nQuestID
    //        , v.strQuestType.c_str()
    //        , v.strQuestStatus.c_str());
    //}

    //quest.initQuestTable();
    //martin->add_log("\n---------------------\n������������...\n---------------------\n");
    //for (auto& v : quest.m_questTable_quest) {
    //    martin->Debug("������: %s -- ID: %d -- ����: %s -- С��: %s"
    //        , v.strQuestName.c_str()
    //        , v.nQuestID
    //        , v.strChapter.c_str()
    //        , v.strSection.c_str());
    //}

    if (g_hLuaThread == NULL) {
        g_isWork = TRUE;
        g_hLuaThread = (HANDLE)_beginthreadex(NULL, 0, ThreadAutoMatic, NULL, 0, NULL);
    } else {
        g_isWork = FALSE;
    }

    return true;
}
