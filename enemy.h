//
// Created by Michael DelSole on 4/13/18.
//

#ifndef DJJAM_ENEMY_H
#define DJJAM_ENEMY_H

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;

class enemy{
public:
    Texture t3;
    Sprite enemyRight;
    int enemyType;
    enemy();
    void setBehavior(int newType);
};

#endif //DJJAM_ENEMY_H