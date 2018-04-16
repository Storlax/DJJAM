//
// Created by dick on 3/22/2018.
//

#include "game.h"
#include "player.h"
#include <fstream>

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
    m_font.loadFromFile("../cmake_modules/Images/stocky.ttf");
}

void gameLoop::setScore() {
    m_score.setFont(m_font);
    m_score.setCharacterSize(30);
    m_score.setFillColor(sf::Color::Black);
    m_score.setPosition(10,0);

    m_highScore.setFont(m_font);
    m_highScore.setCharacterSize(20);
    m_highScore.setFillColor(sf::Color::Black);
    m_highScore.setPosition(25, 0);
}

void gameLoop::update() {

    setFont();
    setScore();

    //loads textures from files, duhhh
    Texture t1,t2;
    t1.loadFromFile("../cmake_modules/Images/background.png");
    t2.loadFromFile("../cmake_modules/Images/platform.png");

    //not sure what this one does; research
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

    Player player;
    //declaring the different images for their respective parts in the game (the person, platform, and background)
    Sprite sBackground(t1), sPlat(t2);

    Sprite currentSprite = player.setSpriteL();

    ifstream loadHighScore;
    loadHighScore.open("../cmake_modules/Score.txt");
    loadHighScore >> highScore;
    cout << "highScore: " << highScore << endl;
    loadHighScore.close();

    while(window.isOpen())
    {

        //declaring an event
        Event e;
        //research this
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
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
        if (y>500)  dy=-10;
        if (y<h)
            for (int i=0;i<10;i++) {
                y=h;
                score += .01;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y>533) {plat[i].y=0; plat[i].x=rand()%400;}
            }

        for (int i=0;i<10;i++)
            if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
                && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))  dy=-11;

        currentSprite.setPosition(x,y);

        window.draw(sBackground);
        window.draw(currentSprite);

        m_score.setString("score: " + std::to_string((int)score));
        m_highScore.setString("high score: " + std::to_string((int) highScore));
        window.draw(m_score);
        window.draw(m_highScore);


        for (int i=0;i<10;i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            window.draw(sPlat);
        }

        window.display();
    }

    ofstream saveHighScore;
    saveHighScore.open("../cmake_modules/Score.txt");
    if ( score > highScore ) {
        saveHighScore << score;
    } else {
        saveHighScore << highScore;
    }
    saveHighScore.close();
}

const RenderWindow &gameLoop::getWindow() const {
    return window;
}

