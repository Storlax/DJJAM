//
// Created by Michael DelSole on 3/22/18.

#include "player.h"

Player::Player(){
    playerLeft.loadFromFile("../cmake_modules/Images/lol.png");
    playerRight.loadFromFile("../cmake_modules/Images/lolFlipped.png");
    background.loadFromFile("../cmake_modules/Images/background.png");
    platform.loadFromFile("../cmake_modules/Images/platform.png");
}

Sprite Player::setSpriteL() {
    Sprite sPersL(playerLeft);
    return sPersL;
}

Sprite Player::setSpriteR() {
    Sprite sPersL(playerRight);
    return sPersL;
}

Sprite Player::setSpriteBackground() {
    Sprite sPlat(platform);
    return sPlat;
}

Sprite Player::setSpritePlatform() {
    Sprite sBackground(background);
    return sBackground;
}