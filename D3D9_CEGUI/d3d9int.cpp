/*	Direct3D9 Interface */

#include <windows.h>
#include "main.h"
#include "d3d9.h"
#include "Game.h"
#include "Martin.h"

HRESULT APIENTRY hkIDirect3D9::QueryInterface(REFIID riid, void **ppvObj) {
    return m_pD3Dint->QueryInterface(riid, ppvObj);
}

ULONG APIENTRY hkIDirect3D9::AddRef() {
    return m_pD3Dint->AddRef();
}

HRESULT APIENTRY hkIDirect3D9::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) {
    return m_pD3Dint->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) {
    return m_pD3Dint->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType, CheckFormat);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) {
    return m_pD3Dint->CheckDeviceFormatConversion(Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels) {
    return m_pD3Dint->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT APIENTRY hkIDirect3D9::CheckDeviceType(UINT Adapter, D3DDEVTYPE CheckType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat, BOOL Windowed) {
    return m_pD3Dint->CheckDeviceType(Adapter, CheckType, DisplayFormat, BackBufferFormat, Windowed);
}

LRESULT CALLBACK FilterWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (theApp.CEGUIWndProc(hWnd, message, wParam, lParam))
        return ::CallWindowProc((WNDPROC)theApp.m_OrgWndProc, hWnd, message, wParam, lParam);
    else
        return 1;
}

HRESULT APIENTRY hkIDirect3D9::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DDevice9 **ppReturnedDeviceInterface) {
    HRESULT hRet = m_pD3Dint->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);
    //static int nCount = 0;
    martin->add_log("CreateDevice ·µ»ØÖµ 0x%X", hRet);
    if (SUCCEEDED(hRet)) {
        theApp.m_pDevice = new hkIDirect3DDevice9(ppReturnedDeviceInterface, pPresentationParameters, this);
        martin->add_log("Hooked Direct3D9 device: 0x%x -> 0x%x", ((hkIDirect3DDevice9*)theApp.m_pDevice)->m_pD3Ddev, theApp.m_pDevice);
        //if (++nCount == 3) {
            //theApp.initGui();
            if (theApp.m_OrgWndProc == 0) {
                theApp.m_hGWnd = hFocusWindow;
                theApp.m_OrgWndProc = ::GetWindowLong(theApp.m_hGWnd, GWL_WNDPROC);
                if (theApp.m_OrgWndProc) {
                    ::SetWindowLong(theApp.m_hGWnd, GWL_WNDPROC, (LONG)&FilterWndProc);
                } else {
                    martin->add_log("GetWindowLong() Failed.");
                    ::ExitProcess(-1);
                }
            }
        //}
    }

    return hRet;
}

HRESULT APIENTRY hkIDirect3D9::EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode) {
    return m_pD3Dint->EnumAdapterModes(Adapter, Format, Mode, pMode);
}

UINT APIENTRY hkIDirect3D9::GetAdapterCount() {
    return m_pD3Dint->GetAdapterCount();
}

HRESULT APIENTRY hkIDirect3D9::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE *pMode) {
    return m_pD3Dint->GetAdapterDisplayMode(Adapter, pMode);
}

HRESULT APIENTRY hkIDirect3D9::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 *pIdentifier) {
    return m_pD3Dint->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT APIENTRY hkIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format) {
    return m_pD3Dint->GetAdapterModeCount(Adapter, Format);
}

HMONITOR APIENTRY hkIDirect3D9::GetAdapterMonitor(UINT Adapter) {
    return m_pD3Dint->GetAdapterMonitor(Adapter);
}

HRESULT APIENTRY hkIDirect3D9::GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9 *pCaps) {
    return m_pD3Dint->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HRESULT APIENTRY hkIDirect3D9::RegisterSoftwareDevice(void *pInitializeFunction) {
    return m_pD3Dint->RegisterSoftwareDevice(pInitializeFunction);
}

ULONG APIENTRY hkIDirect3D9::Release() {
    return m_pD3Dint->Release();
}