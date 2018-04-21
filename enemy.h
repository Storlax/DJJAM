//
// Created by Michael DelSole on 4/13/18.
//

#ifndef DJJAM_ENEMY_H
#define DJJAM_ENEMY_H

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;

class enemy{
private:
    Texture t1,t2,t3,t4;
public:
    Sprite enemyRight;
    int enemyType;
    enemy();
    Sprite setBehavior(int newType);
};

#endif //DJJAM_ENEMY_H