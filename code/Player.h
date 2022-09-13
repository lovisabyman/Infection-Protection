#ifndef PLAYER_H
#define PLAYER_H
#include "Dynamic_Object.h"
#include "Read_From_File.h"


class Player
    : public Dynamic_Object
{
public:
    Player(){}
    virtual void update(std::map <std::string, bool> & inputs,
                        std::vector <Object*> & Screen_objects) = 0;
    virtual bool handle_collision(Object* next,
                                  std::vector <Object*> & Screen_objects) = 0;
    void render(sf::RenderWindow*& window) override;
protected:
    int   RoF_timer   {};
    int   RoF_limit   {Read_From_File::rof_limit};
    float Speed_Player{Read_From_File::speed_player};
};

void load_player_image(Position& position, sf::Texture& texture1,
                       sf::Sprite& rectangle);
void change_player_position(std::map <std::string, bool> & inputs,
                            sf::Vector2f& speed, Position& position);

#endif
