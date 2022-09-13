
CCC = g++
CFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -fmax-errors=3 -g
LDFLAGS = -lsfml-window -lsfml-graphics -lsfml-system
OBJS = State.o Start_Menu.o End_Menu.o Highscore_Menu.o Help_Menu.o Game.o Button.o Object.o Player.o Default_Player.o State_Machine.o Dynamic_Object.o Static_Object.o Wall.o Resource_Manager.o Enemy.o Big_Ball.o Small_Ball.o Powerup.o Projectile.o RoF_Powerup.o Shielded_Powerup.o Read_From_File.o RoF_Player.o Shielded_Player.o New_Highscore.o
play: $(OBJS)
	$(CCC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cc %.h
	$(CCC) $(CFLAGS) -c $<

clean:
	\rm *.o play
