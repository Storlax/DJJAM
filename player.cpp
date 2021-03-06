//
// Created by Michael DelSole on 3/22/18.

#include "player.h"

Player::Player() {
    //Save player texture choices in text file
    applyPlayerModel.open("../cmake_modules/Local_Game_Data/PlayerModel.txt");
    std::string playerSelect;
    applyPlayerModel >> playerSelect;
    applyPlayerModel.close();

    //Change the texture for the player based on what is selected
    if (playerSelect == "PinkSmallMellow")
    {
        playerLeft.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowPinkL.png");
        playerRight.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowPinkR.png");
    }
    else if (playerSelect == "GreenSmallMellow")
    {
        playerLeft.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowGreenL.png");
        playerRight.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowGreenR.png");
    }
    else if (playerSelect == "YellowSmallMellow")
    {
        playerLeft.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowYellowL.png");
        playerRight.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowYellowR.png");
    }
    else
    {
        playerLeft.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowL.png");
        playerRight.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowR.png");
    }
}

//Set the sprite based on what the player is inputting while playing the game
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