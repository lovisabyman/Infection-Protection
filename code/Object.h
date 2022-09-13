//Headerfil för klassen Object.
#ifndef OBJECT_H
#define OBJECT_H
#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Read_From_File.h"

struct Position
{
    //Origo på ett objekts position är i vänstra översta hörnet.
    //Medför att x-koord för ett objekt = left
    //Medför att y-koord för ett objekt = top
    float top;
    float bottom;
    float left;
    float right;
    float width;
    float height;
};

class Object
{
public:
    Object() : texture1{}, rectangle{}
    {}
    virtual ~Object() = default;
    Position get_position();
    virtual void update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & Screen_objects) = 0;
    virtual bool handle_collision(Object* next,
                                  std::vector <Object*> & Screen_objects) = 0;
    virtual void render(sf::RenderWindow*& window) = 0;
protected:
    Position    position { 6, 4, 3, 6, 3, 2};
    float       reset    {Read_From_File::reset_number};
    sf::Texture texture1;
    sf::Sprite  rectangle;


};
#endif
