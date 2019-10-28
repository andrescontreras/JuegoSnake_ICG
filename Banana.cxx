#include "Banana.h"

Banana::
Banana(const std::string& fname, Mesh** omesh)
    :Object(fname,omesh)
{
    this->rotateZ(-1);
    this->rotateY(-11);
    this->m_Mesh->setColor(0.937254,0.992156,0.164705);
}

Banana::
~Banana()
{

}

bool Banana::
placeBanana(std::map<std::pair<float,float>,Object*> notPosible)
{
    float x  = 0;
    float z  = 0;
    bool  encontrado = true;
    do
    {
       x += 1;
       z += 1;
       std::pair<float,float> xz (x,z);
       if(notPosible.find(xz) == notPosible.end())
       {
           encontrado = false;
       }
    }while(encontrado);
    this->m_CoordX = x;
    this->m_CoordZ = z;
    return true;

}

float Banana::
getCoordX()
{
    return this->m_CoordX;
}

float Banana::
getCoordZ()
{
    return this->m_CoordZ;
}

void Banana::
drawInOpenGLContext(GLenum mode)
{
    glPushMatrix();
    glTranslatef(this->m_CoordX,-0.5,this->m_CoordZ);
    this->Object::drawInOpenGLContext(mode);
    glPopMatrix();
}
