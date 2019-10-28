
// -------------------------------------------------------------------------
// @author Leonardo Florez-Valencia (florez-l@javeriana.edu.co)
// -------------------------------------------------------------------------
#ifndef __Conga__h__
#define __Conga__h__

#include "Monkey.h"
#include <GL/glut.h>
#include <vector>
#include <string>

class Conga
{
public:
    Conga(const std::string& obj_fname);
    virtual ~Conga();

    void addMonkey(float xAnt, float zAnt);

    std::vector<Monkey*>    getMonkeys();

    void moveMonkeys(int direction);

    virtual void drawInOpenGLContext( GLenum mode );
protected:
    std::vector<Monkey*>     m_Conga;
    int                      m_ActualDirection;
    Mesh*                    m_MonkeyBodyMesh;
};
#endif // __Conga__h__

// eof - Conga.h

