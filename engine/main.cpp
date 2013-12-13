#include "sgm_typedef.h"
#include "sgmrole.h"
#include "sgmaction.h"
#include "sgmframe.h"
#include "imagemetadata.h"
#include "dxmetadata.h"
#include <iostream>
#include <Windows.h>
#include "sgmsystem.h"
#include "windowsplatform.h"
#include "sgmsystem.h"
#include "dxguiinterface.h"
#include "platformsetting.h"


using namespace std;
using namespace SGM;

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
    CSGMSystem *pSystem = CSGMSystem::Instance();
    CPlatformSetting sysSetting;
    pSystem->InitSgmSystem(CWindowsPlatform::Instance(),CDXGUIInterface::Instance(), sysSetting);
    MSG msg;
    CDXMetadata *pMetadata = new CDXMetadata;
    pMetadata->SetTexture(L"E:\\1.bmp");
    ::ZeroMemory(&msg,sizeof(msg));
    do{
        if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        else
        {

            //CDXGUIInterface::Instance()->D3DDevice()->BeginScene();
            //CDXGUIInterface::Instance()->D3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
            pSystem->BeginScene();
            pMetadata->Draw();
            pSystem->EndScene();
            //CDXGUIInterface::Instance()->D3DDevice()->EndScene();
            //CDXGUIInterface::Instance()->D3DDevice()->Present(NULL, NULL, NULL, NULL);
        }
    }while(WM_QUIT != msg.message);

    return 0;
}

