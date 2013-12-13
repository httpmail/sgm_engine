#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include "sgm_typedef.h"
#include "sgmsingleton.h"

SGM_NAMESPACE_START

class CSGMRole;

class CRoleManager : public CSGMSingleton<CRoleManager>{
public:
    CSGMRole* AllocRole(UINT16 roleId);

private:
    CRoleManager();
    ~CRoleManager();

private:
    friend class CSGMSingleton<CRoleManager>;
    class CRoleManagerHide;
    CRoleManagerHide *m_pHide;
};
SGM_NAMESPACE_END
#endif // ROLEMANAGER_H
