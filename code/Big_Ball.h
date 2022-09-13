#ifndef BIG_BALL_H
#define BIG_BALL_H
#include "Enemy.h"
#include <vector>

class Big_Ball: public Enemy
{
public:
    Big_Ball(int old_Number_Divide, Position& old_pos, sf::Vector2f& old_speed,
             sf::Vector2f& old_gravity);
    Big_Ball(int old_Number_Divide, int x_var, bool Direction);
    void update(std::map <std::string, bool> & inputs,
                std::vector <Object*> & Screen_objects) override;
    bool handle_collision(Object* next,
                          std::vector <Object*> & Screen_objects) override;

private:
    double      size{};
    int         Number_Divide{};
    int         x_var{};
    bool        Direction{};

    float       origin_size       {Read_From_File::origin_size_ball};
    int         factor_encreas    {Read_From_File::ball_encrease_size};
    float       Org_Speed_Big_Ball{Read_From_File::org_speed_big_ball};
    int         Bounce            {Read_From_File::bounce_ball};
    int         Decreas_Divide    {Read_From_File::decreas_divide};
    float       Gravity_y         {Read_From_File::Gravity_Y};
    std::string Picture           {Read_From_File::ball_file};

};

void big_ball_change_speed(sf::Vector2f& speed, Position& position,
                           sf::Vector2f& gravitySpeed, sf::Vector2f& bounce,
                           int Number_Divide);

#endif
