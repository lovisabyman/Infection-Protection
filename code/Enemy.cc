#include "Enemy.h"


void Enemy::render(sf::RenderWindow*& window)
{
    rectangle.setPosition(position.left, position.top);
    window -> draw       (rectangle);
}
