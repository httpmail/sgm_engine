#ifndef DXMETADATALOADER_H
#define DXMETADATALOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include "metadataloader.h"

SGM_NAMESPACE_START
class CDXMetadataLoader : public CMetadataLoader
{
public:
    CDXMetadataLoader();
    ~CDXMetadataLoader();
    Metadata* CreateMetadataFromFile(const std::wstring &srcFile, MetadataType eMetadataType);
    LPDIRECT3DTEXTURE9 CreateTextureFromFile(const std::wstring &srcFile, FLOAT *pWidth = NULL, FLOAT *pHeight = NULL);
    LPDIRECT3DTEXTURE9 CreateTextureFromFormatFile(const std::wstring &srcFile);
    LPDIRECT3DTEXTURE9 CloneTexture(LPDIRECT3DTEXTURE9 srcTexture);
};
SGM_NAMESPACE_END
#endif // DXMETADATALOADER_H
