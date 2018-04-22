//
// Created by Wadson on 4/13/2018.
//

#include "Pickup.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Sprite Pickup::getSprite()
{
    //Set the sprite to be the headphones
    tp.loadFromFile("../cmake_modules/Images/headphones.png");
    Sprite enemy(tp);
    return enemy;
}
