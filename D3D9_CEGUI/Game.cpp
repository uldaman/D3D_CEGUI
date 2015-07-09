#include "GlobalVariable.h"
#include "Game.h"
#include "main.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/String.h"


#include <iostream>
#include <CEGUI/RendererModules/Direct3D9/Renderer.h>
#include <CEGUI/InputEvent.h>
#include "Martin.h"
#include "Quest.h"
#include "LuaAPI.h"
#include <process.h>
#include "DefMessage.h"
#include "Role.h"
#include "NearObject.h"
#include "BrushZones.h"
#include "DataType.h"
#include "Interface.h"
#include <tlhelp32.h>

CGame theApp;

CGame::CGame(void) {
    m_OrgWndProc = 0;
    m_hGWnd = NULL;
}

CGame::~CGame(void) {

}

LRESULT CGame::CEGUIWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
    case WM_SOCKET:
        SOCKET s = (SOCKET)wParam;
        WORD error = WSAGETSELECTERROR(lParam);
        if (error) {
            martin->Debug("connect 连接服务器失败: %d", error);
            ::closesocket(s);
            ExitProcess(0);
        }

        switch (WSAGETSELECTEVENT(lParam)) {
        case FD_CONNECT:
            // OnConnect(s); 表示连接上, 这里可以用来初始化 cegui
            martin->Debug("connect 连接服务器成功");
            break;
        case FD_READ:
            // 读取到数据, 这里可以用来接受服务端操作
            break;
        case FD_CLOSE:
            ::closesocket(s);
            ExitProcess(0);
            break;
        }
        break;
    }

    MesageMapping(hwnd, message, wParam, lParam); // 处理自定义消息

    static bool s_mouseInWindow = false;

    if (m_bInit) {
        switch (message) {
        case WM_MOUSEMOVE:
            //ShowCursor(true);
            if (!s_mouseInWindow) {
                s_mouseInWindow = true;
                ShowCursor(false);
            }

            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition((float)(LOWORD(lParam)), (float)(HIWORD(lParam)))) {
                return 0;
            }
            break;

        case WM_MOUSELEAVE:
            if (s_mouseInWindow) {
                s_mouseInWindow = false;
                ShowCursor(true);
            }
            break;

        case WM_NCMOUSEMOVE:
            if (s_mouseInWindow) {
                s_mouseInWindow = false;
                ShowCursor(true);
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

bool GetProcessOf(const char exename[], PROCESSENTRY32 *process);

void CGame::initGui() {
    CEGUI::Direct3D9Renderer::bootstrapSystem(theApp.m_pDevice);
    //-----------------------------------------------------------
    //    此行等同于下面两行, 即初始化 Direct3D9Renderer
    //    Direct3D9Renderer *myRenderer = &CEGUI::Direct3D9Renderer::create(pDevice);
    //    System::create(*myRenderer);
    //-----------------------------------------------------------

    /////////////////////////////////////////////////////////////////////////
    //    设置默认资源路径
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

    martin->add_log("设置默认资源路径");

    ///////////////////////////////////////////////////////////////////////////
    ////    设置使用的缺省资源
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
    martin->add_log("设置使用的缺省资源");

    ///////////////////////////////////////////////////////////////////////
    //    加载方案
    ///////////////////////////////////////////////////////////////////////
    // 加载主题
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    // 设置字体
    CEGUI::Font& defaultFont = CEGUI::FontManager::getSingleton().createFromFile("STXINGKA.font");
    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(&defaultFont);

    // 设置鼠标, hook 游戏 d3d 时不用设置, 直接使用游戏的鼠标模型
    //System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow"); 

    // 得到窗口管理器
    CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
    martin->add_log("加载方案");

    /////////////////////////////////////////////////////////////////////////
    //    开始绘图
    /////////////////////////////////////////////////////////////////////////
    // 得到根窗口, 即画布
    m_root = static_cast<CEGUI::DefaultWindow*>(winMgr.loadLayoutFromFile("monster.layout"));
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_root);

    // 得到主窗口
    m_mainWnd = static_cast<CEGUI::FrameWindow*>(m_root->getChild("Demo"));
    m_mainWnd->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
        CEGUI::Event::Subscriber(&CGame::onEventHome, this));

    // 得到物品窗口
    m_itemWnd = static_cast<CEGUI::FrameWindow*>(m_root->getChild("Item_Wnd"));
    m_itemWnd->hide();
    m_itemWnd->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
        CEGUI::Event::Subscriber(&CGame::onEventCloseClicked, this));

    m_itemBtn = static_cast<CEGUI::PushButton*>(m_mainWnd->getChild("Item_Btn"));
    m_itemBtn->setText(AToUtf8("物品设置"));
    m_itemBtn->subscribeEvent(CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&CGame::onSkillBtn, this));

    m_questBtn = static_cast<CEGUI::PushButton*>(m_mainWnd->getChild("Quest_Btn"));
    m_questBtn->setText(AToUtf8("自动主线"));
    m_questBtn->subscribeEvent(CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&CGame::onQuestBtn, this));

    martin->add_log("\n---------------------\n全部加载完毕...\n---------------------\n");
    m_bInit = true;

    // 以下为非 CEGUI 操作
    martin->ModuleHide(GetModuleHandle("D3D9_CEGUI.dll")); // 隐藏 DLL
    AddLuaFunction(); // 注册 Lua 函数
    CBrushZones zone;
    zone.initZonesInfo();
    CRole::CatInvincible();
    CRole::initAllItems();
    //PROCESSENTRY32 pe32;
    //if (!GetProcessOf("CeguiInject.exe", &pe32)) {
    //    ExitProcess(0);
    
    if (GetWgPath() == false) {
        ExitProcess(0);
    }
}

bool CGame::GetWgPath() {
    DWORD pid = NULL;
    HWND h = ::FindWindow(NULL, "怪物猎人Online$");
    if (h == NULL) {
        return false;
    }
    DWORD tid = GetWindowThreadProcessId(h, &pid);
    if (pid == NULL) {
        CloseHandle(h);
        return false;
    }

    MODULEENTRY32 lpme;
    lpme.dwSize = sizeof(MODULEENTRY32);
    HANDLE hModuleShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (Module32First(hModuleShot, &lpme)) {
        g_strServerExePath = lpme.szExePath;
        int nPos = g_strServerExePath.find_last_of('\\');
        if (std::string::npos != nPos) {
            g_strServerExePath = g_strServerExePath.substr(0, nPos);
        }
    }

    CloseHandle(hModuleShot);
    CloseHandle(h);
    return true;
}

//bool GetProcessOf(const char exename[], PROCESSENTRY32 *process) {
//    process->dwSize = sizeof(PROCESSENTRY32);
//    HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//
//    if (Process32First(handle, process)) {
//        do {
//            if (lstrcmp(process->szExeFile, exename) == 0) {
//                MODULEENTRY32 lpme;
//                lpme.dwSize = sizeof(MODULEENTRY32);
//                HANDLE hModuleShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process->th32ProcessID);
//                if (Module32First(hModuleShot, &lpme)) {
//                    g_strServerExePath = lpme.szExePath;
//                    int nPos = g_strServerExePath.find_last_of('\\');
//                    if (std::string::npos != nPos) {
//                        g_strServerExePath = g_strServerExePath.substr(0, nPos);
//                    }
//                }
//                CloseHandle(hModuleShot);
//                CloseHandle(handle);
//                return true;
//            }
//        } while (Process32Next(handle, process));
//    }
//
//    CloseHandle(handle);
//    return false;
//}

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
    //    上面代码是为了测试是不是在主线程执行的, 结果是 while 会
    //    导致整个游戏卡主, 应该是主线程
    /////////////////////////////////////////////////////////////////////////


    // 遍历任务
    //CQuest quest;

    //quest.initUnCompleteQuest();
    //martin->add_log("\n---------------------\n当前任务...\n---------------------\n");
    //for (auto& v : quest.m_unComplete_quest) {
    //    martin->Debug("任务名: %s -- ID: %d -- 类别: %s -- 状态: %s -- 交任务NPC: %s"
    //        , v.strQuestName.c_str()
    //        , v.nQuestID
    //        , v.strQuestType.c_str()
    //        , v.strQuestStatus.c_str());
    //}

    //quest.initCompleteQuest();
    //martin->add_log("\n---------------------\n已完成任务...\n---------------------\n");
    //for (auto& v : quest.m_complete_quest) {
    //    martin->Debug("任务名: %s -- ID: %d -- 类别: %s -- 状态: %s"
    //        , v.strQuestName.c_str()
    //        , v.nQuestID
    //        , v.strQuestType.c_str()
    //        , v.strQuestStatus.c_str());
    //}

    //quest.initQuestTable();
    //martin->add_log("\n---------------------\n所有主线任务...\n---------------------\n");
    //for (auto& v : quest.m_questTable_quest) {
    //    martin->Debug("任务名: %s -- ID: %d -- 大章: %s -- 小节: %s"
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
