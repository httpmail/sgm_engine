#ifndef SGM_TYPEDEF_H
#define SGM_TYPEDEF_H

#define SGM_NAMESPACE_START namespace SGM{
#define SGM_NAMESPACE_END }

SGM_NAMESPACE_START

typedef float FLOAT;
typedef double DOUBLE;
typedef bool BOOL;

#ifndef INLINE
#define INLINE inline
#endif

typedef signed char         CHAR;
typedef unsigned char       UCHAR;

typedef signed char         INT8;
typedef unsigned char       UINT8;

typedef signed short        INT16;
typedef unsigned short      UINT16;

typedef signed int          INT32;
typedef unsigned int        UINT32;

typedef signed long long    INT64;
typedef unsigned long long  UINT64;

typedef signed int          INT;

typedef float               FLOAT;

typedef void* sgm_handle;
typedef void* SGMHANDLE;
typedef void* TEXTUREHANDLE;
typedef void* VERTEXHANDLE;

#define INVALID_VALUE (-1)

#ifndef INLINE
#define INLINE inline
#endif

#ifndef TRUE
    #define TRUE 1
#endif

#ifndef FALSE
    #define FALSE 0
#endif

#ifndef NULL
    #define NULL 0
#endif

class CVector2D{
public:
    CVector2D():m_x((float)0),m_y((float)0){}
    CVector2D(const CVector2D& v2d):m_x(v2d.m_x),m_y(v2d.m_y){}
    CVector2D(float x, float y):m_x(x),m_y(y){}
    CVector2D& operator=(const CVector2D& v2d)
    {
        if(&v2d == this)
        {
            return *this;
        }
        m_x = v2d.m_x;
        m_y = v2d.m_y;
        return *this;
    }
    ~CVector2D(){}

    FLOAT m_x;
    FLOAT m_y;
};

class CVector3D{
public:
    CVector3D():m_x((float)0),m_y((float)0),m_z((float)0){}
    CVector3D(const CVector3D& v3d):m_x(v3d.m_x),m_y(v3d.m_y),m_z(v3d.m_z){}
    CVector3D(float x, float y, float z):m_x(x),m_y(y),m_z(z){}
    CVector3D& operator=(const CVector3D& v3d)
    {
        if(&v3d == this)
        {
            return *this;
        }
        m_x = v3d.m_x;
        m_y = v3d.m_y;
        m_z = v3d.m_z;
        return *this;
    }
    ~CVector3D(){}

    FLOAT m_x;
    FLOAT m_y;
    FLOAT m_z;
};

SGM_NAMESPACE_END

#endif // SGM_TYPEDEF_H
