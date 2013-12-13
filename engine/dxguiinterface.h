#ifndef DXGUIINTERFACE_H
#define DXGUIINTERFACE_H
#include <d3d9.h>
#include <d3dx9.h>
#include "guiinterface.h"
#include "sgmsingleton.h"

SGM_NAMESPACE_START
class CDXGUIInterface : public CSGMSingleton<CDXGUIInterface>, public CGUIInterface
{
public:
    void InitialGuiInterface(const CPlatformSetting &platforSetting, const SGMHANDLE &sgmHandle);
    LPDIRECT3DDEVICE9 D3DDevice() const;
    void BeginScene();
    void EndScene();
    const D3DXMATRIX* OrthoMatrixLH() const;
private:
    CDXGUIInterface();
    virtual ~CDXGUIInterface();

protected:
    class CDXGUIInterfaceHide;
    friend class CSGMSingleton<CDXGUIInterface>;
    CDXGUIInterfaceHide *m_pHide;
};
SGM_NAMESPACE_END

#endif // DXGUIINTERFACE_H
