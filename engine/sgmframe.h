#ifndef SGMFRAME_H
#define SGMFRAME_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START

class CImageMetadata;
class CSGMFrame{
public:
    CSGMFrame();
    CSGMFrame(const CSGMFrame &frame);
    CSGMFrame& operator=(const CSGMFrame &frame);
    virtual ~CSGMFrame();

    void Initilize(CImageMetadata *pMetadata, const CVector3D &offset = CVector3D(0.0f,0.0f,0.0f));

public:
    CVector3D OffsetPos() const;

private:
    class CSGMFrameHide;
    CSGMFrameHide *m_pHide;
};

SGM_NAMESPACE_END

#endif // SGMFRAME_H
