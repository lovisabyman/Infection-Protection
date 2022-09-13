#ifndef WALL_H
#define WALL_H
#include "Static_Object.h"
#include "Read_From_File.h"

class Wall: public Static_Object
{
public:
    Wall(Position& wall_position);
    bool handle_collision(Object* next,
                          std::vector <Object*> & Screen_objects) override;
private:
    std::string Picture{Read_From_File::wall_pic};
};

#endif
