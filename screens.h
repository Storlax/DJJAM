//
// Created by nick on 4/13/2018.
//

#ifndef DJJAM_SCREENS_H
#define DJJAM_SCREENS_H

//Basic Screen Class
#include "cScreen.h"

//Including each screen of application
#include "menuScreen.h"
#include "gameScreen.h"

static const string gameName = "DJJAM";
//this holds all the information for our screens
class screens
{
private:
    static const unsigned int windowHeight = 533;
    static const unsigned int windowWidth = 400;
    static const unsigned int antialiasingLevel = 8;
public:
    void initialize();
};

void screens::initialize() {
    //Applications variables
    std::vector<cScreen*> Screens;
    int screenNumber = 0;

    //Window creation
    sf::RenderWindow App(sf::VideoMode(windowWidth, windowHeight, antialiasingLevel), gameName);

    //Mouse cursor no more visible
    App.setMouseCursorVisible(false);

    //Screens preparations
    menuScreen s0;
    Screens.push_back(&s0);
    gameScreen s1;
    Screens.push_back(&s1);

    //Main loop
    while (screenNumber >= 0)
    {
        if(screenNumber == 0) {
            screenNumber = Screens[screenNumber]->Run(App);
        } else if (screenNumber == 1) {
            screenNumber = Screens[screenNumber]->Run(App);
        }
    }
}
#endif //DJJAM_SCREENS_H
