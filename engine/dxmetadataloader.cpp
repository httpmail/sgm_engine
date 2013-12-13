#include "dxmetadataloader.h"
#include "dxguiinterface.h"
#include "sgmsystem.h"

SGM_NAMESPACE_START
CDXMetadataLoader::CDXMetadataLoader()
{
}

CDXMetadataLoader::~CDXMetadataLoader()
{

}

CMetadataLoader::Metadata* CDXMetadataLoader::CreateMetadataFromFile(const std::wstring &srcFile, MetadataType eMetadataType)
{
    return NULL;
}

LPDIRECT3DTEXTURE9 CDXMetadataLoader::CreateTextureFromFile(const std::wstring &srcFile, FLOAT *pWidth, FLOAT *pHeight)
{
    D3DXIMAGE_INFO srcImageInfo;
    LPDIRECT3DTEXTURE9 pTexture = NULL;
    CSGMSystem *pSystem = CSGMSystem::Instance();
    CDXGUIInterface *pDXGUI = dynamic_cast<CDXGUIInterface*>(pSystem->GUIInterface());
    D3DXCreateTextureFromFileEx(
                    pDXGUI->D3DDevice(),
                    srcFile.data(),
                    D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,
                    0,
                    D3DFMT_UNKNOWN,
                    D3DPOOL_MANAGED,
                    D3DX_DEFAULT,
                    D3DX_DEFAULT,
                    0,
                    &srcImageInfo,
                    NULL,
                    &pTexture);

    if(pWidth)
    {
        *pWidth  = static_cast<FLOAT>(srcImageInfo.Width);
    }

    if(pHeight)
    {
        *pHeight = static_cast<FLOAT>(srcImageInfo.Height);
    }
    return pTexture;
}

SGM_NAMESPACE_END
