#ifndef __World__h__
#define __World__h__

#include "Banana.h"
#include "Obstacle.h"
#include "Conga.h"
#include "Mesh.h"
#include <GL/glut.h>
#include <map>

class World
{
public:
    World();
    virtual ~World();

    bool moveMonkeys(int dir);

    virtual void drawInOpenGLContext(GLenum mode);

protected:
    Banana*         m_Banana;
    Obstacle*       m_Obstacle;
    Conga*          m_Conga;
    Mesh*           m_BananaMesh;
};

#endif // __World__h__

// eof - World.h
