//
// Created by stevenmedina-de on 4/18/2018.
//

#ifndef DJJAM_SCORESCREEN_H
#define DJJAM_SCORESCREEN_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class scoreScreen : public cScreen
{
private:

public:
    virtual int Run(sf::RenderWindow &App);

};

int scoreScreen::Run(sf::RenderWindow &App)
{
    std::string highScoreNum;
    //Load high score
    std::ifstream loadHighScore;
    loadHighScore.open("../cmake_modules/Local_Game_Data/HighScore.txt");
    loadHighScore >> highScoreNum;
    loadHighScore.close();

    sf::Event Event;
    bool running = true;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;
    sf::Text highScoreDisplay;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;

    //Set the background and the font
    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump2.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }

    //Display the high score with our font
    highScoreDisplay.setFont(Font);
    highScoreDisplay.setCharacterSize(25);
    highScoreDisplay.setString("High Score: " + highScoreNum);
    highScoreDisplay.setPosition({73, 100});
    highScoreDisplay.setFillColor(sf::Color::Black);

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Main Menu");
    Menu2.setPosition({125, 235});

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Exit Game");
    Menu3.setPosition({125, 285});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    //Select the menu option
                    case sf::Keyboard::Up:
                        if (menu != 0)
                        {
                            menu = menu - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (menu != 1)
                        {
                            menu = menu + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0)
                        {
                            return (0);
                        }
                        else if (menu == 1)
                        {
                            return (-1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        //Highlight selected option
        if (menu == 0)
        {
            Menu2.setFillColor(sf::Color::White);
            Menu3.setFillColor(sf::Color::Black);
        }
        else if (menu == 1)
        {
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::White);
        }

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(highScoreDisplay);
        App.draw(Menu2);
        App.draw(Menu3);

        App.display();
    }
}

#endif //DJJAM_SCORESCREEN_H
