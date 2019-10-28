

// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Monkey__h__
#define __Monkey__h__


#include "Object.h"
#include <GL/glut.h>

class Monkey: public Object
{
public:
    Monkey(const std::string& fname, Mesh** omesh);
    virtual ~Monkey();

    float   getCoordX();
    float   getCoordY();
    float   getCoordZ();

    void    setCoordX(float x);
    void    setCoordY(float y);
    void    setCoordZ(float z);

    void    increaseCoordX();
    void    increaseCoordZ();
    void    decreaseCoordX();
    void    decreaseCoordZ();


    virtual void drawInOpenGLContext( GLenum mode );

protected:
    float           m_CoordX;
    float           m_CoordY;
    float           m_CoordZ;
};
#endif // __Monkey__h__

// eof - Monkey.h
