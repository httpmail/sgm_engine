#ifndef SGMSYSTEM_H
#define SGMSYSTEM_H

#include "sgm_typedef.h"
#include "sgmsingleton.h"

SGM_NAMESPACE_START
class CGUIInterface;
class CPlatform;
class CPlatformSetting;

class CSGMSystem : public CSGMSingleton<CSGMSystem>{
public:
    void InitSgmSystem(CPlatform *platform, CGUIInterface *guiInterface, const CPlatformSetting& platformSetting);
    CGUIInterface* GUIInterface() const;
    CPlatform* PlatformInterface() const;
    CPlatformSetting& PlatformSetting() const;

public:
    void BeginScene();
    void EndScene();

private:
    CSGMSystem();
    virtual ~CSGMSystem();
protected:
    class CSGMSystemHide;
    friend class CSGMSingleton<CSGMSystem>;
    CSGMSystemHide *m_pHide;
};

SGM_NAMESPACE_END

#endif // SGMSYSTEM_H
