#include "sgmrole.h"
#include "sgmaction.h"
#include "sgmrefcounter.h"

SGM_NAMESPACE_START

class CSGMRole::CSGMRoleHide : public CSGMRefCounter{
public:
    CSGMRoleHide(CSGMAction *pAction, INT16 actNum):
        m_pActions(pAction),m_ActNum(actNum)
    {
    }

    virtual ~CSGMRoleHide()
    {
    }

public:

    CSGMAction* Action(INT16 actId) const
    {
        return m_pActions + actId;
    }

    void SetActions(CSGMAction *pAction, INT16 actNum)
    {
        m_pActions  = pAction;
        m_ActNum    = actNum;
    }

    INT16 ActNum() const
    {
        return m_ActNum;
    }

    void Destory()
    {
        delete this;
    }

protected:
    friend class CSGMRole;
    CSGMAction *m_pActions;
    INT16       m_ActNum;
};

CSGMRole::CSGMRole():m_pHide(new CSGMRoleHide(NULL,0))
{
}

CSGMRole::CSGMRole(const CSGMRole &role):
    m_pHide(role.m_pHide)
{
    m_pHide->AddRef();
}

CSGMRole& CSGMRole::operator=(const CSGMRole &role)
{
    if(this != &role)
    {
        m_pHide->Release();
        m_pHide = role.m_pHide;
        m_pHide->AddRef();
    }
    return *this;
}

CSGMRole::~CSGMRole()
{
    m_pHide->Release();
}

INT16 CSGMRole::ActId() const
{
    return m_CurActId;
}

void CSGMRole::SetActId(INT16 actId)
{
    m_CurActId = actId;
}

INT16 CSGMRole::ActNum() const
{
    return m_pHide->ActNum();
}

INT16 CSGMRole::FrameId() const
{
    return m_pHide->Action(m_CurActId)->FrameId();
}

void CSGMRole::SetFrameId(INT16 frameId)
{
    m_pHide->Action(m_CurActId)->SetFrameId(frameId);
}

void CSGMRole::Initialize(CSGMAction *pAction, INT16 actNum)
{
    m_CurActId = 0;
    m_pHide->SetActions(pAction,actNum);
}

SGM_NAMESPACE_END
