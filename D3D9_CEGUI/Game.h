#pragma once
#include <windows.h>
#include <d3d9.h>
#include <CEGUI\GUIContext.h>
#include "main.h"
#include <CEGUI\Window.h>

class CGame {
public:
    CGame(void);
    ~CGame(void);

    LONG m_OrgWndProc = 0;
    HWND m_hGWnd = NULL;
    LPDIRECT3DDEVICE9 m_pDevice = nullptr;
    bool m_bInit = false;

    LRESULT CEGUIWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);

    void initGui();
    CEGUI::utf8* AToUtf8(const char* pMbcs);

    CEGUI::DefaultWindow* m_root;
    CEGUI::FrameWindow* m_mainWnd;
    CEGUI::FrameWindow* m_itemWnd;
    CEGUI::PushButton* m_itemBtn;
    CEGUI::PushButton* m_questBtn;
    
    bool onSkillBtn(const CEGUI::EventArgs& args);
    bool onEventCloseClicked(const CEGUI::EventArgs &args);
    bool onEventHome(const CEGUI::EventArgs &args);
    bool onQuestBtn(const CEGUI::EventArgs& args);
};

extern CGame theApp;