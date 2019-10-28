#include "Obstacle.h"

Obstacle::
Obstacle(const std::string& obj_fname )
{
    this->m_InternalObstacleMesh = new Mesh(obj_fname);
    this->m_InternalObstacleMesh->setColor(0.392156,0.803921,0.266667);
}
Obstacle::
~Obstacle()
{

}

std::map<std::pair<float,float>,Object*>  Obstacle::
getObstacles()
{
    return this->m_Obstacles;
}


void Obstacle::
addObstacle()
{
    for(int i = 1; i <= 2; i++)
    {
        for(int j = 1; j <= 2; j++)
        {
            std::map<std::pair<float,float>,Object*>::iterator it = this->m_Obstacles.begin();
            Object* newObstacle = new Object("snake.txt",&this->m_InternalObstacleMesh);
            std::pair<float,float> myCoords (i*4,j*4);
            newObstacle->rotateX(11);
            newObstacle->rotateY(-11);
            this->m_Obstacles.insert(it,std::pair<std::pair<float,float>,Object*> (myCoords,newObstacle));
        }
    }
}

void Obstacle::
drawInOpenGLContext(GLenum mode)
{
    std::map<std::pair<float,float>,Object*>::iterator it;
    glPushMatrix();
    for (it = this->m_Obstacles.begin(); it!=this->m_Obstacles.end();it++)
    {
        glPushMatrix();
        glTranslatef(std::get<0>(it->first),-1,std::get<1>(it->first));
        it->second->drawInOpenGLContext(mode);
        glPopMatrix();
    }
    glPopMatrix();
}
