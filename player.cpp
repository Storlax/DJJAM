//
// Created by Michael DelSole on 3/22/18.

#include "player.h"

Player::Player(){
    playerLeft.loadFromFile("../cmake_modules/Images/smallMellowL.png");
    playerRight.loadFromFile("../cmake_modules/Images/smallMellowR.png");
}

Sprite Player::setSpriteL() {
    Sprite sPersL(playerLeft);
    return sPersL;
}

Sprite Player::setSpriteR() {
    Sprite sPersL(playerRight);
    return sPersL;
}

Texture Player::setPlatTexture() {
    platform.loadFromFile("../cmake_modules/Images/platform.png");
    return platform;
}

Texture Player::setBGTexture() {
    background.loadFromFile("../cmake_modules/Images/background.png");
    return background;
}