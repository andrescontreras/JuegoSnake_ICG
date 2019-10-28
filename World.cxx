#include "World.h"

World::
World()
{
  this->m_BananaMesh = new Mesh("Banana.obj");
  this->m_Banana     = new Banana("banana.txt",&this->m_BananaMesh);
  this->m_Conga      = new Conga("MonitoSpider.obj");
  this->m_Obstacle   = new Obstacle("RattleSnake.obj");
  this->m_Obstacle->addObstacle();
  this->m_Conga->addMonkey(0,0);
  std::vector<Monkey*> monkeys = this->m_Conga->getMonkeys();
  std::map<std::pair<float,float>,Object*> notPosible = this->m_Obstacle->getObstacles();
  for(unsigned int i = 0; i <monkeys.size(); i++ )
  {
        std::pair<float,float> coords(monkeys[i]->getCoordX(),monkeys[i]->getCoordZ());
        std::map<std::pair<float,float>,Object*>::iterator it = notPosible.begin();
        notPosible.insert(it,std::pair<std::pair<float,float>,Object*> (coords,nullptr));
  }
  this->m_Banana->placeBanana(notPosible);
}

World::
~World()
{

}

bool World::
moveMonkeys(int dir)
{
    std::vector<Monkey*> monkeys = this->m_Conga->getMonkeys();
    std::pair<float,float> xz (monkeys[0]->getCoordX(),monkeys[0]->getCoordZ());
    std::pair<float,float> chg (monkeys[monkeys.size()-1]->getCoordX(),monkeys[monkeys.size()-1]->getCoordZ());
    std::map<std::pair<float,float>,Object*> notPosible = this->m_Obstacle->getObstacles();
    monkeys.erase(monkeys.begin());
    for(unsigned int i = 0; i <monkeys.size(); i++ )
    {
        std::pair<float,float> coords(monkeys[i]->getCoordX(),monkeys[i]->getCoordZ());
        std::map<std::pair<float,float>,Object*>::iterator it = notPosible.begin();
        notPosible.insert(it,std::pair<std::pair<float,float>,Object*> (coords,nullptr));
    }
    if(notPosible.find(xz) == notPosible.end())
    {
        this->m_Conga->moveMonkeys(dir);
    }
    if(xz.first == this->m_Banana->getCoordX() && xz.second == this->m_Banana->getCoordZ() )
    {
           std::map<std::pair<float,float>,Object*>::iterator it = notPosible.begin();
           notPosible.insert(it,std::pair<std::pair<float,float>,Object*> (xz,nullptr));
           this->m_Banana->placeBanana(notPosible);
           this->m_Conga->addMonkey(chg.first, chg.second);
           monkeys = this->m_Conga->getMonkeys();
    }
    return true;
}

void World::
drawInOpenGLContext(GLenum mode)
{
    this->m_Conga->drawInOpenGLContext(mode);
    this->m_Obstacle->drawInOpenGLContext(mode);
    this->m_Banana->drawInOpenGLContext(mode);
}
