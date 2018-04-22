#ifndef DJJAM_GAMEOVERSCREEN_H
#define DJJAM_GAMEOVERSCREEN_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class gameOverScreen : public cScreen
{
private:

public:
    virtual int Run(sf::RenderWindow &App);
};

int gameOverScreen::Run(sf::RenderWindow &App)
{
    SoundBuffer buffer3;
    buffer3.loadFromFile("../cmake_modules/Music/death.wav");
    Sound deathSound;
    deathSound.setBuffer(buffer3);
    int deathSec = 0;
    Clock deathClock;
    string scoreNum;
    deathSound.play();

    ifstream loadScore;
    loadScore.open("../cmake_modules/Local_Game_Data/Score.txt");
    loadScore >> scoreNum;
    loadScore.close();

    sf::Event Event;
    bool running = true;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;
    sf::Text GameOver;
    sf::Text scoreDisplay;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    sf::Text Menu4;
    int menu = 0;

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
    GameOver.setFont(Font);
    GameOver.setCharacterSize(35);
    GameOver.setString("Game Over");
    GameOver.setPosition({85, 50});
    GameOver.setFillColor(sf::Color::Black);

    scoreDisplay.setFont(Font);
    scoreDisplay.setCharacterSize(25);
    scoreDisplay.setString("Score: " + scoreNum);
    scoreDisplay.setPosition({130, 100});
    scoreDisplay.setFillColor(sf::Color::Black);

    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Play Again");
    Menu1.setPosition({125, 200});

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("High Score");
    Menu2.setPosition({125, 250});

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Main Menu");
    Menu3.setPosition({125, 300});

    Menu4.setFont(Font);
    Menu4.setCharacterSize(20);
    Menu4.setString("Exit Game");
    Menu4.setPosition({125, 350});

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
                    case sf::Keyboard::Up:
                        if (menu != 0)
                        {
                            menu = menu -1;
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
                            return (1);
                        }
                        else if (menu == 1)
                        {
                            return (3);
                        }
                        else if (menu == 2)
                        {
                            return (0);
                        }
                        else if (menu == 3)
                        {
                            return (-1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
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

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(GameOver);
        App.draw(scoreDisplay);
        App.draw(Menu1);
        App.draw(Menu2);
        App.draw(Menu3);
        App.draw(Menu4);

        App.display();
    }
}


#endif //DJJAM_GAMEOVERSCREEN_H