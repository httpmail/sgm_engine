#ifndef PLATFORMSETTING_H
#define PLATFORMSETTING_H

#include <string>
#include "sgm_typedef.h"

SGM_NAMESPACE_START
class CPlatformSetting
{
public:
    enum COLOR_FORMAT{
        COLORFMT_DEF = 0,
        COLORFMT_RGB,
        COLORFMT_A8R8G8B8,
        COLORFMT_X8R8G8B8
    };

    enum WINDOW_MODE{
        FMODE_WIND  = TRUE,
        WMODE_WIND = FALSE
    };

    static const UINT32 DEF_WIDTH     = 800;
    static const UINT32 DEF_HEIGHT    = 600;
    static const std::wstring DEF_APPDESCRIPTION;
    static const COLOR_FORMAT DEF_COLORFMT;
public:
    CPlatformSetting():
    m_AppDescription(DEF_APPDESCRIPTION),m_Width(DEF_WIDTH),m_Height(DEF_HEIGHT),m_ColorFmt(DEF_COLORFMT),m_bFullMode(FALSE)
    {}

    CPlatformSetting(const CPlatformSetting& platforSetting):
    m_AppDescription(platforSetting.m_AppDescription),m_Width(platforSetting.m_Width),m_Height(platforSetting.m_Height),m_ColorFmt(platforSetting.m_ColorFmt),m_bFullMode(platforSetting.m_bFullMode)
    {}

    CPlatformSetting& operator=(const CPlatformSetting& platforSetting)
    {
        if(this != &platforSetting)
        {
            m_AppDescription            = platforSetting.m_AppDescription;
            m_Width                           = platforSetting.m_Width;
            m_Height                          = platforSetting.m_Height;
            m_ColorFmt                      = platforSetting.m_ColorFmt;
            m_bFullMode                   = platforSetting.m_bFullMode;
        }
        return *this;
    }
    virtual ~CPlatformSetting(){}

    UINT32 Width() const
    {
        return m_Width;
    }

    UINT32 Height() const
    {
        return m_Height;
    }

    BOOL IsFullModeScreen() const
    {
        return m_bFullMode;
    }
    void SetScreenMode(bool bFullMode = true)
    {
        m_bFullMode = bFullMode;
    }

    const std::wstring& AppDescription() const
    {
        return m_AppDescription;
    }

    COLOR_FORMAT ColorFormat() const
    {
        return m_ColorFmt;
    }

private:
    std::wstring m_AppDescription;
    UINT32 m_Width;
    UINT32 m_Height;
    COLOR_FORMAT m_ColorFmt;
    BOOL m_bFullMode;
};

SGM_NAMESPACE_END
#endif // PLATFORMSETTING_H
