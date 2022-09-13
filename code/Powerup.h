#ifndef POWERUP_H
#define POWERUP_H
#include "Dynamic_Object.h"
#include "Read_From_File.h"

class Powerup :public Dynamic_Object
{
public:
    Powerup(){}
    void update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & Screen_objects) override;
    void render(sf::RenderWindow*& window) override;
    virtual bool handle_collision(Object* next,
                                  std::vector <Object*> & Screen_objects) = 0;

protected:
    int Speed_Powerup {Read_From_File::speed_powerup};
    int timer         {Read_From_File::time_powerup};
    void change_speed();

};


#endif
