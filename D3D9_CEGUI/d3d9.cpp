#include <windows.h>

#include "d3d9.h"
#include "main.h"
#include "Martin.h"

tDirect3DCreate9 oDirect3DCreate9;

IDirect3D9 *APIENTRY hkDirect3DCreate9(UINT SDKVersion) {
    martin->add_log("---------------------\nStart hkDirect3DCreate9");
    IDirect3D9 *d3dint = oDirect3DCreate9(SDKVersion);
    hkIDirect3D9 *ret = NULL;
    if (d3dint != NULL) {
        ret = new hkIDirect3D9(&d3dint);
        martin->add_log("Direct3DCreate9(%i) succeeded...", SDKVersion);
        martin->add_log("Hooked Direct3D9 interface: 0x%x -> 0x%x", ret->m_pD3Dint, ret);
    } else
        martin->add_log("Direct3DCreate9(%i) failed...", SDKVersion);
    martin->add_log("---------------------\n");
    return ret;
}