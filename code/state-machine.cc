#include "State.h"
#include "Resource_Manager.h"
#include "Start_Menu.h"
#include "Game.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Read_From_File.h"

using namespace sf;
int const width {900};
int const height {600};

int main()
{
  Read_From_File rff{};
  RenderWindow window(VideoMode { width, height }, "Infection protection");
  window.setFramerateLimit(Read_From_File::framerate);
  RenderWindow* window_ptr{&window};
  // State *state = new Start_Menu(window_ptr);
  State *state = new Start_Menu(window_ptr);
  State *next_state{state};

  while(next_state != 0)
  {
     state -> handle();
     next_state = state -> update();
     state -> render();
     if (next_state != state)
     {
       state = next_state;
     }
  }

  window.close();

  return 0;
}
