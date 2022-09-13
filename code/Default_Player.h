#ifndef DEFAULT_PLAYER_H
#define DEFAULT_PLAYER_H
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Read_From_File.h"

class Default_Player: public Player
{
public:
    Default_Player(Position& start_position);
    void update(std::map <std::string, bool> & inputs,
                std::vector <Object*> & Screen_objects) override;
    bool handle_collision(Object* next,
                          std::vector <Object*> & Screen_objects) override;
private:
    std::string Picture{Read_From_File::def_player};

};




#endif
