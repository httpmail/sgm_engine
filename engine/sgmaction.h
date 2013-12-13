#ifndef SGMACTION_H
#define SGMACTION_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START

class CSGMFrame;
class CSGMAction{
public:
    CSGMAction();
    CSGMAction(const CSGMAction &action);
    CSGMAction& operator=(const CSGMAction &action);
    virtual ~CSGMAction();

    void Initialize(CSGMFrame *pFrames, INT16 frameNum);

public:
    INT16 FrameId() const
    {
        return m_frameId;
    }

    void SetFrameId(INT16 frameId)
    {
        m_frameId = frameId;
    }

    INT16 FrameNum() const;

private:
    class CSGMActionHide;
    CSGMActionHide *m_pHide;

    INT16 m_frameId;
};

SGM_NAMESPACE_END

#if 0
class CSGMFrame;
class CSGMAction
{
public:
    CSGMAction();
    CSGMAction(const CSGMAction &srcAction);
    CSGMAction& operator=(const CSGMAction &srcAction);
    virtual ~CSGMAction();

    const CSGMFrame& Frame(UINT16 frameId);

    void SetFrameId(UINT16 frameId)
    {
        m_CurFrameId = frameId;
    }

    UINT16 FrameId() const
    {
        return m_CurFrameId;
    }

    void Initialize(CSGMFrame* frames, UINT16 frameNum);

protected:
    CSGMFrame* CloneFrames(CSGMFrame *pFrames, INT16 frameNum);
protected:
    CSGMFrame  *m_pFrames;
    INT16      m_FrameNumber;
    INT16      m_CurFrameId;
};

#endif
#endif // SGMACTION_H
