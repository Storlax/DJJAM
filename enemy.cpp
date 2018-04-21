////
// Created by Michael DelSole on 4/13/18.

#include "enemy.h"

enemy::enemy(){
    t1.loadFromFile("../cmake_modules/Images/FlamingSkull.png");
    t2.loadFromFile("../cmake_modules/Images/pianoGuy.png");
    t3.loadFromFile("../cmake_modules/Images/drumGuy.png");
}

Sprite enemy::setBehavior(int newType) {
    if (newType == 1) {
        Sprite enemyT(t1);
        return enemyT;
    }
    else if (newType == 2){
        Sprite enemyT(t2);
        return enemyT;
    }
    else if (newType == 3){
        Sprite enemyT(t3);
        return enemyT;
    }
}