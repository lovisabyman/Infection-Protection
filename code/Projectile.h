#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Dynamic_Object.h"
#include "Read_From_File.h"

class Projectile :public Dynamic_Object
{
public:
    Projectile(Position& player_position);
    void update(std::map <std::string, bool> & inputs,
                std::vector <Object*> & Screen_objects) override;
    void render(sf::RenderWindow*& window) override;
    bool handle_collision(Object* next,
                          std::vector <Object*> & Screen_objects) override;
private:
    int         Projectile_Speed {Read_From_File::projectile_speed};
    float       Scale_Projectile {Read_From_File::scale_projectile};
    std::string Picture          {Read_From_File::projectile_file};
};

#endif
