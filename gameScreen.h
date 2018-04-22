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
#include "collision.h"
#include "Pickup.h"
#include "TextureHolder.h"
#include <random>

#include <SFML/Graphics.hpp>
#include <cmath>
//TODO: ADD FUNCTION FOR PLATFORM GENERATION (including initial platform) AND GAME SPEED BASED ON SCORE

struct point { int x, y; };

static int randNum(int min, int max){
    random_device rd;
    uniform_int_distribution<int> dist(1, max);
    return min+dist(rd)%max;
}

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
    float enemyX;
    int newType = randNum(1,4);
    float currentAngle = 0;
    float shootTimer = 0;
    int templocation;
    float max_FPS = 60;
    float rotation = 0;
    float spinCounter = 0;
    bool spinStart = false;

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

    App.setFramerateLimit(max_FPS);
    max_FPS = 60;

    setFont();
    setScore();

    //We need real randomness
    random_device rd;
    uniform_int_distribution<int> dist(1, 450);

    //loads textures from files, duhhh
    Texture t1, t2, t3, t4, t5;
    t1.loadFromFile("../cmake_modules/Images/backgroundColor.png");
    t2.loadFromFile("../cmake_modules/Images/platform.png");
    t3.loadFromFile("../cmake_modules/Images/platformblue.png");
    t4.loadFromFile("../cmake_modules/Images/platformred.png");
    t5.loadFromFile("../cmake_modules/Images/platformyellow.png");

    //Enemy stuff
    float enemyY = -80;
    enemyX = 100+(dist(rd)%(300-100+1));
    float enemyRelativeX = enemyX;
    bool enemyPresent = false;
    bool bulletPresent = false;
    float unitVector;
    float offsetX;
    float offsetY;
    enemy newEnemy;
    Bullet bull;
    Sprite enemy = newEnemy.setBehavior(newType);
    bull.setSprite(newType);

    //srand(time(reinterpret_cast<time_t *>(NULL)));


    //Platform stuff
    point plat[9];
    point platBlue[7];
    point platRed[4];
    point platYellow[3];

    plat[0].y = rand() % 8 + 525;
    for (int i = 0; i < 9; i++) {
        if (i != 0) {
            plat[i].x = 50 + rand() % 330;
            templocation = plat[i - 1].y - (rand() % 23 + 60);
            if (templocation < 0) {
                templocation = rand() % 533;
            }
            plat[i].y = templocation;

        }
        plat[i].x = 50 + rand() % 330;
        templocation = 0;
    }
    //Added random generation for all platforms.
    platBlue[0].y = rand() % 8 + 525;
    for (int i = 0; i < 7; i++) {
        if (i != 0) {
            templocation = platBlue[i - 1].y - (rand() % 23 + 60);
            if (templocation < 0) {
                templocation = rand() % 533;
            }
            platBlue[i].y = templocation;
        }
        platBlue[i].x = 50 + rand() % 330;
        templocation = 0;
    }


    platRed[0].y = rand() % 8 + 525;
    for (int i = 0; i < 4; i++) {
        if (i != 0) {
            templocation = platRed[i - 1].y - (rand() % 23 + 60);
            if (templocation < 0) {
                templocation = rand() % 533;
            }
            platRed[i].y = templocation;
        }
        platRed[i].x = 50 + rand() % 330;
        templocation = 0;

    }

    platYellow[0].y = rand() % 8 + 525;
    for (int i = 0; i < 3; i++) {
        if (i != 0) {
            templocation = platYellow[i - 1].y - (rand() % 23 + 60);
            if (templocation < 0) {
                templocation = rand() % 533;
            }
            platYellow[i].y = templocation;
        }
        platYellow[i].x = 50 + rand() % 330;
        templocation = 0;

    }

    //starting locations yay!
    int x = 100,y = 100,h = 200;
    //good ol' changes in positions
    float dx = 0,dy = 0;

    //Instantiate our player class
    Player player;

    //Initialize our sprites
    Sprite sBackground(t1), sPlat(t2), sPlatBlue(t3), sPlatRed(t4), sPlatYellow(t5);
    Sprite currentSprite = player.setSpriteL();

    //Pickups
    Clock spawnClock; //starts clock for pickups
    TextureHolder textureHolder; //Holds all the textures in this file

    //speed up game with collectibles
    int musicNum = 0;
    int tempNum = -1;

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
            // Make the bullet move with the platforms
            if (bulletPresent) {
                bull.bulletSprite.setPosition(bull.bulletSprite.getPosition().x,bull.bulletSprite.getPosition().y-dy);
            }
            for (int i = 0; i < 7; i++) {
                y = h;
                score += .01;
                if (!enemyPresent) {
                    timeSteps += .01;
                }
            }
            for (int i = 0; i < 9; i++) {
                y = h;
                score += .01;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y = 0;
                    plat[i].x = 50+ dist(rd) % 330;
                }
            }
            for (int i = 0; i < 7; i++) {
                y = h;
                score += .01;
                platBlue[i].y = platBlue[i].y - dy;
                if (platBlue[i].y > 533) {
                    platBlue[i].y = 0;
                    platBlue[i].x = 50 + dist(rd) % 330;
                }
            }
            for (int i = 0; i < 3; i++) {
                y = h;
                score += .01;
                platRed[i].y = platRed[i].y - dy;
                if (platRed[i].y > 533) {
                    platRed[i].y = 0;
                    platRed[i].x = 50 + dist(rd) % 330;
                }
            }
            for (int i = 0; i < 3; i++) {
                y = h;
                score += .01;
                platYellow[i].y = platYellow[i].y - dy;
                if (platYellow[i].y > 533) {
                    platYellow[i].y = 0;
                    platYellow[i].x = 50 + dist(rd) % 330;
                }
            }
        }

        if(enemyY > 540){
            //Reset everything for the next enemy
            enemyPresent = false;
            timeSteps = 0;
            enemyY = -40;
            //srand(static_cast<unsigned int>(time(nullptr)));
            enemyX = 50+(dist(rd)%(300-50+1));
            enemyRelativeX = enemyX;
            newType = randNum(1,4);
            cout<<newType;
            enemy = newEnemy.setBehavior(newType);
            enemy.setOrigin(0,0);
            bull.bulletSprite.setOrigin(0,0);
            shootTimer = 0;
            bull.distanceTraveled = 0;
            rotation = 0;
            spinCounter = 0;
            spinStart = false;
        }

        if (score <= 50) {
            for (int i = 0; i < 9; i++) {
                if ((x + 50 > plat[i].x) && (x + 10 < plat[i].x + 68)
                    && (y + 50 > plat[i].y) && (y + 50 < plat[i].y + 14) && (dy > 0))
                    dy = -11;
            }
        }
        if (score <= 210 && score > 50) {

            for (int i = 0; i < 7; i++) {
                if ((x + 50 > platBlue[i].x) && (x + 10 < platBlue[i].x + 68)
                    && (y + 50 > platBlue[i].y) && (y + 50 < platBlue[i].y + 14) && (dy > 0))
                    dy = -11;
            }
        }

        if (score > 210 && score <= 260) {
            for (int i = 0; i < 4; i++) {
                if ((x + 50 > platRed[i].x) && (x + 10 < platRed[i].x + 68)
                    && (y + 50 > platRed[i].y) && (y + 50 < platRed[i].y + 14) && (dy > 0))
                    dy = -11;
            }
        }
        if (score > 260) {

            for (int i = 0; i < 3; i++) {
                if ((x + 50 > platYellow[i].x) && (x + 10 < platYellow[i].x + 68)
                    && (y + 50 > platYellow[i].y) && (y + 50 < platYellow[i].y + 14) && (dy > 0))
                    dy = -11;
            }
        }

        currentSprite.setPosition(x,y);


        //Draw everything on screen
        App.draw(sBackground);

        App.draw(currentSprite);

        m_score.setString("score: " + std::to_string((int)score));
        App.draw(m_score);

        if (score <= 50) {
            for (int i = 0; i < 9; i++) {
                sPlat.setPosition(plat[i].x, plat[i].y);
                App.draw(sPlat);
            }
        }
        if (score > 50 && score <= 210) {
            for (int i = 0; i < 7; i++) {
                sPlatBlue.setPosition(platBlue[i].x, platBlue[i].y);
                App.draw(sPlatBlue);
            }
        }
        if (score > 210 && score <= 260) {
            for (int i = 0; i < 7; i++) {
                sPlatRed.setPosition(platRed[i].x, platRed[i].y);
                App.draw(sPlatRed);
            }
        }
        if (score > 260) {
            for (int i = 0; i < 7; i++) {
                sPlatRed.setPosition(platRed[i].x, platRed[i].y);
                App.draw(sPlatRed);
            }
        }

        //// Enemy Handling ////

        //int interval = 10+(rand()%(30-10+1));
        float interval = 11;

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
                    bull.setSprite(2);
                    bull.bulletSprite.setPosition(enemyX+40,enemyY+40);
                    unitVector = sqrt(pow(enemyX-x,2)+pow(enemyY-y,2));
                    offsetX = x- enemyX;
                    offsetY = y- enemyY;
                    bulletPresent = true;
                }
            } //Boomerang drumstick enemy
            else if(newType == 3){
                shootTimer += 1;
                if (shootTimer >= 90){
                    bull.setSprite(3);
                    bull.bulletSprite.setPosition(enemyX+40,enemyY+40);
                    unitVector = sqrt(pow(enemyX-x,2)+pow(enemyY-y,2));
                    offsetX = x- enemyX;
                    offsetY = y- enemyY;
                    bulletPresent = true;
                    shootTimer = 0;
                }
            } //GuitarEnemy, rotates to look
            else if(newType == 4) {
                enemy.setOrigin(42.5,13.5);
                offsetX = x- enemyX;
                offsetY = y- enemyY;
                if (spinStart){
                    spinCounter += 1;
                }
                float distance = sqrt(pow(enemyX-x,2)+pow(enemyY-y,2));
                if(distance >= 120 && spinStart == false) {
                    float ang = atan2(offsetY, offsetX) * (180 / 3.1415926);
                    if (x > enemyX) {
                        enemy.setTexture(textureHolder.GetTexture("../cmake_modules/Images/guitarGuy.png"));
                        enemy.setRotation(ang);
                    } else {
                        enemy.setTexture(textureHolder.GetTexture("../cmake_modules/Images/guitarGuyL.png"));
                        enemy.setRotation(ang);
                    }
                }
                else{
                    if (x > enemyX) {
                        enemy.setTexture(textureHolder.GetTexture("../cmake_modules/Images/guitarGuySmile.png"));
                    } else {
                        enemy.setTexture(textureHolder.GetTexture("../cmake_modules/Images/guitarGuySmileL.png"));
                    }
                    spinStart = true;
                    spinCounter += 1;
                    if (spinCounter >= 70) {
                        enemy.rotate(20);
                        spinCounter += 1;
                        if(spinCounter >= 300){
                            spinStart = false;
                            spinCounter = 0;
                        }
                    }
                }
            }
        }
        if (bulletPresent == true) {
            //Music Notes
            if (newType == 2) {
                bull.bulletSprite.move(4 * offsetX / unitVector, 4 * offsetY / unitVector);
                App.draw(bull.bulletSprite);
                if (bull.bulletSprite.getPosition().x >= 400 || bull.bulletSprite.getPosition().x <= -40
                    || bull.bulletSprite.getPosition().y >= 533 || bull.bulletSprite.getPosition().y <= -40) {
                    bulletPresent = false;
                }
                if (Collision::PixelPerfect(currentSprite, bull.bulletSprite)) {
                    score = 0.f;
                    return (2);
                }
            } //Boomerang Drumsticks
            else if(newType == 3) {
                bull.bulletSprite.setOrigin(5,37);
                bull.bulletSprite.setRotation(rotation);
                rotation += 10;
                if (rotation >= 359){
                    rotation = 0;
                }
                bull.distanceTraveled += 0.1;
                if (bull.distanceTraveled <= 5) {
                    bull.bulletSprite.move(3 * offsetX / unitVector, 3 * offsetY / unitVector);
                } else {
                    bull.bulletSprite.move(-3 * offsetX / unitVector, -3 * offsetY / unitVector);
                    if (Collision::PixelPerfect(bull.bulletSprite, enemy)) {
                        bull.distanceTraveled = 0;
                        bulletPresent = false;
                    }
                }
                App.draw(bull.bulletSprite);
                if (Collision::PixelPerfect(currentSprite, bull.bulletSprite)) {
                    score = 0.f;
                    return (2);
                }
            }
        }
        if (enemyPresent){
            App.draw(enemy);
            if (Collision::PixelPerfect(currentSprite,enemy)){
                score = 0.f;
                return(2);
            }
        }

        //Making the pickups
        //the texture is set here and then this sprite is passed by reference
        Sprite musicNote_Type_1 = Sprite(textureHolder.GetTexture("../cmake_modules/Images/headphones.png"));
        Pickup musicNotes(musicNote_Type_1);
        musicNotes.setArena(400, 400); //tells pick the space they can spawn in


        Time spawnTime = spawnClock.getElapsedTime();

        //spawn code to set the sprite's location
        if (!musicNotes.getSpawned()) {
            musicNotes.spawn(); //sets the note's random positions
        } else
        {
            musicNotes.setSpawned(0); //redundant bc spawned value is false
        }


        //Draws Note Type 1
        if (spawnTime.asSeconds() >= 5)// if sprite is not spawned and rand nums are right values
        {
            //at this point we know the clock is at least 5 secs
            //so the next few lines tell the c6lock to wait 5 more seconds before despawning
            if (spawnTime.asSeconds() <= 10)
            {
                App.draw(musicNotes.getSprite());

                //Collision detection with pick ups
                if (currentSprite.getGlobalBounds().intersects(musicNotes.getPosition())) {
                    /*
                     ****************Code FOR THE STAGE SPEED GOES HERE!!***************
                     */

                    spawnClock.restart(); //time resets when there is a collision
                }
            }
            else if (spawnTime.asSeconds() > 10)
            {
                spawnClock.restart(); //resets spawnClock so if statement can work again
            }
        }
        if (y > 613)
        {
            score = 0.f;
            return(2);
        }
        App.display();

        if(musicNum > tempNum && max_FPS < 120.0) {
            tempNum = musicNum;
            max_FPS += 5.0;
            App.setFramerateLimit(max_FPS);
        }
    }
}

#endif //DJJAM_GAMESCREEN_H