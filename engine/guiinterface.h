#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START
class CPlatformSetting;
class CGUIInterface
{
public:
    CGUIInterface(){}
    virtual ~CGUIInterface(){}
    virtual void InitialGuiInterface(const CPlatformSetting& platforSetting, const SGMHANDLE& sgmHandle) = 0;
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;
};
SGM_NAMESPACE_END
#endif // GUIINTERFACE_H
