#ifndef SHIELDED_PLAYER_H
#define SHIELDED_PLAYER_H
#include "Player.h"
#include "Read_From_File.h"
#include <SFML/Graphics.hpp>

class Shielded_Player
    : public Player
{
public:
    Shielded_Player(Position& start_position);
    void update(std::map <std::string, bool> & inputs,
                std::vector <Object*> & Screen_objects) override;
    bool handle_collision(Object* next,
                          std::vector <Object*> & Screen_objects) override;
private:
    int         remaining_time{Read_From_File::remaining_time_shielded};
    std::string Picture       {Read_From_File::shield_player_pic};
};

#endif
