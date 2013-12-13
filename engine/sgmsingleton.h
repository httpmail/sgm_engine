#ifndef SGMSINGLETON_H
#define SGMSINGLETON_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START
template<class T>
class CSGMSingleton
{
public:
    static T* Instance()
    {
        if(!m_pInstance)
        {
            m_pInstance = new T;
        }
        return m_pInstance;
    }
protected:
    CSGMSingleton(){}
    virtual ~CSGMSingleton(){}
    static T *m_pInstance;
};

template<class T>
T* CSGMSingleton<T>::m_pInstance = NULL;

SGM_NAMESPACE_END

#endif // SGMSINGLETON_H
