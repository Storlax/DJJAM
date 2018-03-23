//finally got this working; only took 10 hours!
//learn about time.h; apparently that's a thing

#include <SFML/Graphics.hpp>
#include<iostream>
#include "player.cpp"
#include "game.cpp"

//this includes the standard functions in SFML's custom namespace which saves us an assload of "sf::insertCrapHere"
using namespace sf;
//who uses structs anymore? I guess C is useful; probably better to do this in a class; just declaring coordinates

int main()
{
    std::cout<< "Michael you're famous";
    //renders a window of size whatever I've declared; check parameters
    RenderWindow app(VideoMode(400, 533), "DJJAM");
    //sets framerate maximum to stop the program from seizing
    app.setFramerateLimit(60);

    //loads textures from files, duhhh
    Texture t1,t2;
    t1.loadFromFile("../cmake_modules/Images/background.png");
    t2.loadFromFile("../cmake_modules/Images/platform.png");

    Player player;
    //declaring the different images for their respective parts in the game (the person, platform, and background)
    Sprite sBackground(t1), sPlat(t2);
    Sprite sPersL(player.t1);
    Sprite sPersR(player.t2);

    Sprite currentSprite = sPersL;

    //not sure what this one does; research
    point plat[20];

    for (int i = 0; i < 10;i++)
    {
        //seems to be setting the location of the platforms randomly
        plat[i].x = rand()%400;
        plat[i].y = rand()%533;
    }

    //starting locations yay!
    int x = 100,y = 100,h = 200;
    //good ol' changes in positions
    float dx = 0,dy = 0;

    //most self explanatory line on earth
    while (app.isOpen())
    {
        //declaring an event
        Event e;
        //research this
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
        //nice built in functions to detect key movement; ya love to see it!
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            currentSprite = sPersR;
            x += 3;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            currentSprite = sPersL;
            x-=3;
        }

        //good ol' gravity
        dy+=0.2;
        //changes the current position to account for movement
        y+=dy;
        if (y>500)  dy=-10;

        if (y<h)
            for (int i=0;i<10;i++)
            {
                y=h;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
            }

        for (int i=0;i<10;i++)
            if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
                && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))  dy=-10;

        currentSprite.setPosition(x,y);

        app.draw(sBackground);
        app.draw(currentSprite);
        for (int i=0;i<10;i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    return 0;
}
