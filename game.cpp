//
// Created by dick on 3/22/2018 <- Michael's Birthday.
//

#include "game.h"
#include "player.h"
#include "enemy.h"

void gameLoop::initialize() {
    if(!window.isOpen())
    {
        createWindow();
    }
}

void gameLoop::createWindow() {
    //for graphics improvement
    sf::ContextSettings settings;
    settings.antialiasingLevel = antialiasingLevel;
    window.create(sf::VideoMode(windowHeight, windowWidth), gameName, sf::Style::Close, settings);
    window.setFramerateLimit(maxFPS);
}

void gameLoop::setFont() {
    m_font.loadFromFile("../cmake_modules/Images/OpenSans-Regular.ttf");
}

void gameLoop::setScore() {
    m_score.setFont(m_font);
    m_score.setCharacterSize(35);
    m_score.setFillColor(sf::Color::Black);
    m_score.setPosition(10,0);
}

void gameLoop::update() {

    setFont();
    setScore();

    //loads textures from files, duhhh
    Texture t1,t2;
    t1.loadFromFile("../cmake_modules/Images/background.png");
    t2.loadFromFile("../cmake_modules/Images/platform.png");

    //Enemy stuff
    bool enemyPresent = false;
    enemy newEnemy;
    Sprite enemy = newEnemy.enemyRight;

    //Platform stuff
    point plat[20];
    for (int i = 0; i < 10;i++)
    {
        //seems to be setting the location of the platforms randomly
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

    while(window.isOpen()) {

        //declaring an event
        Event e;
        //research this
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }
        //nice built in functions to detect key movement; ya love to see it!
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            currentSprite = player.setSpriteR();
            if (x > 380) {
                x = -60;
            } else {
                x += 3.5;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            currentSprite = player.setSpriteL();
            if (x < -60) {
                x = 410;
            } else {
                x -= 3.5;
            }
        }

        //good ol' gravity
        //dy += 0.25;
        dy += 0.2;
        //changes the current position to account for movement
        y += dy;
        if (y > 500) dy = -10;
        if (y < h) {
            if (enemyPresent) {
                enemyY -= dy;
            }
            for (int i = 0; i < 10; i++) {
                y = h;
                score += .01;
                if (!enemyPresent){
                    timeSteps += .01;
                }
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y = 0;
                    plat[i].x = rand() % 400;
                }
            }
        }
        if(enemyY > 540){
            enemyPresent = false;
            timeSteps = 0;
            enemyY = -40;
            srand(static_cast<unsigned int>(time(nullptr)));
            enemyX = 50+(rand()%(300-50+1));
            enemyRelativeX = enemyX;
        }

        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
                dy = -11;

        currentSprite.setPosition(x, y);

        //Draw everything on screen
        window.draw(sBackground);
        window.draw(currentSprite);

        m_score.setString("score: " + std::to_string((int) score));
        window.draw(m_score);

        for (int i = 0; i < 10; i++) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            window.draw(sPlat);
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
            //Move Back and forth
            enemyX += 2*cos(currentAngle);
            if (enemyX > (enemyRelativeX)+15) {
                currentAngle = 180;
            }
            if (enemyX < (enemyRelativeX)-15) {
                currentAngle = 0;
            }
        }
        if (enemyPresent){
            window.draw(enemy);
        }

        window.display();
    }
}

const RenderWindow &gameLoop::getWindow() const {
    return window;
}

