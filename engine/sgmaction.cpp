#include "sgmaction.h"
#include "sgmrefcounter.h"
#include "sgmframe.h"

SGM_NAMESPACE_START

class CSGMAction::CSGMActionHide : public CSGMRefCounter{
public:
    CSGMActionHide(CSGMFrame *pFrames, INT16 frameNum):
        m_pFrames(pFrames),m_FrameNum(frameNum)
    {
    }

    virtual ~CSGMActionHide()
    {
    }

public:

    void SetFrames(CSGMFrame *pFrame, INT16 frameNum)
    {
        m_pFrames   = pFrame;
        m_FrameNum  = frameNum;
    }

    CSGMFrame* Frame(INT16 frameId) const
    {
        return m_pFrames + frameId;
    }

    INT16 FrameNum() const
    {
        return m_FrameNum;
    }

protected:
    void Destory()
    {
        delete this;
    }

protected:
    CSGMFrame   *m_pFrames;
    INT16       m_FrameNum;
};

/*
 *
 *
 *
 **/
CSGMAction::CSGMAction():
    m_pHide(new CSGMActionHide(NULL,0)),m_frameId(0)
{
}

CSGMAction::CSGMAction(const CSGMAction &action):
    m_pHide(action.m_pHide)
{
    if(m_pHide)
    {
        m_pHide->AddRef();
    }
}

CSGMAction& CSGMAction::operator =(const CSGMAction &action)
{
    if(this != &action)
    {
        if(m_pHide)
        {
            m_pHide->Release();
        }
        m_pHide = action.m_pHide;
        m_pHide->AddRef();
    }
    return *this;
}

CSGMAction::~CSGMAction()
{
    m_pHide->Release();
}

INT16 CSGMAction::FrameNum() const
{
    return m_pHide->FrameNum();
}

void CSGMAction::Initialize(CSGMFrame *pFrames, INT16 frameNum)
{
    m_pHide->SetFrames(pFrames,frameNum);
}

SGM_NAMESPACE_END




