//
// Created by dick on 3/22/2018.
//

#ifndef DJJAM_GAME_H
#define DJJAM_GAME_H

//the meat of the project
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>

using namespace std;

//we need our coordinates
struct point
{ int x,y;};

//our constants that we will be needing for our game window
static const int windowHeight = 400;
static const int windowWidth = 533;
static const int maxFPS = 60;
static const string gameName = "DJJAM Muthaf*ckas";

//constants for other crap
static const int gravity = 9.8f;
//add more here as we go

class gameLoop {
public:
    void intializeGame();
    void pollEvents();
    void updateScreenState();
    void updateGameState();
};









#endif //DJJAM_GAME_H
