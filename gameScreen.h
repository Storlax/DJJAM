//
// Created by miami on 4/13/2018.
//

#ifndef DJJAM_GAMESCREEN_H
#define DJJAM_GAMESCREEN_H


#include <iostream>
#include "cScreen.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#include <SFML/Graphics.hpp>
#include <cmath>
//TODO: ADD FUNCTION FOR PLATFORM GENERATION (including initial platform) AND GAME SPEED BASED ON SCORE

struct point { int x, y; };

using namespace std;
using namespace sf;
//our game screen
class gameScreen : public cScreen
{
private:
    sf::Font m_font;
    sf::Text m_score;
    float score = 0.f;
    float timeSteps = 0;
public:
    virtual int Run(sf::RenderWindow &App);
    void setScore();
    void setFont();

    float enemyX = 100+(rand()%(300-100+1));
    float enemyRelativeX = enemyX;
    float currentAngle = 0;
    float shootTimer = 0;

};

void gameScreen::setFont() {
    m_font.loadFromFile("../cmake_modules/Images/OpenSans-Regular.ttf");
}

void gameScreen::setScore() {
    m_score.setFont(m_font);
    m_score.setCharacterSize(35);
    m_score.setFillColor(sf::Color::Black);
    m_score.setPosition(10,0);
}

int gameScreen::Run(sf::RenderWindow &App)
{
    score = 0;

    App.setFramerateLimit(60);

    setFont();
    setScore();

    //loads textures from files, duhhh
    Texture t1,t2;
    t1.loadFromFile("../cmake_modules/Images/background.png");
    t2.loadFromFile("../cmake_modules/Images/platform.png");

    //Enemy stuff
    float enemyY = -80;
    bool enemyPresent = false;
    bool bulletPresent = false;
    float unitVector;
    float offsetX;
    float offsetY;
    enemy newEnemy;
    Bullet bull;
    int newType = newEnemy.enemyType;
    Sprite enemy = newEnemy.enemyRight;
    srand(time(reinterpret_cast<time_t *>(NULL)));

    //Platform stuff
    point plat[20];
    for (int i = 0; i < 10;i++)
    {
        //setting the location of the platforms randomly
        plat[i].x = rand()%400;
        plat[i].y = rand()%533;
    }

    //starting locations yay!
    int x = 100,y = 100,h = 200;
    //good ol' changes in positions
    float dx = 0,dy = 0;

    //Instantiate our player class
    Player player;

    //Initialize our sprites
    Sprite sBackground(t1), sPlat(t2);
    Sprite currentSprite = player.setSpriteL();

    while(App.isOpen())
    {

        //declaring an event
        Event e;
        //research this
        while (App.pollEvent(e))
        {
            if (e.type == Event::Closed)
                App.close();
        }
        //nice built in functions to detect key movement; ya love to see it!
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            currentSprite = player.setSpriteR();
            if (x>380) {
                x = -60;
            }else {
                x += 3.5;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            currentSprite = player.setSpriteL();
            if (x<-60) {
                x = 410;
            } else {
                x -= 3.5;
            }
        }

        //good ol' gravity
        dy+=0.25;
        //changes the current position to account for movement
        y+=dy;
        //if (y>500)  dy=-10;
        if (y<h) {
            if (enemyPresent) {
                enemyY -= dy;
            }
            for (int i = 0; i < 10; i++) {
                y = h;
                score += .01;
                if (!enemyPresent) {
                    timeSteps += .01;
                }
            }
            for (int i = 0; i < 10; i++) {
                y = h;
                score += .01;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y = 0;
                    plat[i].x = rand() % 400;
                }
            }

        }

        if(enemyY > 540){
            //Reset everything for the next enemy
            enemyPresent = false;
            timeSteps = 0;
            enemyY = -40;
            srand(static_cast<unsigned int>(time(nullptr)));
            enemyX = 50+(rand()%(300-50+1));
            enemyRelativeX = enemyX;
            newType = 1+(rand()%(2));
            newEnemy.setBehavior(newType);
            shootTimer = 0;
        }

        for (int i=0;i<10;i++)
            if ((x + 50 > plat[i].x) && (x+20<plat[i].x+68)
                && (y + 70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))  dy=-11;

        currentSprite.setPosition(x,y);


        //Draw everything on screen
        App.draw(sBackground);
        App.draw(currentSprite);

        m_score.setString("score: " + std::to_string((int)score));
        App.draw(m_score);

        for (int i=0;i<10;i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            App.draw(sPlat);
        }

        //// Enemy Handling ////

        /*
         * multiple enemies: one goes towards player, one shoots at player, one just stays still
         * at end of enemyPresent, set timeSteps back to 0
         */

        /*
         * Teleporter:
         *             enemy.setPosition(100+(rand()%(300-100+1)),enemyY);
         */


        //int interval = 10+(rand()%(30-10+1));
        int interval = 11;

        if (timeSteps <= interval+1 && timeSteps >= interval-1){
            enemy.setPosition(enemyX,enemyY);
            enemyPresent = true;
            //Move Back and forth enemy
            if(newType == 1) {
                enemyX += 2 * cos(currentAngle);
                if (enemyX > (enemyRelativeX) + 15) {
                    currentAngle = 180;
                }
                if (enemyX < (enemyRelativeX) - 15) {
                    currentAngle = 0;
                }
            }//Shoot music notes enemy
            else if(newType == 2){
                shootTimer += 1;
                if (shootTimer >= 90 && bulletPresent == false){
                    bull.bulletSprite.setPosition(enemyX+40,enemyY+40);
                    unitVector = sqrt(pow(enemyX-x,2)+pow(enemyY-y,2));
                    offsetX = x- enemyX;
                    offsetY = y- enemyY;
                    bulletPresent = true;
                }
            }
        }
        if (bulletPresent == true) {
            bull.bulletSprite.move(4*offsetX/unitVector,4*offsetY/unitVector);
            App.draw(bull.bulletSprite);
            if(bull.bulletSprite.getPosition().x >= 400 || bull.bulletSprite.getPosition().x <= -40
                || bull.bulletSprite.getPosition().y >= 533 || bull.bulletSprite.getPosition().y <= -40){
                bulletPresent = false;
            }
        }
        if (enemyPresent){
            App.draw(enemy);
        }

        if (y > 613)
        {
            score = 0.f;
            return(2);
        }
        App.display();
    }
}

#endif //DJJAM_GAMESCREEN_H