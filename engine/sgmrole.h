#ifndef SGMROLE_H
#define SGMROLE_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START
class CSGMAction;

class CSGMRole{
public:
    CSGMRole();
    CSGMRole(const CSGMRole &role);
    CSGMRole& operator=(const CSGMRole &role);
    virtual ~CSGMRole();

    void Initialize(CSGMAction *pAction,INT16 actNum);

public:
    INT16 ActId() const;
    void SetActId(INT16 actId);

    INT16 FrameId() const;
    void SetFrameId(INT16 frameId);

    INT16 ActNum() const;

    CVector3D Position() const
    {
        return m_Pos;
    }

    void SetPosition(const CVector2D &v2d)
    {
        m_Pos.m_x = v2d.m_x;
        m_Pos.m_y = v2d.m_y;
    }

    void SetPosition(FLOAT x, FLOAT y)
    {
        m_Pos.m_x = x;
        m_Pos.m_y = y;
    }

    void SetPosition(const CVector3D &v3d)
    {
        m_Pos = v3d;
    }

    void SetPosition(FLOAT x, FLOAT y, FLOAT z)
    {
        m_Pos.m_x = x;
        m_Pos.m_y = y;
        m_Pos.m_z = z;
    }

    FLOAT XPos() const
    {
        return m_Pos.m_x;
    }
    void SetXPos(FLOAT x)
    {
        m_Pos.m_x = x;
    }

    FLOAT YPos() const
    {
        return m_Pos.m_y;
    }

    void SetYPos(FLOAT y)
    {
        m_Pos.m_y = y;
    }

    FLOAT ZPos() const
    {
        return m_Pos.m_z;
    }

    void SetZPos(FLOAT z)
    {
        m_Pos.m_z = z;
    }

private:
    class CSGMRoleHide;
    CSGMRoleHide *m_pHide;

    CVector3D   m_Pos;
    INT16       m_CurActId;
};
SGM_NAMESPACE_END

#endif
