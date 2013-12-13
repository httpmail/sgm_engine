#include "sgmframe.h"
#include "sgmrefcounter.h"
#include "imagemetadata.h"

SGM_NAMESPACE_START
class CSGMFrame::CSGMFrameHide : public CSGMRefCounter{
public:
    CSGMFrameHide(CImageMetadata *pMetadata, const CVector3D &v3d);
    virtual ~CSGMFrameHide();

public:
    void SetMetadata(CImageMetadata *pMetadata, const CVector3D &v3d)
    {
        m_pMetadata = pMetadata;
        m_OffsetPos = v3d;
    }

    CImageMetadata* Metadata() const
    {
        return m_pMetadata;
    }

    CVector3D OffsetPos() const
    {
        return m_OffsetPos;
    }

protected:
    void Destory();

protected:
    CImageMetadata  *m_pMetadata;
    CVector3D       m_OffsetPos;
};

CSGMFrame::CSGMFrameHide::CSGMFrameHide(CImageMetadata *pMetadata, const CVector3D &v3d):
    m_pMetadata(pMetadata),m_OffsetPos(v3d)
{

}

CSGMFrame::CSGMFrameHide::~CSGMFrameHide()
{
}

void CSGMFrame::CSGMFrameHide::Destory()
{
    delete this;
}

CSGMFrame::CSGMFrame():m_pHide(new CSGMFrameHide(NULL,CVector3D(0.0f,0.0f,0.0f)))
{
}

CSGMFrame::CSGMFrame(const CSGMFrame &frame):
    m_pHide(frame.m_pHide)
{
    m_pHide->AddRef();
    m_pHide = NULL;
}

CSGMFrame& CSGMFrame::operator =(const CSGMFrame &frame)
{
    if(this != &frame)
    {
        m_pHide->Release();
        m_pHide = frame.m_pHide;
        m_pHide->AddRef();
    }
    return *this;
}

CSGMFrame::~CSGMFrame()
{
    m_pHide->Release();
}


CVector3D CSGMFrame::OffsetPos() const
{
    return m_pHide->OffsetPos();
}

void CSGMFrame::Initilize(CImageMetadata *pMetadata, const CVector3D &offset)
{
    return m_pHide->SetMetadata(pMetadata,offset);
}

SGM_NAMESPACE_END
