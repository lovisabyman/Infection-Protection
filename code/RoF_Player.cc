#include "RoF_Player.h"
#include "Default_Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Wall.h"
#include "Resource_Manager.h"
#include "Read_From_File.h"

RoF_Player::RoF_Player(Position& start_position)
{
    speed.x  = Speed_Player;
    position = start_position;
    texture1 = Resource_Manager::load_graphics(Picture);
    load_player_image(position, texture1, rectangle);
}

void RoF_Player::update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & screen_objects)
//This section of the code is partly inspierd by lecture 8 in the course TDDC76
//at Linköpings university. https://gitlab.ida.liu.se/TDDI82/SFML-exempel
{
    change_player_position(inputs, speed, position);
    if(RoF_timer > 0)
    {
        RoF_timer--;
    }
    if (inputs.at("Up_arrow") == true && RoF_timer == 0)
    {
        screen_objects.push_back(new Projectile(position));
        RoF_timer = new_RoF_limit;
    }
    inputs.at("Up_arrow") = false;
    remaining_time--;
    if (remaining_time == 0)
    {
        for (unsigned int i = 0; i < screen_objects.size(); i++)
        {
            if (screen_objects.at(i) == this)
            {
                screen_objects.erase(screen_objects.begin() + i);
            }
        }
        screen_objects.push_back(new Default_Player(position));
        delete this;
    }
}

bool RoF_Player::handle_collision(Object* next, std::vector <Object*> &)
{
    if (dynamic_cast<Wall*>(next))
    {
        position.left  -= speed.x;
        position.right -= speed.x;
        return false;
    }
    else if (dynamic_cast<Enemy*>(next))
    {
        return true;
    }
    return false;
}
