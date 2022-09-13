#include "Big_Ball.h"
#include "Resource_Manager.h"
#include "Wall.h"
#include "Projectile.h"
#include <math.h>
#include "Small_Ball.h"
#include "Enemy.h"
#include "Shielded_Player.h"
#include "Default_Player.h"
#include "RoF_Player.h"
#include "Dynamic_Object.h"
#include "Read_From_File.h"


Big_Ball::Big_Ball(int old_Number_Divide, Position& old_pos,
                   sf::Vector2f& old_speed, sf::Vector2f& old_gravity)
{
    Number_Divide  = old_Number_Divide;
    size           = origin_size * pow(factor_encreas,
                                       Number_Divide - Decreas_Divide);
    speed.x        = old_speed.x;
    speed.y        = reset;
    bounce.x       = Bounce;
    gravitySpeed.x = -(old_gravity.x * bounce.x);
    gravitySpeed.y = Gravity_y;

    texture1       = Resource_Manager::load_graphics(Picture);
    rectangle.setTexture  (texture1);
    rectangle.setScale    (size, size);
    rectangle.setPosition (size * texture1.getSize().x,
                           size * texture1.getSize().y);
    rectangle.setOrigin   (0, 0);

    position.top    = old_pos.top;
    position.left   = old_pos.left;
    position.bottom = position.top + size * texture1.getSize().y;
    position.right  = position.left + size * texture1.getSize().x;
    position.width  = size * texture1.getSize().x;
    position.height = size * texture1.getSize().y;
}


Big_Ball::Big_Ball(int old_Number_Divide, int x_var, bool Direction)
{
    texture1      = Resource_Manager::load_graphics(Picture);
    Number_Divide = old_Number_Divide;

    size        = origin_size * pow(factor_encreas,
                                    Number_Divide - Decreas_Divide);
    double xpos = size * texture1.getSize().x;
    double ypos = size * texture1.getSize().y;

    if (Direction == true)
    {
        speed.x = -1*Org_Speed_Big_Ball;
    }
    else
    {
        speed.x = Org_Speed_Big_Ball;
    }
    speed.y        = reset;
    gravitySpeed.x = reset;
    gravitySpeed.y = Gravity_y;
    bounce.x       = Bounce;

    position.top    = -ypos;
    position.bottom = reset;
    position.left   = reset + x_var;
    position.right  = xpos + x_var;
    position.width  = xpos;
    position.height = ypos;

    rectangle.setTexture  (texture1);
    rectangle.setScale    (size, size);
    rectangle.setPosition (position.left, position.top);
}

//Koden i big_ball_change_speed är delvis hämtad från hemsidan,
//https://www.w3schools.com/graphics/tryit.asp?filename=trygame_bouncing
void big_ball_change_speed(sf::Vector2f& speed, Position& position,
                           sf::Vector2f& gravitySpeed, sf::Vector2f& bounce
                           , int Number_Divide)
{
    int Window_Bottom = Read_From_File::window_bottom;
    int max_height{};
    if (Number_Divide == Read_From_File::number_divide3)
    {
        max_height = Read_From_File::max_height_big_ball1;
    }
    else if (Number_Divide == Read_From_File::number_divide2)
    {
        max_height = Read_From_File::max_height_big_ball2;
    }
    else if (Number_Divide == Read_From_File::number_divide1)
    {
        max_height = Read_From_File::max_height_big_ball3;
    }
    if (gravitySpeed.x < max_height)
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


void Big_Ball::update(std::map <std::string, bool> &,
                      std::vector <Object*> &)
{
    big_ball_change_speed(speed, position, gravitySpeed, bounce, Number_Divide);
}


bool Big_Ball::handle_collision(Object* next,
                                std::vector <Object*> & Screen_objects)
{
  if (dynamic_cast<Wall*>(next))
  {
      speed.x         = -1 * (speed.x);
      position.left  += speed.x / abs(speed.x);
      position.right += speed.x / abs(speed.x);
      return false;
  }
  else if (dynamic_cast<Projectile*>(next))
  {
      if (Number_Divide >= 2)
      {
          Number_Divide = Number_Divide - 1;
          Screen_objects.push_back(new Big_Ball(Number_Divide, position,
                                                speed, gravitySpeed));
          speed.x = -1*(speed.x);
          Screen_objects.push_back(new Big_Ball(Number_Divide, position,
                                                speed, gravitySpeed));
          return true;
      }
      else if (Number_Divide == 1)
      {
          speed.x = Read_From_File::org_speed_small_ball;
          Screen_objects.push_back(new Small_Ball(position, speed, gravitySpeed));
          speed.x = -1 * (speed.x);
          Screen_objects.push_back(new Small_Ball(position, speed, gravitySpeed));
          return true;
      }
  }
  else if (dynamic_cast<Default_Player*>(next))
  {
      return true;
  }
  else if (dynamic_cast<RoF_Player*>(next))
  {
      return true;
  }
  else if (dynamic_cast<Shielded_Player*>(next))
  {
      return true;
  }
  return false;
}
