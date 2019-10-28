#include "Conga.h"

// -------------------------------------------------------------------------
Conga::
Conga( const std::string& obj_fname )
{
    this->m_MonkeyBodyMesh = new Mesh(obj_fname);
    this->m_MonkeyBodyMesh->setColor(0.729411,0.474509,0.184313);
}

Conga::
~Conga()
{

}
void Conga::
addMonkey(float xAnt, float zAnt)
{
    if(this->m_Conga.empty())
    {
        this->m_Conga.push_back(new Monkey("mono_body.txt",&this->m_MonkeyBodyMesh));
    }
    else
    {
        Monkey* oldTail = this->m_Conga[this->m_Conga.size()-1];
        this->m_Conga.push_back(new Monkey("mono_body.txt",&this->m_MonkeyBodyMesh));
        this->m_Conga[this->m_Conga.size()-1]->setCoordX(xAnt);
        this->m_Conga[this->m_Conga.size()-1]->setCoordY(oldTail->getCoordY());
        this->m_Conga[this->m_Conga.size()-1]->setCoordZ(zAnt);
        this->m_Conga[this->m_Conga.size()-1]->setQuaternionAxis(this->m_Conga[this->m_Conga.size()-2]->getQuaternionAxis());
        this->m_Conga[this->m_Conga.size()-1]->setQuaternionReal(this->m_Conga[this->m_Conga.size()-2]->getQuaternionReal());
    }
}

std::vector<Monkey*> Conga::
getMonkeys()
{
    return this->m_Conga;
}


void Conga::
moveMonkeys(int direction)
{
    if(this->m_Conga.size() > 1 )
    {
        for(unsigned int i = this->m_Conga.size()-1;i > 0; i--)
        {
            this->m_Conga[i]->setCoordX(this->m_Conga[i-1]->getCoordX());
            this->m_Conga[i]->setCoordZ(this->m_Conga[i-1]->getCoordZ());
            this->m_Conga[i]->setQuaternionAxis(this->m_Conga[i-1]->getQuaternionAxis());
            this->m_Conga[i]->setQuaternionReal(this->m_Conga[i-1]->getQuaternionReal());
        }
    }
    switch(direction)
        {
        case 1:
            if (this->m_ActualDirection != 2)
            {
                if(this->m_ActualDirection == 3)
                {
                    this->m_Conga[0]->rotateY(-11);
                }
                else if (this->m_ActualDirection == 4)
                {
                    this->m_Conga[0]->rotateY(11);
                }
                this->m_Conga[0]->increaseCoordX();
                this->m_ActualDirection = 1;
            }
            break;
        case 2:
            if (this->m_ActualDirection != 1)
            {
                if(this->m_ActualDirection == 3)
                {
                    this->m_Conga[0]->rotateY(11);
                }
                else if (this->m_ActualDirection == 4)
                {
                    this->m_Conga[0]->rotateY(-11);
                }
                this->m_ActualDirection = 2;
                this->m_Conga[0]->decreaseCoordX();
            }
            break;
        case 3:
            if (this->m_ActualDirection != 4)
            {
                if(this->m_ActualDirection == 1)
                {
                    this->m_Conga[0]->rotateY(11);
                }
                else if (this->m_ActualDirection == 2)
                {
                    this->m_Conga[0]->rotateY(-11);
                }
                this->m_ActualDirection = 3;
                this->m_Conga[0]->increaseCoordZ();
            }
            break;
        case 4:
            if (this->m_ActualDirection != 3)
            {
                if(this->m_ActualDirection == 1)
                {
                    this->m_Conga[0]->rotateY(-11);
                }
                else if (this->m_ActualDirection == 2)
                {
                    this->m_Conga[0]->rotateY(11);
                }
                this->m_ActualDirection = 4;
                this->m_Conga[0]->decreaseCoordZ();
            }
            break;
        }
}
void Conga::
drawInOpenGLContext( GLenum mode )
{
    for(unsigned int i = 0 ; i < this->m_Conga.size(); i++)
    {
        this->m_Conga[i]->drawInOpenGLContext(mode);
    }
}
