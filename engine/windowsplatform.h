#ifndef WINDOWSPLATFORM_H
#define WINDOWSPLATFORM_H

#include "platform.h"
#include "sgmsingleton.h"

SGM_NAMESPACE_START
class CWindowsPlatform : public CSGMSingleton<CWindowsPlatform>,public CPlatform
{
public:
    void InitPlatformWindow(const CPlatformSetting &platformSetting);
    void ShowPlatformWindow();
    SGMHANDLE Handle() const;

private:
    CWindowsPlatform();
    ~CWindowsPlatform();
    friend class CSGMSingleton<CWindowsPlatform>;
protected:
    class CWindowsPlatformHide;
    CWindowsPlatformHide *m_pHide;
};
SGM_NAMESPACE_END

#endif // WINDOWSPLATFORM_H
