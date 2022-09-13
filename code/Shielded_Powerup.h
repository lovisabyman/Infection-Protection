#ifndef SHIELDED_POWERUP_H
#define SHIELDED_POWERUP_H
#include "Powerup.h"

class Shielded_powerup
    : public Powerup
{
public:
    Shielded_powerup(int xpos);
    bool handle_collision(Object* next, std::vector <Object*> & Screen_objects)
         override;
private:
    float       Height{Read_From_File::shield_powerup_height};
    float       Width{Read_From_File::shield_powerup_width};
    float       Scale{Read_From_File::scale_shield_powerup};
    std::string Picture{Read_From_File::shield_powerup_pic};
};

#endif
