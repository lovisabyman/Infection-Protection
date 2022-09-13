#include "Player.h"
#include <iostream>

void load_player_image(Position& position, sf::Texture& texture1,
                       sf::Sprite& rectangle)
{
    rectangle.setTexture(texture1);
    float scale_width {position.width  / texture1.getSize().x};
    float scale_height{position.height / texture1.getSize().y};
    rectangle.setScale    (scale_width, scale_height);
    rectangle.setPosition (position.left, position.top);
}

void change_player_position(std::map <std::string, bool> & inputs,
                                     sf::Vector2f& speed, Position& position)
{
    float Speed_Player{Read_From_File::speed_player};
    if (inputs.at("Right_arrow") == true)
    {
        speed.x = Speed_Player;
        position.left  += speed.x;
        position.right += speed.x;
        inputs.at("Right_arrow") = false;
    }
    else if (inputs.at("Left_arrow") == true)
    {
        speed.x = -Speed_Player;
        position.left  += speed.x;
        position.right += speed.x;
        inputs.at("Left_arrow") = false;
    }
}

void Player::render(sf::RenderWindow*& window)
{
    rectangle.setPosition(position.left, position.top);
    if (speed.x > 0)
    {
        window -> draw(rectangle);
    }
    else if (speed.x < 0)
    {
        rectangle.scale      (-1, 1);
        rectangle.setOrigin  (0, 0);
        rectangle.setPosition(position.left + position.width, position.top);
        window -> draw       (rectangle);
        rectangle.scale      (-1, 1);
        rectangle.setOrigin  (0, 0);
        rectangle.setPosition(position.left, position.top);
    }
}