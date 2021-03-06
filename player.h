//
// Created by Michael DelSole on 3/22/18.
//

#ifndef SFMLDEMO_PLAYER_H
#define SFMLDEMO_PLAYER_H

#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>

//this includes the standard functions in SFML's custom namespace which saves us an load of "sf::insertCrapHere"
using namespace sf;

class Player {
private:
    Texture playerLeft, playerRight;
    Texture background, platform;
public:
    //Player has different animations
    Player();
    Sprite setSpriteL();
    Sprite setSpriteR();
    Texture setPlatTexture();
    Texture setBGTexture();
    std::ifstream applyPlayerModel;

};

#endif //SFMLDEMO_PLAYER_H