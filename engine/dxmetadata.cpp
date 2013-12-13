#include <d3d9.h>
#include <d3dx9.h>
#include "dxmetadata.h"
#include "sgmsystem.h"
#include "dxguiinterface.h"
#include "dxmetadataloader.h"

SGM_NAMESPACE_START

class CDXMetadata::CDXMetadataHide : public CSGMRefCounter{
public:
    CDXMetadataHide():m_pTexture(NULL),m_pIndexBuf(NULL),m_pVertexBuf(NULL)
    {
    }

    CDXMetadataHide(const CDXMetadataHide& srcHide):
    CSGMRefCounter(srcHide),
    m_pTexture(srcHide.m_pTexture),m_pIndexBuf(srcHide.m_pIndexBuf),m_pVertexBuf(srcHide.m_pVertexBuf)
    {
    }

    ~CDXMetadataHide()
    {
        if(m_pTexture)
        {
            m_pTexture->Release();
            m_pTexture = NULL;
        }

        if(m_pIndexBuf)
        {
            m_pIndexBuf->Release();
            m_pIndexBuf = NULL;
        }

        if(m_pVertexBuf)
        {
            m_pVertexBuf->Release();
            m_pVertexBuf = NULL;
        }
    }

public:

    void Destory()
    {
        delete this;
    }

    LPDIRECT3DINDEXBUFFER9 IndexBuf() const
    {
        return m_pIndexBuf;
    }

    LPDIRECT3DVERTEXBUFFER9 VertexBuf() const
    {
        return m_pVertexBuf;
    }

    LPDIRECT3DTEXTURE9 Texture() const
    {
        return m_pTexture;
    }

    void CreateMetadata(LPDIRECT3DTEXTURE9 srcTexture,
                        FLOAT width,FLOAT height,
                        FLOAT origX, FLOAT origY);

protected:

    void SetTexture(LPDIRECT3DTEXTURE9 srcTexture)
    {
        m_pTexture = srcTexture;
    }

    void CreateIndexBuf();
    void CreateVertexBuf(FLOAT width, FLOAT height, FLOAT origX, FLOAT origY);

private:

    LPDIRECT3DTEXTURE9        m_pTexture;
    LPDIRECT3DINDEXBUFFER9    m_pIndexBuf;
    LPDIRECT3DVERTEXBUFFER9   m_pVertexBuf;
};


 static LPD3DXSPRITE     m_pSprite = NULL;
void CDXMetadata::CDXMetadataHide::CreateIndexBuf()
{
}

void CDXMetadata::CDXMetadataHide::CreateVertexBuf(FLOAT width, FLOAT height, FLOAT origX, FLOAT origY)
{
    // create buffer
    LPDIRECT3DDEVICE9 lpD3D9 = dynamic_cast<CDXGUIInterface*>(CSGMSystem::Instance()->GUIInterface())->D3DDevice();
    lpD3D9->CreateVertexBuffer(
                BASE2D_VERTEX_SIZE,
                D3DUSAGE_WRITEONLY,
                BASE2D_VERTEX_FVF,
                D3DPOOL_MANAGED,
                &m_pVertexBuf,
                NULL);

    // fill buffer
    static FLOAT z = 1.0f;
    FLOAT half_width    = width/2;
    FLOAT half_height   = height/2;

    FLOAT left_top_x    = -half_width;
    FLOAT left_top_y    = half_height;
    FLOAT right_top_x   = width + left_top_x;
    FLOAT right_top_y   = left_top_y;

    FLOAT left_bottom_x   = left_top_x;
    FLOAT left_bottom_y   = left_top_y - height;
    FLOAT right_bottom_x  = right_top_x;
    FLOAT right_bottom_y  = left_bottom_y;

    _2DBaseVertex *pVertexBuf;
    _2DBaseVertex fillSrc[] = {
        {left_top_x,    left_top_y,     z,0,0},
        {right_top_x,   right_top_y,    z,1,0},
        {right_bottom_x,right_bottom_y, z,1,1},
        {left_bottom_x, left_bottom_y,  z,0,1},
    };
    m_pVertexBuf->Lock(0,0,(void**)&pVertexBuf,0);
    memcpy(pVertexBuf,fillSrc,BASE2D_VERTEX_SIZE);
    m_pVertexBuf->Unlock();
}

void CDXMetadata::CDXMetadataHide::CreateMetadata(LPDIRECT3DTEXTURE9 srcTexture,
                                                  FLOAT width, FLOAT height,
                                                  FLOAT origX, FLOAT origY)
{
    SetTexture(srcTexture);
    CreateVertexBuf(width,height,origX,origY);
}

/*
 *
 ***/
CDXMetadata::CDXMetadata():
m_pHide(new CDXMetadataHide)
{
}

CDXMetadata::~CDXMetadata()
{
    m_pHide->Release();
}

CDXMetadata::CDXMetadata(const CDXMetadata &srcMetadata):
CImageMetadata(srcMetadata),
m_pHide(srcMetadata.m_pHide)
{
    m_pHide->AddRef();
}

CDXMetadata& CDXMetadata::operator=(const CDXMetadata &srcMetadata)
{
    if(this != &srcMetadata)
    {
        CImageMetadata::operator =(srcMetadata);
        m_pHide->Release();
        m_pHide = srcMetadata.m_pHide;
        m_pHide->AddRef();
    }

    return *this;
}

void CDXMetadata::SetTexture(LPDIRECT3DTEXTURE9 lpTexture)
{
}

void CDXMetadata::SetTexture(LPDIRECT3DTEXTURE9 lpTexture, UINT16 width, UINT16 height)
{
}

void CDXMetadata::SetTexture(const std::wstring &srcPath, IMAGE_ORIGIN_TYPE eOriginType)
{
    float width,height;
    float origX,origY;

    CDXMetadataLoader loader;
    LPDIRECT3DTEXTURE9 pTexture = loader.CreateTextureFromFile(srcPath,&width,&height);

    switch(eOriginType)
    {
    case IORIGIN_CENTRAL:
        origX = 0.0f;
        origY = 0.0f;
        break;
    case IORIGIN_TOPLEFT:
        origX = width/2.0f;
        origY = height/2.0f;
        break;
    case IORIGIN_BOTTOM_MID:
        origX = width/20.f;
        origY = height;
        break;
    default:
        origX = 0.0f;
        origY = 0.0f;
    }

    m_pHide->CreateMetadata(pTexture,width,height,origX,origY);
}

void CDXMetadata::Draw()
{


    LPDIRECT3DDEVICE9 lpD3D9 = dynamic_cast<CDXGUIInterface*>(CSGMSystem::Instance()->GUIInterface())->D3DDevice();
    lpD3D9->SetTransform(D3DTS_PROJECTION,dynamic_cast<CDXGUIInterface*>(CSGMSystem::Instance()->GUIInterface())->OrthoMatrixLH());
    lpD3D9->SetTexture(0,m_pHide->Texture());
    lpD3D9->SetStreamSource(0,m_pHide->VertexBuf(),0,BASE2D_VERTEX_TYPE_SIZE);
    lpD3D9->SetFVF(BASE2D_VERTEX_FVF);
    lpD3D9->DrawPrimitive(D3DPT_TRIANGLEFAN,0,2);
    lpD3D9->SetRenderState(D3DRS_LIGHTING,FALSE);

}

SGM_NAMESPACE_END
