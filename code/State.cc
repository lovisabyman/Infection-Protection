#include "State.h"
#include <SFML/Graphics.hpp>

using namespace sf;

State::State(RenderWindow* incoming_window_ptr) :
             window_ptr{incoming_window_ptr},
             window_size{incoming_window_ptr->getSize()} {}
