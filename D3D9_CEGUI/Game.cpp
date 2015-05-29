#include "Game.h"
#include "main.h"
#include "CEGUI/CEGUI.h"
#include "CEGUI/String.h"


#include <iostream>
#include <CEGUI/RendererModules/Direct3D9/Renderer.h>
#include <CEGUI/InputEvent.h>
#include "Martin.h"

CGame theApp;

CGame::CGame(void) {
    m_OrgWndProc = 0;
    m_hGWnd = NULL;
}

CGame::~CGame(void) {

}

LRESULT CGame::CEGUIWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam) {
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
            }
            break;
        }
        break;
    }
    if (m_bInit) {
        switch (message) {
        case WM_MOUSEMOVE:
            //ShowCursor(true);
            if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition((float)(LOWORD(lparam)), (float)(HIWORD(lparam)))) {
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

void CGame::initGui() {

    //setSupportsDisplayList();

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
    rp->setResourceGroupDirectory("schemes", "E:\\cegui-0.8.4\\datafiles\\schemes");
    rp->setResourceGroupDirectory("imagesets", "E:\\cegui-0.8.4\\datafiles\\imagesets");
    rp->setResourceGroupDirectory("fonts", "E:\\cegui-0.8.4\\datafiles\\fonts");
    rp->setResourceGroupDirectory("layouts", "E:\\cegui-0.8.4\\datafiles\\layouts");
    rp->setResourceGroupDirectory("looknfeels", "E:\\cegui-0.8.4\\datafiles\\looknfeel");
    rp->setResourceGroupDirectory("lua_scripts", "E:\\cegui-0.8.4\\datafiles\\lua_scripts");
    rp->setResourceGroupDirectory("schemas", "E:\\cegui-0.8.4\\datafiles\\xml_schemas");
    rp->setResourceGroupDirectory("animations", "E:\\cegui-0.8.4\\datafiles\\animations");
    add_log("设置默认资源路径");

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
    add_log("设置使用的缺省资源");

    ///////////////////////////////////////////////////////////////////////
    //    加载方案
    ///////////////////////////////////////////////////////////////////////
    // 加载主题
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    // 设置字体
    CEGUI::Font& defaultFont = CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-12.font");
    CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont(&defaultFont);

    // 设置鼠标, hook 游戏 d3d 时不用设置, 直接使用游戏的鼠标模型
    //System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow"); 

    // 得到窗口管理器
    CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
    add_log("加载方案");

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
    m_itemBtn->setText("Set Item");
    m_itemBtn->subscribeEvent(CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&CGame::onSkillBtn, this));

    m_questBtn = static_cast<CEGUI::PushButton*>(m_mainWnd->getChild("Quest_Btn"));
    m_questBtn->subscribeEvent(CEGUI::PushButton::EventClicked,
        CEGUI::Event::Subscriber(&CGame::onQuestBtn, this));


    add_log("Hello World!");
    m_root->setVisible(false);
    martin->ModuleHide(GetModuleHandle("D3D9_CEGUI.dll"));
    m_bInit = true;
}

void CGame::Render() {
    CEGUI::System::getSingleton().renderAllGUIContexts();
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
    // 遍历任务

    return true;
}
