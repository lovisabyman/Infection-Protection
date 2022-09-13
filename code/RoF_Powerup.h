#ifndef ROF_POWERUP_H
#define ROF_POWERUP_H
#include "Powerup.h"
#include "Read_From_File.h"

class RoF_powerup
    : public Powerup
{
public:
    RoF_powerup(int xpos);
    bool handle_collision(Object* next, std::vector <Object*> & Screen_objects)
         override;
private:
    float       Height  {Read_From_File::rof_powerup_height};
    float       Width   {Read_From_File::rof_powerup_width};
    float       Scale   {Read_From_File::rof_scale};
    std::string Picture {Read_From_File::rof_powerup_pic};
};

#endif
