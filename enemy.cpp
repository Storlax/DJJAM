//
// Created by Michael DelSole on 4/13/18.
//

#include "enemy.h"

enemy::enemy(){
    t3.loadFromFile("../cmake_modules/Images/FlamingSkull.png");
    enemyRight.setTexture(t3, true);
}