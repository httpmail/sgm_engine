#ifndef PLATFORM_H
#define PLATFORM_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START
class CPlatformSetting;
class CPlatform
{
public:
    CPlatform(){}
    virtual ~CPlatform(){}
    virtual void InitPlatformWindow(const CPlatformSetting& platformSetting) = 0;
    virtual void ShowPlatformWindow(){}
    virtual SGMHANDLE Handle() const = 0;
};
SGM_NAMESPACE_END

#endif // PLATFORM_H
