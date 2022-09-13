#include "Wall.h"
#include "Dynamic_Object.h"
#include "Resource_Manager.h"
#include <iostream>

Wall::Wall(Position& wall_position)
{
    position.top    = wall_position.top;
    position.bottom = wall_position.bottom;
    position.left   = wall_position.left;
    position.right  = wall_position.right;
    position.width  = wall_position.width;
    position.height = wall_position.height;

    texture1 = Resource_Manager::load_graphics(Picture);

    rectangle.setTexture(texture1);
    float scale_width {position.width / texture1.getSize().x};
    float scale_height{position.height / texture1.getSize().y};
    rectangle.setScale    (scale_width, scale_height);
    rectangle.setPosition (position.left, position.top);
}

bool Wall::handle_collision(Object*, std::vector <Object*> &)
{
    return false;
}
