#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Dynamic_Object: public Object
{
public:
    Dynamic_Object(){}
    virtual void update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & Screen_objects) = 0;
    virtual bool handle_collision(Object* next,
                                  std::vector <Object*> & Screen_objects) = 0;
    virtual void render(sf::RenderWindow*& window) = 0;

protected:
    sf::Vector2f speed{0, 0};

};


#endif
