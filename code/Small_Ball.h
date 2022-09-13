#ifndef SMALL_BALL_H
#define SMALL_BALL_H
#include "Enemy.h"
#include <vector>
#include "Read_From_File.h"

class Small_Ball :public Enemy
{
public:
    Small_Ball(Position& old_pos, sf::Vector2f& old_speed,
               sf::Vector2f& old_gravity);
    Small_Ball(int x_var, bool Direction);
    void update(std::map <std::string, bool> & inputs,
                std::vector <Object*> & Screen_objects) override;
    bool handle_collision(Object* next, std::vector <Object*> & Screen_objects)
                          override;
private:
    int         x_var{};
    bool        Direction{};
    float       Size_Ball           {Read_From_File::size_small_ball};
    float       Gravity_y           {Read_From_File::Gravity_Y};
    int         Bounce              {Read_From_File::bounce_ball};
    float       Org_Speed_Small_Ball{Read_From_File::org_speed_small_ball};
    std::string Picture             {Read_From_File::ball_file};

};

//Alice: Ska man kunna nå den här funktionen utanför klassen? Om nej tror jag
//inte den ska stå med här.
void small_ball_change_speed(sf::Vector2f& speed, Position& position,
                             sf::Vector2f& gravitySpeed, sf::Vector2f& bounce);


#endif
