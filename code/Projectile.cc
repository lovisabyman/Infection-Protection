#include "Projectile.h"
#include "Enemy.h"
#include "Powerup.h"
#include "Resource_Manager.h"
#include <math.h>
#include <iostream>


Projectile::Projectile(Position& player_position)
//This section of the code is partly inspierd by lecture 8 in the course TDDC76
//at Linköpings university. https://gitlab.ida.liu.se/TDDI82/SFML-exempel
{
    texture1 = Resource_Manager::load_graphics(Picture);

    speed.y     = Projectile_Speed;
    float scale = Scale_Projectile;
    float xpos  = scale * texture1.getSize().x;
    float ypos  = scale * texture1.getSize().y;

    position.width        = xpos;
    position.height       = ypos;
    position.top          = player_position.top  - position.height;
    position.bottom       = player_position.top;
    float player_x_center = player_position.left + (player_position.width / 2);
    position.left         = player_x_center      - (position.width / 2);
    position.right        = player_x_center      + (position.width / 2);

    rectangle.setTexture  (texture1);
    rectangle.setScale    (scale, scale);
    rectangle.setPosition (xpos, ypos);

}

void change_projectile_position(std::map <std::string, bool> &,
                                sf::Vector2f& speed, Position& position)
{
    position.top    -= speed.y;
    position.bottom -= speed.y;
}

void Projectile::update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & screen_objects)
{
    change_projectile_position(inputs, speed, position);
    if (position.bottom <= 0)
    {
        for (unsigned int i = 0; i < screen_objects.size(); i++)
        {
            if (screen_objects.at(i) == this)
            {
                screen_objects.erase(screen_objects.begin() + i);
            }
        }
        delete this;
    }
}

bool Projectile::handle_collision(Object* next, std::vector <Object*> &)
{
    if(dynamic_cast<Enemy*>(next))
      {
          return true;
      }
    else if(dynamic_cast<Powerup*>(next))
    {
        return true;
    }
    return false;
}

void Projectile::render(sf::RenderWindow*& window)
{
    rectangle.setPosition(position.left, position.top);
    window -> draw       (rectangle);
}
