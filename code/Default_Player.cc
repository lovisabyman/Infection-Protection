#include "Default_Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Enemy.h"
#include "Resource_Manager.h"
#include "Player.h"
#include "Read_From_File.h"

Default_Player::Default_Player(Position& start_position)
{
    speed.x  = Speed_Player;
    position = start_position;
    texture1 = Resource_Manager::load_graphics(Picture);
    load_player_image(position, texture1, rectangle);
}

void Default_Player::update(std::map <std::string, bool> & inputs,
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
        RoF_timer = RoF_limit;
    }
    inputs.at("Up_arrow") = false;
}

bool Default_Player::handle_collision(Object* next, std::vector <Object*> &)
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
