#ifndef METADATALOADER_H
#define METADATALOADER_H

#include <string>
#include "sgm_typedef.h"


SGM_NAMESPACE_START
class CMetadataLoader
{
public:
    enum MetadataType{
        METATYPE_UNKNOWN,
        METATYPE_DXTEXTURE,
        METATYPE_FILEMEMORY,
        METATYPE_FORMATFILE
    };

    struct Metadata{
        UINT8   *data;
        UINT32 dataLength;
        UINT32 ColorFormat;
        UINT32 ImageWidth;
        UINT32 ImageHeight;
        MetadataType eMetadataType;
    };
public:
    CMetadataLoader(){}
    virtual ~CMetadataLoader(){};
    virtual Metadata* CreateMetadataFromFile(const std::wstring &srcFile, MetadataType eMetadataType) = 0;
};
SGM_NAMESPACE_END

#endif // METADATALOADER_H
