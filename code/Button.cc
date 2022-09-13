#include "Button.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

Button::Button(std::string n, Vector2u s, Vector2f p) : name{n}, size{s}, position{p} {}

bool Button::is_pressed(int mouse_x, int mouse_y)
{
    if (mouse_x > position.x && mouse_x < position.x + size.x &&
        mouse_y > position.y && mouse_y < position.y + size.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}
