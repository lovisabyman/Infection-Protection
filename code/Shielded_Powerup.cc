#include "Shielded_Powerup.h"
#include "Resource_Manager.h"
#include "Projectile.h"
#include "Shielded_Player.h"
#include "Default_Player.h"
#include "Object.h"
#include "Read_From_File.h"
#include "Powerup.h"
#include <math.h>
#include "Wall.h"

//the inargument-integer describes from which position
//the powerup enters the screen.
Shielded_powerup::Shielded_powerup(int xpos)
//This section of the code is partly inspierd by lecture 8 in the course TDDC76
//at Linköpings university. https://gitlab.ida.liu.se/TDDI82/SFML-exempel
{
    int End_Left_Limit{Read_From_File::end_left_limit};
    if (xpos > End_Left_Limit)
    {
        speed.x = -Speed_Powerup;
    }
    else
    {
        speed.x = Speed_Powerup;
    }
    speed.y = Speed_Powerup;

    //Baserat på bildens storlek, skalning och placering.
    position.top    = reset;
    position.bottom = Height;
    position.left   = xpos;
    position.right  = xpos + Width;
    position.width  = Width;
    position.height = Height;

    texture1 = Resource_Manager::load_graphics(Picture);
    rectangle.setTexture (texture1);
    rectangle.setScale   (Scale, Scale);
    rectangle.setPosition(Width, Height);
    rectangle.setOrigin  (0, 0);
}

bool Shielded_powerup::handle_collision(Object* next,
                                        std::vector <Object*> & Screen_objects)
{
    if (dynamic_cast<Wall*>(next))
    {
        speed.x = -speed.x;
        return false;
    }
    else if (dynamic_cast<Projectile*>(next))
    {
        Position old_position;
        for (unsigned int i = 0; i < Screen_objects.size(); i++)
        {
            if (dynamic_cast<Player*>(Screen_objects[i]))
            //if the player hits a powerup with the projectile,
            //the player swiches out to one with a powerup upgrade.
            {
                old_position = Screen_objects[i] -> get_position();
                Object* temp{Screen_objects[i]};
                Screen_objects[i] = new Shielded_Player(old_position);
                delete temp;
            }
        }
        return true;
    }
    return false;
}
