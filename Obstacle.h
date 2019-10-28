#ifndef __Obstacle__h__
#define __Obstacle__h__

#include "Object.h"
#include <GL/glut.h>
#include <map>

class Obstacle
{
public:
    Obstacle(const std::string& obj_fname );
    virtual ~Obstacle();

    std::map<std::pair<float,float>,Object*>  getObstacles();
    void                                      addObstacle();

    virtual void drawInOpenGLContext(GLenum mode);
protected:
    Mesh*                                       m_InternalObstacleMesh;
    std::map<std::pair<float,float>,Object*>    m_Obstacles;
};

#endif // __Obstacle__h__

// eof - Obstacle.h
