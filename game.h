//
// Created by dick on 3/22/2018.
//

#ifndef DJJAM_GAME_H
#define DJJAM_GAME_H

//the meat of the project
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

//our coordinate system
struct point { int x, y; };

//our constants that we will be needing for our game window
static const unsigned windowHeight = 400;
static const unsigned windowWidth = 533;
static const unsigned maxFPS = 60;
static const unsigned antialiasingLevel = 8;
static const string gameName = "DJJAM - Starring Mykle";

//constants for other crap
static const int gravity = 9.8f;
//add more here as we go

class gameLoop {
public:
    void initialize();
    void update();
    void poll();
    void setScore();
    void setFont();
    const RenderWindow &getWindow() const;
private:
    sf::Clock clock;
    sf::RenderWindow window;

    sf::Font m_font;
    sf::Text m_score;
    sf::Text m_highScore;

    float score = 0.f;
    int highScore = 0;
    void createWindow();
};









#endif //DJJAM_GAME_H
