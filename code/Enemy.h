#ifndef ENEMY_H
#define ENEMY_H
#include "Dynamic_Object.h"
#include <vector>
#include "Read_From_File.h"

class Enemy: public Dynamic_Object
{
public:
    Enemy(){}
    virtual void update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & Screen_objects) = 0;
    virtual bool handle_collision(Object* next,
                                  std::vector <Object*> & Screen_objects) = 0;
    void render(sf::RenderWindow*& window) override;

    sf::Vector2f gravitySpeed {reset,reset}; //gravitySpeed & gravity
    sf::Vector2f bounce       {reset,reset}; //bounce

};

#endif
