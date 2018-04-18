//
// Created by miami on 4/16/2018.
//

#ifndef DJJAM_GAMEOVERSCREEN_H
#define DJJAM_GAMEOVERSCREEN_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
//TODO: fix loop back to first screen
class gameOverScreen : public cScreen
{
private:
    int menu = 0;
    bool running = true;
public:
    virtual int Run(sf::RenderWindow &App);
};

int gameOverScreen::Run(sf::RenderWindow &App) {

    while (running) {

        Event e;

        sf::Text t;
        sf::Font f;
        sf::Text Menu1;
        sf::Text Menu2;
        sf::Text Menu3;

        f.loadFromFile("../cmake_modules/Images/OpenSans-Regular.ttf");
        t.setFont(f);
        t.setCharacterSize(35);
        t.setFillColor(sf::Color::Black);
        t.setPosition(20, 0);

        sf::Texture placeHolder;
        placeHolder.loadFromFile("../cmake_modules/Images/background.png");
        sf::Sprite bg(placeHolder);

        t.setString("GG's");

        Menu1.setFont(f);
        Menu1.setCharacterSize(20);
        Menu1.setString("Play DJJAM");
        Menu1.setPosition({ 20, 100 });

        Menu2.setFont(f);
        Menu2.setCharacterSize(20);
        Menu2.setString("Exit Game");
        Menu2.setPosition({ 20, 200 });

        Menu3.setFont(f);
        Menu3.setCharacterSize(20);
        Menu3.setString("Continue");
        Menu3.setPosition({ 20, 300 });


        while (App.pollEvent(e))
        {
            if (e.type == Event::Closed)
                App.close();
        }


        if (e.type == sf::Event::KeyPressed)
        {
            switch (e.key.code)
            {
                case sf::Keyboard::Up:
                    menu = 0;
                    break;
                case sf::Keyboard::Down:
                    menu = 1;
                    break;
                case sf::Keyboard::Return:
                    if (menu == 0)
                    {   std::cout << "You clicked enter!";
                        return (1);
                    }
                    else
                    {
                        return (-1);
                    }
                    break;
                default:
                    break;
            }
        }

        if (menu == 0)
        {
            Menu1.setFillColor(sf::Color::Red);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::Black);
        }
        else
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::Red);
            Menu3.setFillColor(sf::Color::Black);
        }

        App.clear();

        App.draw(bg);
        App.draw(t);
        App.draw(Menu1);
        App.draw(Menu2);

        App.display();
    }
}

#endif //DJJAM_GAMEOVERSCREEN_H
