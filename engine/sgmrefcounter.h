#ifndef SGMREFCOUNTER_H
#define SGMREFCOUNTER_H

#include "sgm_typedef.h"

SGM_NAMESPACE_START

class CSGMRefCounter{
public:

    CSGMRefCounter():m_pCounter(new int(1))
    {
    }

    CSGMRefCounter(const CSGMRefCounter& refCounter):m_pCounter(refCounter.m_pCounter)
    {
        (*m_pCounter)++;
    }

    CSGMRefCounter& operator= (const CSGMRefCounter& refCounter)
    {
        if(this != &refCounter)
        {
            Release();
            m_pCounter = refCounter.m_pCounter;
            (*m_pCounter)++;
        }
        return *this;
    }

    virtual ~CSGMRefCounter()
    {
        if(m_pCounter)
        {
            if(--(*m_pCounter) <= 0)
            {
                delete m_pCounter;
            }
        }
    };

    INT RefCounter() const
    {
        return *m_pCounter;
    }

    INT* Ref() const
    {
        return m_pCounter;
    }

public:
    void Release()
    {
        if(m_pCounter)
        {
            if((--(*m_pCounter)) <= 0)
            {
                delete m_pCounter;
                m_pCounter = NULL;
                Destory();
            }
        }
    }

    void AddRef()
    {
        (*m_pCounter)++;
    }

protected:
    virtual void Destory() = 0;

protected:
    INT *m_pCounter;
};
SGM_NAMESPACE_END

#endif // SGMREFCOUNTER_H
