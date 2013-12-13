#include "sgmsystem.h"
#include "platformsetting.h"
#include "platform.h"
#include "guiinterface.h"

SGM_NAMESPACE_START

class CSGMSystem::CSGMSystemHide{
public:
    CSGMSystemHide(CPlatform *platform, CGUIInterface *guiInterface, const CPlatformSetting &Setting);
    ~CSGMSystemHide();

    INLINE CPlatform* Platform()
    {
        return m_pPlatform;
    }

    INLINE CGUIInterface* GUIInterface()
    {
        return m_pGUIInterface;
    }

    INLINE CPlatformSetting& PlatformSetting()
    {
        return m_UsedSetting;
    }

    INLINE CPlatformSetting& DefaultSetting()
    {
        return m_DefaultSetting;
    }

private:
    CPlatform   *m_pPlatform;
    CGUIInterface *m_pGUIInterface;
    CPlatformSetting m_UsedSetting;
    CPlatformSetting m_DefaultSetting;
};

CSGMSystem::CSGMSystemHide::CSGMSystemHide(CPlatform* platform, CGUIInterface* guiInterface, const CPlatformSetting& Setting):
m_pPlatform(platform),m_pGUIInterface(guiInterface),m_UsedSetting(Setting),m_DefaultSetting(Setting)
{
}

CSGMSystem::CSGMSystemHide::~CSGMSystemHide()
{
}

CSGMSystem::CSGMSystem():
m_pHide(NULL)
{
}

CSGMSystem::~CSGMSystem()
{
    if(m_pHide)
    {
        delete m_pHide;
        m_pHide = NULL;
    }
}

void CSGMSystem::InitSgmSystem(CPlatform *platform, CGUIInterface *guiInterface,const CPlatformSetting &platformSetting)
{
    if(!m_pHide)
    {
        m_pHide = new CSGMSystemHide(platform,guiInterface,platformSetting);
        m_pHide->Platform()->InitPlatformWindow(platformSetting);
        m_pHide->GUIInterface()->InitialGuiInterface(platformSetting,m_pHide->Platform()->Handle());
        m_pHide->Platform()->ShowPlatformWindow();
    }
}

CGUIInterface* CSGMSystem::GUIInterface() const
{
    return m_pHide->GUIInterface();
}

CPlatform* CSGMSystem::PlatformInterface() const
{
    return m_pHide->Platform();
}

CPlatformSetting& CSGMSystem::PlatformSetting() const
{
    return m_pHide->PlatformSetting();
}

void CSGMSystem::BeginScene()
{
    m_pHide->GUIInterface()->BeginScene();
}

void CSGMSystem::EndScene()
{
    m_pHide->GUIInterface()->EndScene();
}

SGM_NAMESPACE_END
