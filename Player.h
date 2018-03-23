//
// Created by Michael DelSole on 3/22/18.
//

#ifndef SFMLDEMO_PLAYER_H
#define SFMLDEMO_PLAYER_H

#include <SFML/Graphics.hpp>
#include<iostream>

//this includes the standard functions in SFML's custom namespace which saves us an assload of "sf::insertCrapHere"
using namespace sf;

class Player{
public:
    Texture t1, t2;
    Player();
};

#endif //SFMLDEMO_PLAYER_H