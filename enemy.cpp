////
// Created by Michael DelSole on 4/13/18.
//

#include "enemy.h"

enemy::enemy(){
    enemyType = 1+(rand()%(2));
    std::cout<<enemyType;
    if (enemyType == 1) {
        t3.loadFromFile("../cmake_modules/Images/FlamingSkull.png");
        enemyRight.setTexture(t3, true);
    }
    else if (enemyType == 2){
        t3.loadFromFile("../cmake_modules/Images/pianoGuy.png");
        enemyRight.setTexture(t3, true);
    }

}

void enemy::setBehavior(int newType) {
    if (newType == 1) {
        t3.loadFromFile("../cmake_modules/Images/FlamingSkull.png");
        enemyRight.setTexture(t3, true);
    }
    else if (newType == 2){
        t3.loadFromFile("../cmake_modules/Images/pianoGuy.png");
        enemyRight.setTexture(t3, true);
    }
}