#ifndef __Banana__h__
#define __Banana__h__

#include "Object.h"
#include <GL/glut.h>
#include <map>

class Banana: public Object
{
public:
    Banana(const std::string& fname, Mesh** omesh);
    virtual ~Banana();

    bool placeBanana(std::map<std::pair<float,float>,Object*> notPosible);
    float getCoordX();
    float getCoordZ();


    virtual void drawInOpenGLContext(GLenum mode);

protected:
    float    m_CoordX;
    float    m_CoordZ;
};

#endif // __Banana__h__

// eof - Banana.h

