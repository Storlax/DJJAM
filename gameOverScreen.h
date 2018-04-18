//
// Created by miami on 4/16/2018.
//

#ifndef DJJAM_GAMEOVERSCREEN_H
#define DJJAM_GAMEOVERSCREEN_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <windows.h>
//TODO: fix loop back to first screen
class gameOverScreen : public cScreen
{
public:
    virtual int Run(sf::RenderWindow &App);
};

int gameOverScreen::Run(sf::RenderWindow &App) {
    std::cout << "I'm working";
    sf::Texture placeHolder;
    placeHolder.loadFromFile("../cmake_modules/Images/background.png");
    sf::Sprite bg(placeHolder);
    App.draw(bg);

    App.display();
    //Sleep(10000);
    return 0;
}

#endif //DJJAM_GAMEOVERSCREEN_H
