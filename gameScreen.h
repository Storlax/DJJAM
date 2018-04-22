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
#include "songs.h"
#include <random>

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
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
    int platAngleRed[7];
    int platAngleYellow[5];
    float shootTimer = 0;
    int templocation;
    int highScore = 0;
    float max_FPS = 60;
    float rotation = 0;
    float spinCounter = 0;
    bool spinStart = false;
    float pickupCounter = 0;
    bool pickupPresent = false;
    Clock platRedClock;
    Clock platYellowClock;

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

    ifstream inputHighScore;
    inputHighScore.open("../cmake_modules/Local_Game_Data/HighScore.txt");
    inputHighScore >> highScore;
    inputHighScore.close();

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
    Pickup newPickup;
    Sprite pickup = newPickup.getSprite();
    float pickupY = -80;
    float pickupX = 100+(dist(rd)%(300-100+1));

    //srand(time(reinterpret_cast<time_t *>(NULL)));


    //Platform stuff
    point plat[9];
    point platBlue[7];
    point platRed[7];
    point platYellow[8];

    plat[0].y = dist(rd) % 8 + 525;
    for (int i = 0; i < 9; i++) {
        if (i != 0) {
            plat[i].x = 50 + dist(rd) % 330;
            templocation = plat[i - 1].y - (dist(rd) % 23 + 60);
            if (templocation < 0) {
                templocation = dist(rd) % 533;
            }
            plat[i].y = templocation;

        }
        plat[i].x = 50 + dist(rd) % 330;
        templocation = 0;
    }
    //Added random generation for all platforms.
    platBlue[0].y = dist(rd) % 8 + 525;
    for (int i = 0; i < 7; i++) {
        if (i != 0) {
            templocation = platBlue[i - 1].y - (dist(rd) % 23 + 60);
            if (templocation < 0) {
                templocation = dist(rd) % 533;
            }
            platBlue[i].y = templocation;
        }
        platBlue[i].x = 50 + dist(rd) % 330;
        templocation = 0;
    }


    platRed[0].y = dist(rd) % 8 + 525;
    for (int i = 0; i < 7; i++) {
        if (i != 0) {
            templocation = platRed[i - 1].y - (dist(rd) % 23 + 60);
            if (templocation < 0) {
                templocation = dist(rd) % 533;
            }
            platRed[i].y = templocation;
        }
        platRed[i].x = 50 + dist(rd) % 330;
        templocation = 0;

    }

    platYellow[0].y = dist(rd) % 8 + 525;
    for (int i = 0; i < 8; i++) {
        if (i != 0) {
            templocation = platYellow[i - 1].y - (dist(rd) % 23 + 60);
            if (templocation < 0) {
                templocation = dist(rd) % 533;
            }
            platYellow[i].y = templocation;
        }
        platYellow[i].x = 50 + dist(rd) % 330;
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


    //Winters Code
    //music note collection counter for game speed
    int musicNum = 0;
    int tempNum = -1;

    musicStuff playMeSomeTunes;
    Clock soundCheck;
    int tempSec = -1;
    int otherSec = -1;
    int sec = 0;
    bool timeSame = false;
    bool singleUse = true;
    bool singleUse1 = true;
    bool singleUse2 = true;

    //jump sound effects
    SoundBuffer buffer;
    buffer.loadFromFile("../cmake_modules/Music/jump.wav");
    Sound jumpSound;
    jumpSound.setBuffer(buffer);
    int jumpSec = 0;
    Clock jumpClock;

    //collection sound effect
    SoundBuffer buffer2;
    buffer2.loadFromFile("../cmake_modules/Music/harp.wav");
    Sound collectSound;
    collectSound.setBuffer(buffer2);
    int collectSec = 0;
    Clock collectClock;
    //

    //death sound effect
    SoundBuffer buffer3;
    buffer3.loadFromFile("../cmake_modules/Music/death.wav");
    Sound deathSound;
    deathSound.setBuffer(buffer3);
    int deathSec = 0;
    Clock deathClock;
    //

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
            if (pickupPresent) {
                pickupY -= dy;
            }
            // Make the bullet move with the platforms
            if (bulletPresent) {
                bull.bulletSprite.setPosition(bull.bulletSprite.getPosition().x,bull.bulletSprite.getPosition().y-dy);
            }
            for (int i = 0; i < 3; i++) {
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
            for (int i = 0; i < 7; i++) {
                y = h;
                score += .01;
                platRed[i].y = platRed[i].y - dy;
                if (platRed[i].y > 533) {
                    platRed[i].y = 0;
                    platRed[i].x = 50 + dist(rd) % 330;
                }
            }
            for (int i = 0; i < 8; i++) {
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
            enemyX = 50+(dist(rd)%(300-50+1));
            enemyRelativeX = enemyX;
            newType = randNum(1,4);
            enemy = newEnemy.setBehavior(newType);
            enemy.setOrigin(0,0);
            bull.bulletSprite.setOrigin(0,0);
            shootTimer = 0;
            bull.distanceTraveled = 0;
            spinCounter = 0;
            spinStart = false;
            bull.bulletSprite.setRotation(0);
            bull.bulletSprite.setOrigin(0,0);
        }
        if(pickupY > 540){
            pickupPresent = false;
            pickupY = -40;
            pickupX = 50+(dist(rd)%(300-50+1));
            pickupCounter = 0;
        }

        Time platTime = platRedClock.getElapsedTime();
        if (platTime.asSeconds() < 10) {
            for (int i = 0; i < 9; i++) {
                if ((x + 50 > plat[i].x) && (x + 10 < plat[i].x + 68)
                    && (y + 50 > plat[i].y) && (y + 50 < plat[i].y + 14) && (dy > 0)) {
                    dy = -11;
                    //Winters Code
                    Time jumpTime = jumpClock.getElapsedTime();
                    jumpSec = jumpTime.asMilliseconds();
                    if (jumpSec > 50){
                        jumpSound.play();
                        jumpClock.restart();
                    }
                }
            }
        }
        if (platTime.asSeconds() > 10 && platTime.asSeconds() < 20) {
            for (int i = 0; i < 7; i++) {
                if ((x + 50 > platBlue[i].x) && (x + 10 < platBlue[i].x + 68)
                    && (y + 50 > platBlue[i].y) && (y + 50 < platBlue[i].y + 14) && (dy > 0)) {
                    dy = -11;
                    //Winters Code
                    Time jumpTime = jumpClock.getElapsedTime();
                    jumpSec = jumpTime.asMilliseconds();
                    if (jumpSec > 50){
                        jumpSound.play();
                        jumpClock.restart();
                    }
                }
            }
        }

        if ((platTime.asSeconds() > 20 && platTime.asSeconds() < 30)|| (platTime.asSeconds() > 40 && platTime.asSeconds() < 50)) {
            for (int i = 0; i < 7; i++) {
                if ((x + 50 > platRed[i].x) && (x + 10 < platRed[i].x + 68)
                    && (y + 50 > platRed[i].y) && (y + 50 < platRed[i].y + 14) && (dy > 0)) {
                    dy = -11;
                    //Winters Code
                    Time jumpTime = jumpClock.getElapsedTime();
                    jumpSec = jumpTime.asMilliseconds();
                    if (jumpSec > 50){
                        jumpSound.play();
                        jumpClock.restart();
                    }
                }
            }
        }
        if ((platTime.asSeconds() > 30 && platTime.asSeconds() <= 40) || (platTime.asSeconds() > 40 && platTime.asSeconds() < 50)) {
            for (int i = 0; i < 8; i++) {
                if ((x + 50 > platYellow[i].x) && (x + 10 < platYellow[i].x + 68)
                    && (y + 50 > platYellow[i].y) && (y + 50 < platYellow[i].y + 14) && (dy > 0)) {
                    dy = -11;
                    //Winters Code
                    Time jumpTime = jumpClock.getElapsedTime();
                    jumpSec = jumpTime.asMilliseconds();
                    if (jumpSec > 50) {
                        jumpSound.play();
                        jumpClock.restart();
                    }
                }
            }
        }

        currentSprite.setPosition(x,y);


        //Draw everything on screen
        App.draw(sBackground);

        App.draw(currentSprite);

        m_score.setString("score: " + std::to_string((int)score));
        App.draw(m_score);

        if (platTime.asSeconds() < 10) {
            for (int i = 0; i < 9; i++) {
                sPlat.setPosition(plat[i].x, plat[i].y);
                App.draw(sPlat);
            }
        }
        if (platTime.asSeconds() >= 10 && platTime.asSeconds() <= 20) {
            for (int i = 0; i < 7; i++) {
                sPlatBlue.setPosition(platBlue[i].x, platBlue[i].y);
                App.draw(sPlatBlue);
            }
        }
        if (platTime.asSeconds() >= 20 && platTime.asSeconds() <= 30 || platTime.asSeconds() > 40 && platTime.asSeconds() <=50) {
            for (int j = 0; j < 7; j++) {
                    if (platRed[j].x + 40 >= 400) {
                        platAngleRed[j] = 180;
                        }
                    else if (platRed[j].x <= 0) {
                        platAngleRed[j] = 0;
                    }
                    platRed[j].x += 3 * cos(platAngleRed[j]);
                    sPlatRed.setPosition(platRed[j].x, platRed[j].y);
                App.draw(sPlatRed);
                }
        }
        //Not working so I changed it
        if (platTime.asSeconds() > 30 && platTime.asSeconds() < 40 || platTime.asSeconds() > 40 && platTime.asSeconds() < 50) {
            for (int j = 0; j < 8; j++) {
                if (platYellow[j].x + 40 >= 400) {
                    platAngleYellow[j] = 180;
                } else if (platYellow[j].x <= 0) {
                    platAngleYellow[j] = 0;
                }
                platYellow[j].x += 3 * sin(platAngleYellow[j]);
                sPlatYellow.setPosition(platYellow[j].x, platYellow[j].y);
                App.draw(sPlatYellow);
            }
        }
        if(platTime.asSeconds() > 50){
            platRedClock.restart();
        }

        //// Enemy Handling ////

        //int interval = 10+(dist(rd)%(30-10+1));
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
            } //GuitarEnemy, rotates to look at player
            else if(newType == 4) {
                enemy.setOrigin(42.5,13.5);
                offsetX = x- enemyX;
                offsetY = y- enemyY;
                if (spinStart){
                    spinCounter += 1;
                }
                float distance = sqrt(pow(enemyX-x,2)+pow(enemyY-y,2));
                if(distance >= 140 && spinStart == false) {
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
                    platRedClock.restart();
                    platYellowClock.restart();
                    ofstream outputHighScore;
                    outputHighScore.open("../cmake_modules/Local_Game_Data/HighScore.txt");
                    if (score > highScore) {
                        outputHighScore << (int) score;
                    } else {
                        outputHighScore << highScore;
                    }
                    outputHighScore.close();

                    ofstream outputScore;
                    outputScore.open("../cmake_modules/Local_Game_Data/Score.txt");
                    outputScore << (int) score;
                    outputScore.close();
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
                    platRedClock.restart();
                    platYellowClock.restart();
                    ofstream outputHighScore;
                    outputHighScore.open("../cmake_modules/Local_Game_Data/HighScore.txt");
                    if (score > highScore) {
                        outputHighScore << (int) score;
                    } else {
                        outputHighScore << highScore;
                    }
                    outputHighScore.close();

                    ofstream outputScore;
                    outputScore.open("../cmake_modules/Local_Game_Data/Score.txt");
                    outputScore << (int) score;
                    outputScore.close();
                    score = 0.f;
                    return (2);
                }
            }
        }
        if (enemyPresent){
            App.draw(enemy);
            if (Collision::PixelPerfect(currentSprite,enemy)){
                platRedClock.restart();
                platYellowClock.restart();
                ofstream outputHighScore;
                outputHighScore.open("../cmake_modules/Local_Game_Data/HighScore.txt");
                if (score > highScore) {
                    outputHighScore << (int) score;
                } else {
                    outputHighScore << highScore;
                }
                outputHighScore.close();

                ofstream outputScore;
                outputScore.open("../cmake_modules/Local_Game_Data/Score.txt");
                outputScore << (int) score;
                outputScore.close();
                score = 0.f;
                return(2);
            }
        }

        if (!pickupPresent){
            pickupCounter += 1;
        }
        if (pickupCounter == 250) {
            pickupPresent = true;
        }
        if(pickupPresent){
            pickup.setPosition(pickupX, pickupY);
            App.draw(pickup);
            if (Collision::PixelPerfect(pickup, currentSprite)) {
                musicNum += 1;
                Time collectTime = collectClock.getElapsedTime();
                collectSec = collectTime.asMilliseconds();
                if (collectSec > 50) {
                    collectSound.play();
                    collectClock.restart();
                }
                pickupPresent = 0;
                pickupCounter = 0;
                pickupY = -40;
                pickupX = 50+(dist(rd)%(300-50+1));
            }
        }

        if (y > 613)
        {
            platRedClock.restart();
            platYellowClock.restart();
            ofstream outputHighScore;
            outputHighScore.open("../cmake_modules/Local_Game_Data/HighScore.txt");
            if (score > highScore) {
                outputHighScore << (int) score;
            } else {
                outputHighScore << highScore;
            }
            outputHighScore.close();

            ofstream outputScore;
            outputScore.open("../cmake_modules/Local_Game_Data/Score.txt");
            outputScore << (int) score;
            outputScore.close();
            score = 0.f;
            return(2);
        }
        App.display();

        //Winters Code

        if(musicNum > tempNum && max_FPS < 120.0) {
            tempNum = musicNum;
            max_FPS += 5.0;
            App.setFramerateLimit(max_FPS);
        }

        Time soundTime = soundCheck.getElapsedTime();
        sec = soundTime.asSeconds();


        if(tempSec == sec){
            timeSame = true;
        }

        if(musicNum == 3 && singleUse == true){
            sec = 0;
            otherSec = 0;
            singleUse = false;
            tempSec = sec;
            otherSec = playMeSomeTunes.playMusic(sec,timeSame,musicNum);

        }
        if(musicNum == 6 && singleUse1 == true){
            sec = 0;
            otherSec = 0;
            singleUse1 = false;
            tempSec = sec;
            otherSec = playMeSomeTunes.playMusic(sec,timeSame,musicNum);

        }
        if(musicNum == 9 && singleUse2 == true){
            sec = 0;
            otherSec = 0;
            singleUse2 = false;
            tempSec = sec;
            otherSec = playMeSomeTunes.playMusic(sec,timeSame,musicNum);

        }
        if (timeSame == true && sec != tempSec) {

            tempSec = sec;
            otherSec = playMeSomeTunes.playMusic(sec,timeSame,musicNum);

            timeSame = false;
        }
        if(timeSame == false){
            tempSec = sec;
            otherSec = playMeSomeTunes.playMusic(sec,timeSame,musicNum);
        }
        if(otherSec == 0 && timeSame == false){
            soundCheck.restart();
        }
        otherSec = -1;
    }
}

#endif //DJJAM_GAMESCREEN_H