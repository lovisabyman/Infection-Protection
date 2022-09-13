//Headerfil för klassen Static_Object.
#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
#include "Object.h"
#include <vector>

class Static_Object: public Object
{
public:
    Static_Object(){}
    void update(std::map <std::string, bool> &, std::vector <Object*> &)
                override
    {}
    virtual bool handle_collision(Object* next,
                                  std::vector <Object*> & Screen_objects) = 0;
    void render(sf::RenderWindow*& window) override;
};

#endif
