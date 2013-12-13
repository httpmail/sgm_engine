#include "dxguiinterface.h"
#include "platformsetting.h"
#include "math.h"

SGM_NAMESPACE_START

class CDXGUIInterface::CDXGUIInterfaceHide{
public:
    CDXGUIInterfaceHide();
    ~CDXGUIInterfaceHide();
    void InitDirect3D(const CPlatformSetting& setting, HWND hWnd);
    INLINE LPDIRECT3DDEVICE9 D3DDevice() const
    {
        return m_pDevice;
    }
    INLINE D3DXMATRIX* OrthoLH() const
    {
        return m_pOrthLH;
    }
protected:
    D3DFORMAT CommonColorFMT2D3DColorFMT(CPlatformSetting::COLOR_FORMAT eColorFMT);
    void SetFModeD3D(const CPlatformSetting &setting, HWND hWnd);
    void SetWModeD3D(HWND hWnd);
    void CreateOrthoLH(FLOAT width, FLOAT height);

private:
    LPDIRECT3D9                 m_pD3D;
    LPDIRECT3DDEVICE9           m_pDevice;
    D3DCAPS9                    m_D3DCaps;
    D3DDISPLAYMODE              m_DisplayMode;
    D3DPRESENT_PARAMETERS       m_D3DParam;
    UINT32                      m_vp;
    D3DXMATRIX*                 m_pOrthLH;
};

CDXGUIInterface::CDXGUIInterfaceHide::CDXGUIInterfaceHide():
m_pD3D(NULL),m_pDevice(NULL),m_vp(0)
{
}

CDXGUIInterface::CDXGUIInterfaceHide::~CDXGUIInterfaceHide()
{
    if(m_pD3D)
    {
        m_pD3D->Release();
        m_pD3D = NULL;
    }
    if(m_pDevice)
    {
        m_pDevice->Release();
        m_pDevice = NULL;
    }
}

D3DFORMAT CDXGUIInterface::CDXGUIInterfaceHide::CommonColorFMT2D3DColorFMT(CPlatformSetting::COLOR_FORMAT eColorFMT)
{
    D3DFORMAT color_format = D3DFMT_UNKNOWN;
    if(eColorFMT == CPlatformSetting::COLORFMT_DEF)
    {
        color_format = m_DisplayMode.Format;
    }
    else
    {
        color_format = m_DisplayMode.Format;
    }
    return color_format;
}

void  CDXGUIInterface::CDXGUIInterfaceHide::SetFModeD3D(const CPlatformSetting& setting, HWND hWnd)
{
    ::ZeroMemory(&m_D3DParam, sizeof(m_D3DParam));

    m_D3DParam.hDeviceWindow                = hWnd;

    m_D3DParam.BackBufferWidth              = setting.Width();
    m_D3DParam.BackBufferHeight             = setting.Height();
    m_D3DParam.BackBufferFormat             = CommonColorFMT2D3DColorFMT(setting.ColorFormat());
    m_D3DParam.BackBufferCount              = 1;
    m_D3DParam.SwapEffect                   = D3DSWAPEFFECT_COPY;
    m_D3DParam.MultiSampleType              = D3DMULTISAMPLE_NONE;
    m_D3DParam.MultiSampleQuality           = 0;

    m_D3DParam.FullScreen_RefreshRateInHz   = D3DPRESENT_INTERVAL_DEFAULT;
    m_D3DParam.Windowed                     = FALSE;


}

void  CDXGUIInterface::CDXGUIInterfaceHide::SetWModeD3D(HWND hWnd)
{
    ::ZeroMemory(&m_D3DParam, sizeof(m_D3DParam));

    m_D3DParam.hDeviceWindow        = hWnd;

    m_D3DParam.BackBufferHeight     = 0;
    m_D3DParam.BackBufferWidth      = 0;
    m_D3DParam.BackBufferFormat     = m_DisplayMode.Format;

    m_D3DParam.BackBufferCount      = 1;
    m_D3DParam.SwapEffect           = D3DSWAPEFFECT_DISCARD;
    m_D3DParam.MultiSampleType      = D3DMULTISAMPLE_NONE;
    m_D3DParam.MultiSampleQuality   = 0;

    m_D3DParam.FullScreen_RefreshRateInHz   = D3DPRESENT_INTERVAL_DEFAULT;
    m_D3DParam.Windowed                     = TRUE;
}

void CDXGUIInterface::CDXGUIInterfaceHide::InitDirect3D(const CPlatformSetting &setting, HWND hWnd)
{
    ::ZeroMemory(&m_D3DParam,sizeof(m_D3DParam));
    ::ZeroMemory(&m_DisplayMode,sizeof(m_DisplayMode));

    if( NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
    {
        throw "Direct3DCreate9 failed";
    }

    m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);
    m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_DisplayMode);

    if(m_D3DCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {
        m_vp =  D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }
    else
    {
        m_vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }

    m_vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    if(setting.IsFullModeScreen())
    {
        SetFModeD3D(setting, hWnd);
    }
    else
    {
        SetWModeD3D(hWnd);
    }

    if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, m_vp, &m_D3DParam, &m_pDevice)))
    {
         throw("CreateDevice failed");
    }

    CreateOrthoLH(static_cast<FLOAT>(setting.Width()),static_cast<FLOAT>(setting.Height()));
}

void CDXGUIInterface::CDXGUIInterfaceHide::CreateOrthoLH(FLOAT width, FLOAT height)
{
    m_pOrthLH = new D3DXMATRIX;
    D3DXMatrixOrthoLH(m_pOrthLH,width,height,-1000.0f,1000.0f); // don't worry about those two magic number
}

/*
 *
 **/
CDXGUIInterface::CDXGUIInterface():m_pHide(new CDXGUIInterfaceHide)
{
}

CDXGUIInterface::~CDXGUIInterface()
{
    if(m_pHide)
    {
        delete m_pHide;
        m_pHide = NULL;
    }
}

void CDXGUIInterface::InitialGuiInterface(const CPlatformSetting &platforSetting, const SGMHANDLE &sgmHandle)
{
    m_pHide->InitDirect3D(platforSetting,static_cast<HWND>(sgmHandle));
}

LPDIRECT3DDEVICE9 CDXGUIInterface::D3DDevice() const
{
    return m_pHide->D3DDevice();
}

void CDXGUIInterface::BeginScene()
{
    m_pHide->D3DDevice()->BeginScene();
}

void CDXGUIInterface::EndScene()
{
    m_pHide->D3DDevice()->EndScene();
    m_pHide->D3DDevice()->Present(NULL, NULL, NULL, NULL);
}

const D3DXMATRIX* CDXGUIInterface::OrthoMatrixLH() const
{
    return m_pHide->OrthoLH();
}

SGM_NAMESPACE_END
