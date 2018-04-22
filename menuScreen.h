//
// Created by Nick on 4/13/2018.
//

#ifndef DJJAM_MENUSCREEN_H
#define DJJAM_MENUSCREEN_H

#include <iostream>
#include "cScreen.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>

//our menu screen
class menuScreen : public cScreen
{
private:
    int alpha_max;
    int alpha_div;
    bool playing;
public:
    menuScreen(void);
    virtual int Run(sf::RenderWindow &App);
};


menuScreen::menuScreen(void)
{
    alpha_max = 3 * 255;
    alpha_div = 3;
    playing = false;
}

int menuScreen::Run(sf::RenderWindow &App)
{
    sf::Event Event;
    bool Running = true;
    sf::Texture Texture;
    sf::Sprite Sprite;
    int alpha = 0;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    sf::Text Menu4;
    int menu = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    Sprite.setColor(sf::Color(255, 255, 255, alpha));
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Play DJJAM");
    Menu1.setPosition({ 123, 310 });

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Shader Changer");
    Menu2.setPosition({ 123, 345 });

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("High Score");
    Menu3.setPosition({ 123, 380 });

    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Exit Game");
    Menu4.setPosition({ 123, 415 });

    if (playing)
    {
        alpha = alpha_max;
    }

    while (Running)
    {
        //Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            //Key pressed
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        if (menu != 0)
                        {
                            menu = menu - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (menu != 3)
                        {
                            menu = menu + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0)
                        {
                            //Let's get playing!
                            playing = true;
                            return (1);
                        }
                        else if (menu == 1)
                        {
                            playing = true;
                            return (4);
                        }
                        else if (menu == 2)
                        {
                            playing = true;
                            return (3);
                        }
                        else if (menu == 3)
                        {
                            return (-1);
                        }
                        break;
                    default:
                        std::cout << "what happened ?!?!" << std::endl;
                        break;
                }
            }
        }
        //When getting at alpha_max, we stop modifying the sprite
        if (alpha<alpha_max)
        {
            alpha++;
        }
        Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
        if (menu == 0)
        {
            Menu1.setFillColor(sf::Color::White);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::Black);
            Menu4.setFillColor(sf::Color::Black);
        }
        else if (menu == 1)
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::White);
            Menu3.setFillColor(sf::Color::Black);
            Menu4.setFillColor(sf::Color::Black);
        }
        else if (menu == 2)
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::White);
            Menu4.setFillColor(sf::Color::Black);
        }
        else if (menu == 3)
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::Black);
            Menu4.setFillColor(sf::Color::White);
        }

        //Clearing screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        if (alpha == alpha_max)
        {
//            if (playing)
//            {
//                App.draw(Menu3);
//            }
//            else
//            {
//                App.draw(Menu1);
//            }
//            App.draw(Menu2);
            App.draw(Menu1);
            App.draw(Menu2);
            App.draw(Menu3);
            App.draw(Menu4);
        }
        App.display();
    }
}

#endif //DJJAM_MENUSCREEN_H
