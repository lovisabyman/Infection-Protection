#include "Small_Ball.h"
#include "Resource_Manager.h"
#include <math.h>
#include "Wall.h"
#include "Projectile.h"
#include "Shielded_Player.h"
#include "Default_Player.h"
#include "RoF_Player.h"
#include "Read_From_File.h"


Small_Ball::Small_Ball(Position& old_pos, sf::Vector2f& old_speed,
                       sf::Vector2f& old_gravity)
    : x_var{}
{
    texture1 = Resource_Manager::load_graphics(Picture);
    speed.x        = old_speed.x;
    speed.y        = reset;
    gravitySpeed.x = -(old_gravity.x * bounce.x);
    gravitySpeed.y = Gravity_y;
    bounce.x       = Bounce;

    position.top    = old_pos.top;
    position.left   = old_pos.left;
    position.bottom = position.top  + Size_Ball * texture1.getSize().y;
    position.right  = position.left + Size_Ball * texture1.getSize().x;
    position.width  = Size_Ball * texture1.getSize().x;
    position.height = Size_Ball * texture1.getSize().y;

    rectangle.setTexture (texture1);
    rectangle.setScale   (Size_Ball, Size_Ball);
    rectangle.setPosition(Size_Ball * texture1.getSize().x,
                          Size_Ball * texture1.getSize().y);
}

Small_Ball::Small_Ball(int x_var, bool Direction)
    : x_var{}
{
    texture1 = Resource_Manager::load_graphics(Picture);
    double xpos = Size_Ball * texture1.getSize().x;
    double ypos = Size_Ball * texture1.getSize().y;

    if (Direction == true)
    {
        speed.x = -1*Org_Speed_Small_Ball;
    }
    else
    {
        speed.x = Org_Speed_Small_Ball;
    }
    speed.y     = reset;

    gravitySpeed.x = reset;
    gravitySpeed.y = Gravity_y;
    bounce.x       = Bounce;

    //Baserat på bildens storlek, skalning och placering.
    position.top    = -ypos;
    position.bottom = reset;
    position.left   = reset + x_var;
    position.right  = xpos  + x_var;
    position.width  = xpos;
    position.height = ypos;

    rectangle.setTexture (texture1);
    rectangle.setScale   (Size_Ball, Size_Ball);
    rectangle.setPosition(position.left, position.top);
}

//Koden i small_ball_change_speed är delvis hämtad från hemsidan
//https://www.w3schools.com/graphics/tryit.asp?filename=trygame_bouncing
void small_ball_change_speed(sf::Vector2f& speed, Position& position,
                             sf::Vector2f& gravitySpeed, sf::Vector2f& bounce)
{
    int Window_Bottom  = Read_From_File::window_bottom;
    if (gravitySpeed.x < Read_From_File::max_height_small_ball)
    {
        gravitySpeed.x = gravitySpeed.x + gravitySpeed.y;
    }
    position.left   = position.left   + speed.x;
    position.right  = position.right  + speed.x;
    position.top    = position.top    + (speed.y + gravitySpeed.x);
    position.bottom = position.bottom + (speed.y + gravitySpeed.x);

    if (position.bottom > Window_Bottom)
    {
        gravitySpeed.x  = -(gravitySpeed.x * bounce.x);
        position.bottom = Window_Bottom   - 1;
        position.top    = position.bottom - position.height;
    }
}

void Small_Ball::update(std::map <std::string, bool> &,
                        std::vector <Object*> &)
{
    small_ball_change_speed(speed, position, gravitySpeed, bounce);
}

bool Small_Ball::handle_collision(Object* next, std::vector <Object*> &)
{
    if (dynamic_cast<Wall*>(next))
    {
        speed.x *= -1;
        position.left  += speed.x / abs(speed.x);
        position.right += speed.x / abs(speed.x);
        return false;
    }
    else if (dynamic_cast<Projectile*>(next))
    {
        return true;
    }
    else if (dynamic_cast<Shielded_Player*>(next))
    {
        return true;
    }
    else if (dynamic_cast<Default_Player*>(next))
    {
        return true;
    }
    else if (dynamic_cast<RoF_Player*>(next))
    {
        return true;
    }
    return false;
}
