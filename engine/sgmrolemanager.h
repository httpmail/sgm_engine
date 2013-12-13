#ifndef CSGMROLEMANAGER_H
#define CSGMROLEMANAGER_H

#include "sgmsingleton.h"

SGM_NAMESPACE_START
class CSGMRole;
class CSGMRoleManager : public CSGMSingleton<CSGMRoleManager>
{
public:

private:
    friend class CSGMSingleton<CSGMRoleManager>;
    CSGMRoleManager(void);
    ~CSGMRoleManager(void);
};

SGM_NAMESPACE_END

#endif