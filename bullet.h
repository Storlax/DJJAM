//
// Created by Michael DelSole on 4/18/18.
//

#ifndef DJJAM_BULLET_H
#define DJJAM_BULLET_H

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace sf;

class Bullet{
public:
    Texture t2,t3;
    Sprite bulletSprite;
    int bulletType;
    float distanceTraveled;
    void setSprite(int type);
};

void Bullet::setSprite(int newType) {
    if (newType == 2){
        t2.loadFromFile("../cmake_modules/Images/musicBullet.png");
        bulletSprite.setTexture(t2, true);
    }
    else if (newType == 3){
        t3.loadFromFile("../cmake_modules/Images/drumStick.png");
        bulletSprite.setTexture(t3, true);
    }
}




#endif //DJJAM_BULLET_H
