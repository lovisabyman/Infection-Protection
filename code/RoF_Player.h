#ifndef ROF_PLAYER_H
#define ROF_PLAYER_H
#include "Player.h"
#include <SFML/Graphics.hpp>

class RoF_Player
    : public Player
{
public:
    RoF_Player(Position& start_position);
    void update(std::map <std::string, bool> & inputs,
                std::vector <Object*> & Screen_objects) override;
    bool handle_collision(Object* next, std::vector <Object*> & Screen_objects)
         override;
private:
    int new_RoF_limit  {Read_From_File::rof_timer};
    int remaining_time {Read_From_File::remaining_time_rof};
    std::string Picture{Read_From_File::rof_player_pic};
};

#endif
