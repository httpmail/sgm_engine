#include <vector>
#include "rolemanager.h"
#include "sgmrole.h"

SGM_NAMESPACE_START

class CRoleManager::CRoleManagerHide{
public:
    CRoleManagerHide();
    ~CRoleManagerHide();

private:
    std::vector<CSGMRole*> m_FromFile;
    std::vector<CSGMRole*> m_TempAdded;
};

CRoleManager::CRoleManagerHide::CRoleManagerHide()
{
}

CRoleManager::CRoleManagerHide::~CRoleManagerHide()
{
}

/*
 *
 **/
CRoleManager::CRoleManager()
{
}

CRoleManager::~CRoleManager()
{
}

CSGMRole* CRoleManager::AllocRole(UINT16 roleId)
{
    return NULL;
}

SGM_NAMESPACE_END
