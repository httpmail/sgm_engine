#ifndef DXMETADATA_H
#define DXMETADATA_H

#include "dxmetadataloader.h"
#include "imagemetadata.h"

SGM_NAMESPACE_START
class CDXMetadata : public CImageMetadata{
public:
    enum IMAGE_ORIGIN_TYPE{
        IORIGIN_TOPLEFT = 0,
        IORIGIN_CENTRAL,
        IORIGIN_BOTTOM_MID
    };
public:
    CDXMetadata();
    virtual ~CDXMetadata();
    CDXMetadata(const CDXMetadata& srcMetadata);
    CDXMetadata& operator =(const CDXMetadata &srcMetadata);

public:
    void SetTexture(const std::wstring &srcPath, IMAGE_ORIGIN_TYPE eOriginType = IORIGIN_CENTRAL);
    void SetTexture(LPDIRECT3DTEXTURE9 lpTexture);
    void SetTexture(LPDIRECT3DTEXTURE9 lpTexture, UINT16 width, UINT16 height);

    void Draw();
public:

    struct _2DBaseVertex{
        FLOAT x,y,z;
        FLOAT u,v;
    };

    const static UINT32 BASE2D_VERTEX_TYPE_SIZE = sizeof(_2DBaseVertex);
    const static DWORD  BASE2D_VERTEX_FVF       = (D3DFVF_XYZ|D3DFVF_TEX1);
    const static DWORD  BASE2D_VERTEX_NUMBER    = 4;
    const static DWORD  BASE2D_VERTEX_SIZE      = BASE2D_VERTEX_NUMBER*BASE2D_VERTEX_TYPE_SIZE;
private:
    class CDXMetadataHide;
    CDXMetadataHide *m_pHide;
};
SGM_NAMESPACE_END

#endif // DXMETADATA_H
