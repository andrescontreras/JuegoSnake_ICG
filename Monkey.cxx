#include "Monkey.h"

Monkey::
Monkey(const std::string& fname, Mesh** omesh)
    :Object(fname,omesh)
{
    this->rotateX(11);
    this->rotateY(-11);
    this->m_CoordX = 0;
    this->m_CoordY = -1;
    this->m_CoordZ = 0;
    this->m_ScaleX = 0.01;
    this->m_ScaleY = 0.01;
    this->m_ScaleZ = 0.01;
}
Monkey::
~Monkey()
{

}

float Monkey::
getCoordX()
{
    return this->m_CoordX;
}

float Monkey::
getCoordY()
{
    return this->m_CoordY;
}

float Monkey::
getCoordZ()
{
    return this->m_CoordZ;
}

void Monkey::
setCoordX(float x)
{
    this->m_CoordX =x;
}

void Monkey::
setCoordY(float y)
{
    this->m_CoordY =y;
}

void Monkey::
setCoordZ(float z)
{
    this->m_CoordZ =z;
}

void Monkey::
increaseCoordX()
{
    this->m_CoordX += 1;
}

void Monkey::
increaseCoordZ()
{
    this->m_CoordZ += 1;
}

void Monkey::
decreaseCoordX()
{
    this->m_CoordX -= 1;
}

void Monkey::
decreaseCoordZ()
{
    this->m_CoordZ -= 1;
}

void Monkey::
drawInOpenGLContext( GLenum mode )
{
    glPushMatrix();
    glTranslatef(this->m_CoordX,this->m_CoordY,this->m_CoordZ);
    this->Object::drawInOpenGLContext(mode);
    glPopMatrix();
}
