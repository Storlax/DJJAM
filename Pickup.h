//
// Created by Wadson on 4/13/2018.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class Pickup {
public:
    //Get whatever sprite it is in case we add more collectibles
    Sprite getSprite();
    Texture tp;
};