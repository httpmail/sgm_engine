#ifndef IMAGEMETADATA_H
#define IMAGEMETADATA_H

#include "sgm_typedef.h"
#include "sgmrefcounter.h"

SGM_NAMESPACE_START
class CImageMetadata
{
public:
    virtual void Release(){};
    virtual void Draw() = 0;
public:
    virtual ~CImageMetadata() = 0;
    CImageMetadata():
        m_MetadataNumber(INVALID_VALUE),
        m_VertexNumber(INVALID_VALUE),m_IndexNumber(INVALID_VALUE),
        m_MetaTypeSize(INVALID_VALUE)
    {
    }

    CImageMetadata(const CImageMetadata& srcMetadata):
        m_MetadataNumber(srcMetadata.m_MetadataNumber),
        m_VertexNumber(srcMetadata.m_VertexNumber),
        m_IndexNumber(srcMetadata.m_IndexNumber),
        m_MetaTypeSize(srcMetadata.m_MetaTypeSize)
    {
    }

    CImageMetadata& operator = (const CImageMetadata& srcMetadata)
    {
        if(this != &srcMetadata)
        {
            m_MetadataFormat    = srcMetadata.m_MetadataFormat;
            m_MetadataNumber    = srcMetadata.m_MetadataNumber;
            m_MetaTypeSize      = srcMetadata.m_MetaTypeSize;
            m_IndexNumber       = srcMetadata.m_IndexNumber;
        }
        return *this;
    }

    UINT16 MetadataNumber() const
    {
        return m_MetadataNumber;
    }

    UINT16 VertexNumber() const
    {
        return m_VertexNumber;
    }

    UINT16 IndexNumber() const
    {
        return m_IndexNumber;
    }

    UINT16 SizeOfMetadataType() const
    {
        return m_MetaTypeSize;
    }

    UINT32 FormatOfMetadata() const
    {
        return m_MetadataFormat;
    }

protected:
    void SetMetadataNumber(UINT16 metaNumber)
    {
        m_MetadataNumber = metaNumber;
    }

    void SetVertexNumber(UINT16 vertexNumber)
    {
        m_VertexNumber = vertexNumber;
    }

    void SetIndexNumber(UINT16 IndexNumber)
    {
        m_IndexNumber = IndexNumber;
    }

    void SetSizeOfMetadataType(UINT16 metaTypeSize)
    {
        m_MetaTypeSize = metaTypeSize;
    }

    void SetFormatOfMetadata(UINT32 metaFormat)
    {
        m_MetadataFormat = metaFormat;
    }

protected:

    UINT16 m_MetadataNumber;
    UINT16 m_VertexNumber;
    UINT16 m_IndexNumber;
    UINT16 m_MetaTypeSize;
    UINT32 m_MetadataFormat;
};


SGM_NAMESPACE_END

#endif // IMAGEMETADATA_H
