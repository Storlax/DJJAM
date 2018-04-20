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
    Texture te;
    Sprite bulletSprite;
    int bulletType;
    float distanceTraveled;
    Bullet();
    void setSprite(int type);
};

Bullet::Bullet(){
    te.loadFromFile("../cmake_modules/Images/musicBullet.png");
    bulletSprite.setTexture(te, true);
}

void Bullet::setSprite(int newType) {
    if (newType == 2){
        te.loadFromFile("../cmake_modules/Images/musicBullet.png");
        bulletSprite.setTexture(te, true);
    }
    else if (newType == 3){
        te.loadFromFile("../cmake_modules/Images/drumStick.png");
        bulletSprite.setTexture(te, true);
    }
}




#endif //DJJAM_BULLET_H
