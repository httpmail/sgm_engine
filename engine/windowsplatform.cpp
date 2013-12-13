#include <windows.h>
#include "windowsplatform.h"
#include "platformsetting.h"

SGM_NAMESPACE_START

class CWindowsPlatform::CWindowsPlatformHide{
public:
    CWindowsPlatformHide():
    m_hWnd(NULL)
    {
    }

    ~CWindowsPlatformHide()
    {
    }

    HWND Handle() const
    {
        return m_hWnd;
    }
    void ShowWindow()
    {
        ::UpdateWindow(m_hWnd);
        ::ShowWindow(m_hWnd,SW_SHOWDEFAULT);
    }
    void InitWindow(const CPlatformSetting& platformSetting);

protected:
    void CreateFModeWindow(LPCWSTR className, HINSTANCE hInstance);
    void CreateWModeWindow(LPCWSTR className, HINSTANCE hInstance, UINT16 width, UINT16 height);
    void RegisterWndClass(LPCWSTR className);
    HWND RegisterWindow(LPCWSTR className, DWORD style, HINSTANCE hInstance, UINT32  width = CW_USEDEFAULT, UINT32 height = CW_USEDEFAULT);
    static  LRESULT CALLBACK Win32Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
    HWND m_hWnd;
};

void CWindowsPlatform::CWindowsPlatformHide::RegisterWndClass(LPCWSTR className)
{
    WNDCLASSEX wndClass;

    ::ZeroMemory(&wndClass,sizeof(wndClass));
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hIcon          = NULL;
    wndClass.hCursor        = NULL;
    wndClass.lpszMenuName   = NULL;
    wndClass.hInstance      = GetModuleHandle(NULL);
    wndClass.lpfnWndProc    = CWindowsPlatformHide::Win32Proc;
    wndClass.lpszClassName  = className;
    wndClass.cbSize         = sizeof(wndClass);
    wndClass.style          = CS_CLASSDC;
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);

    if(!RegisterClassEx(&wndClass))
        throw "Register Class Failed";
}

void CWindowsPlatform::CWindowsPlatformHide::CreateFModeWindow(LPCWSTR className, HINSTANCE hInstance)
{
    m_hWnd = RegisterWindow(className,WS_POPUP,hInstance);
}

void CWindowsPlatform::CWindowsPlatformHide::CreateWModeWindow(LPCWSTR className, HINSTANCE hInstance, UINT16 width, UINT16 height)
{
    m_hWnd = RegisterWindow(className,WS_OVERLAPPED|WS_MINIMIZEBOX|WS_SYSMENU, hInstance,width,height);

    //adjust window
    RECT real_rect = {0,0,width,height};
    AdjustWindowRect(&real_rect,GetWindowLong(m_hWnd,GWL_STYLE),(NULL != ::GetMenu(m_hWnd)));
    MoveWindow(m_hWnd,
                0,0,
                real_rect.right - real_rect.left,
                real_rect.bottom - real_rect.top,
                false);
}

HWND CWindowsPlatform::CWindowsPlatformHide::RegisterWindow(LPCWSTR className, DWORD style, HINSTANCE hInstance, UINT32 width, UINT32 height)
{
    return CreateWindow(
                className,          // className
                className,          // appName
                style,              // style
                0,0,                // x,y position
                width,height,
                NULL,               // hWndParent
                NULL,               // menu
                hInstance,
                NULL
                );
}

LRESULT CALLBACK CWindowsPlatform::CWindowsPlatformHide::Win32Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch( msg )
    {
        case WM_DESTROY:
            ::PostQuitMessage(0);
         break;

         case WM_KEYDOWN:
            if( wParam == VK_ESCAPE)
                ::DestroyWindow(hWnd);
         break;

         case WM_PAINT:
            PAINTSTRUCT ps;
            RECT rect;
            HDC hDestDC = BeginPaint(hWnd,&ps);
            GetClientRect(hWnd,&rect);
            FillRect(hDestDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            EndPaint(hWnd,&ps);
         break;
    }

    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

void CWindowsPlatform::CWindowsPlatformHide::InitWindow(const CPlatformSetting &platformSetting)
{
    RegisterWndClass(platformSetting.AppDescription().data());
    if(platformSetting.IsFullModeScreen())
    {
        CreateFModeWindow(platformSetting.AppDescription().data(), GetModuleHandle(NULL));
    }
    else
    {
        CreateWModeWindow(platformSetting.AppDescription().data(),GetModuleHandle(NULL),platformSetting.Width(),platformSetting.Height());
    }
}

/*
 *
 *
 ***/
CWindowsPlatform::CWindowsPlatform():
m_pHide(new CWindowsPlatformHide)
{
}
CWindowsPlatform::~CWindowsPlatform()
{
    if(m_pHide)
    {
        delete m_pHide;
        m_pHide = NULL;
    }
}

void CWindowsPlatform::InitPlatformWindow(const CPlatformSetting &platformSetting)
{
    m_pHide->InitWindow(platformSetting);
}

void CWindowsPlatform::ShowPlatformWindow()
{
    m_pHide->ShowWindow();
}

SGMHANDLE CWindowsPlatform::Handle() const
{
    return static_cast<SGMHANDLE>(m_pHide->Handle());
}

SGM_NAMESPACE_END
