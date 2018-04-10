//finally got this working; only took 10 hours!
//learn about time.h; apparently that's a thing

#include <SFML/Graphics.hpp>
#include "game.h"

//this includes the standard functions in SFML's custom namespace which saves us an assload of "sf::insertCrapHere"
using namespace sf;
//who uses structs anymore? I guess C is useful; probably better to do this in a class; just declaring coordinates

int main()
{

    gameLoop gLoop;

    gLoop.initialize();

    gLoop.update();

    return 0;
}
