#include "Powerup.h"
#include "Read_From_File.h"



void Powerup::change_speed()
{
    float Straight_Line{Read_From_File::powerup_beeline};
    if(position.top > Straight_Line)
    {
        speed.y = 0;
    }
}

void Powerup::update(std::map <std::string, bool> &,
                     std::vector <Object*> & Screen_objects)
{
    change_speed();
    position.left   += speed.x;
    position.right  += speed.x;
    position.top    += speed.y;
    position.bottom += speed.y;

    if (timer-- == 0)
    {
        auto it = std::find(Screen_objects.begin(), Screen_objects.end(), this);
        Screen_objects.erase(it);
        delete this;
    }
}

void Powerup::render(sf::RenderWindow*& window)
{
    rectangle.setPosition(position.left, position.top);
    window -> draw (rectangle);
}

//Vet ej om behövs
int   Speed_Powerup    {Read_From_File::speed_powerup};
float Straight_Line    {Read_From_File::powerup_beeline};
int   Start_Left_Limit {Read_From_File::start_left_limit};
int   End_Left_Limit   {Read_From_File::end_left_limit};
int   End_Right_Limit  {Read_From_File::end_right_limit};
int   Powerup_right    {Read_From_File::powerup_right};
int   Powerup_left     {Read_From_File::powerup_left};
