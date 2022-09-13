#include <SFML/Graphics.hpp> // includes most things in SFML

using namespace sf;

int const width  { 640 };
int const height { 480 };
std::string object;

std::string choose_object(std::string object)
{
  return object;
}

int main ()
{
    RenderWindow window {
        VideoMode { width, height },
        "SFML DEMO"
    };
    Texture texture1;
    if ( !texture1.loadFromFile (choose_object("handsprit.png")) )
    {
        // gick inte att ladda bilden
        return 1;
    }
    Sprite circle { texture1 };
    circle.setScale(0.07, 0.07);
    circle.setPosition (width / 2, height / 2);

    auto size { texture1.getSize () };
    circle.setOrigin (size.x/2, size.y/2 );

    /* ladda in en texture (bild) */
    Texture texture;
    if ( !texture.loadFromFile (choose_object("tegnell.png")) )
    {
        // gick inte att ladda bilden
        return 1;
    }

    // skapa sprite
    Sprite sprite { texture };
    sprite.setPosition (width / 2, height / 2);
    sprite.setScale(0.3, 0.3);

    // sätt origin på sprite till mitten
    auto size1 { texture.getSize () };
    sprite.setOrigin (size1.x / 2, size1.y / 2);

    float const speed { 4.0 };

    // skapa en klocka
    Clock clock;

    double const fps { 60.0 };

    // beräkna hur lång tid vi har per frame
    auto const target { milliseconds (1000.0 / fps) };

    /* skapa text */
    Font font;
    if ( !font.loadFromFile ("font.ttf") )
    {
        // kunde inte ladda typsnitt
        return 2;
    }

    // skapa text objekt
    Text text { "Bubble trouble remake", font };

    auto bounds { text.getGlobalBounds () };
    text.setPosition ((width - bounds.width) / 2, 0);

    // loopa sålänge fönstret finns
    while ( window.isOpen () )
    {
        // börja tidtagning
        clock.restart ();

        /* hantera events */
        Event event;
        // hämta ett event i taget
        while ( window.pollEvent (event) )
      {

        if ( Keyboard::isKeyPressed (Keyboard::Key::W) )
        {
            sprite.setRotation (0);

            circle.move (0, -speed);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::A) )
        {

            sprite.move (-speed, 0);
            circle.move (-speed, 0);
        }
        else if ( Keyboard::isKeyPressed (Keyboard::Key::D) )
        {

            sprite.move (speed, 0);
            circle.move (speed, 0);
        }

        auto sprite_box { sprite.getGlobalBounds () };
        auto circle_box { circle.getGlobalBounds () };

        /* rita ut */
        window.clear (); // rensa skärmen

        window.draw (text); // rita ut texten

        if ( Keyboard::isKeyPressed (Keyboard::Key::W) )
        {
        window.draw (circle);
        }
        else{
          circle.setPosition(sprite.getPosition());
        }


        window.draw (sprite); // rita ut bilden

        window.display (); // visa ändringarna

        // räkna ut hur lång tid vi har kvar tills nästa
        // frame ska börja
        auto wait_time { target - clock.getElapsedTime () };

        // vänta tiden som blev över
        sleep (wait_time);
    }}
}
