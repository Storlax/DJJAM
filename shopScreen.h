//
// Created by stevenmedina-de on 4/19/2018.
//

//#ifndef DJJAM_SHOPSCREEN_H
//#define DJJAM_SHOPSCREEN_H

#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class shopScreen : public cScreen
{
private:
    bool running = true;

public:
    virtual int Run(sf::RenderWindow &App);

    int ShopPlayerSkins(sf::RenderWindow &App);

    int ShopEnemySkins(sf::RenderWindow &App);
    int ShopPianoGuy(sf::RenderWindow &App);
    int ShopFlameBoi(sf::RenderWindow &App);
    int ShopDrumGuy(sf::RenderWindow &App);

};

int shopScreen::Run(sf::RenderWindow &App)
{

    sf::Event Event;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;
    sf::Text Menu1;
    sf::Text Menu2;
    sf::Text Menu3;
    int menu = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/Shop Background.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    //Set menu font
    Menu1.setFont(Font);
    Menu1.setCharacterSize(20);
    Menu1.setString("Player Shaders");
    Menu1.setPosition({105, 310});

    Menu2.setFont(Font);
    Menu2.setCharacterSize(20);
    Menu2.setString("Enemy Shaders");
    Menu2.setPosition({105, 345});

    Menu3.setFont(Font);
    Menu3.setCharacterSize(20);
    Menu3.setString("Main Menu");
    Menu3.setPosition({130, 380});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    //Control the menu
                    case sf::Keyboard::Up:
                        if (menu != 0)
                        {
                            menu = menu - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (menu != 2)
                        {
                            menu = menu + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (menu == 0)
                        {
                            int returnType = ShopPlayerSkins(App);
                            if (returnType == -1)
                            {
                                return (-1);
                            }
                        }
                        else if (menu == 1)
                        {
                            int returnType = ShopEnemySkins(App);
                            if (returnType == -1)
                            {
                                return (-1);
                            }
                        }
                        else if (menu == 2)
                        {
                            return (0);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        //Highlight selected option
        if (menu == 0)
        {
            Menu1.setFillColor(sf::Color::White);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::Black);
        }
        else if (menu == 1)
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::White);
            Menu3.setFillColor(sf::Color::Black);
        }
        else if (menu == 2)
        {
            Menu1.setFillColor(sf::Color::Black);
            Menu2.setFillColor(sf::Color::Black);
            Menu3.setFillColor(sf::Color::White);
        }

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(Menu1);
        App.draw(Menu2);
        App.draw(Menu3);


        App.display();
    }
}

/*
 *  Each of these next shop screens are the same thing, just for different textures. We have a player skins and enemy skins.
 *  The basic menu functions are the same, and all of them just use our apply function in order to apply the skin.
 *  The selections are saved into text files in order for the preferences to be saved for when the user runs the program
 *  in the future
 */

int shopScreen::ShopPlayerSkins(sf::RenderWindow &App)
{
    sf::Event Event;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;

    sf::Sprite greenMellow;
    sf::Texture greenSM;
    sf::Sprite pinkMellow;
    sf::Texture pinkSM;
    sf::Sprite yellowMellow;
    sf::Texture yellowSM;
    sf::Sprite smallMellow;
    sf::Texture sM;

    sf::Text Item1;
    sf::Text Item2;
    sf::Text Item3;
    sf::Text Item4;
    sf::Text Return;
    int itemSelect = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump2.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    //Set the items available for selection. It's pretty repititive and self-explanatory
    Item1.setFont(Font);
    Item1.setCharacterSize(20);
    Item1.setString("Apply Skin");
    Item1.setPosition({200, 50});

    pinkSM.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowPinkR.png");
    pinkMellow.setTexture(pinkSM, true);
    pinkMellow.setPosition({75, 38});


    Item2.setFont(Font);
    Item2.setCharacterSize(20);
    Item2.setString("Apply Skin");
    Item2.setPosition({200, 135});

    greenSM.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowGreenR.png");
    greenMellow.setTexture(greenSM, true);
    greenMellow.setPosition({75, 123});


    Item3.setFont(Font);
    Item3.setCharacterSize(20);
    Item3.setString("Apply Skin");
    Item3.setPosition({200, 220});

    yellowSM.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowYellowR.png");
    yellowMellow.setTexture(yellowSM, true);
    yellowMellow.setPosition({75, 208});


    Item4.setFont(Font);
    Item4.setCharacterSize(20);
    Item4.setString("Apply Skin");
    Item4.setPosition({200, 305});

    sM.loadFromFile("../cmake_modules/Images/smallMellow_themes/smallMellowR.png");
    smallMellow.setTexture(sM, true);
    smallMellow.setPosition({75, 293});


    Return.setFont(Font);
    Return.setCharacterSize(20);
    Return.setString("Return");
    Return.setPosition({145, 390});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        if (itemSelect != 0)
                        {
                            itemSelect = itemSelect - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (itemSelect != 4)
                        {
                            itemSelect = itemSelect + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        //Apply the selected model and save it to the text file for the future
                        if (itemSelect == 0)
                        {
                            ofstream selectPlayerModel;
                            selectPlayerModel.open("../cmake_modules/Local_Game_Data/PlayerModel.txt");
                            selectPlayerModel << "PinkSmallMellow";
                            selectPlayerModel.close();
                            return (0);
                        }
                        else if (itemSelect == 1)
                        {
                            ofstream selectPlayerModel;
                            selectPlayerModel.open("../cmake_modules/Local_Game_Data/PlayerModel.txt");
                            selectPlayerModel << "GreenSmallMellow";
                            selectPlayerModel.close();
                            return (0);
                        }
                        else if (itemSelect == 2)
                        {
                            ofstream selectPlayerModel;
                            selectPlayerModel.open("../cmake_modules/Local_Game_Data/PlayerModel.txt");
                            selectPlayerModel << "YellowSmallMellow";
                            selectPlayerModel.close();
                            return (0);
                        }
                        else if (itemSelect == 3)
                        {
                            ofstream selectPlayerModel;
                            selectPlayerModel.open("../cmake_modules/Local_Game_Data/PlayerModel.txt");
                            selectPlayerModel << "SmallMellow";
                            selectPlayerModel.close();
                            return (0);
                        }
                        else if (itemSelect == 4)
                        {
                            return (1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (itemSelect == 0)
        {
            Item1.setFillColor(sf::Color::White);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 1)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::White);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 2)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::White);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 3)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::White);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 4)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::White);

        }

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(Item1);
        App.draw(pinkMellow);
        App.draw(Item2);
        App.draw(greenMellow);
        App.draw(Item3);
        App.draw(yellowMellow);
        App.draw(Item4);
        App.draw(smallMellow);
        App.draw(Return);

        App.display();
    }
}

//Same functionality for player skin shop, see comments there for code clarification
int shopScreen::ShopEnemySkins(sf::RenderWindow &App)
{
    sf::Event Event;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;
    sf::Text Item1;
    sf::Text Item2;
    sf::Text Item3;
    sf::Text Return;
    int itemSelect = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump2.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    //Option for each of our enemies
    Item1.setFont(Font);
    Item1.setCharacterSize(20);
    Item1.setString("Piano Guy Skins");
    Item1.setPosition({108, 225});

    Item2.setFont(Font);
    Item2.setCharacterSize(20);
    Item2.setString("Flaming Skull Skins");
    Item2.setPosition({85, 260});

    Item3.setFont(Font);
    Item3.setCharacterSize(20);
    Item3.setString("Drum Guy Skins");
    Item3.setPosition({110, 295});

    Return.setFont(Font);
    Return.setCharacterSize(20);
    Return.setString("Return");
    Return.setPosition({158, 330});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        if (itemSelect != 0)
                        {
                            itemSelect = itemSelect - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (itemSelect != 3)
                        {
                            itemSelect = itemSelect + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (itemSelect == 0)
                        {
                            int returnType = ShopPianoGuy(App);
                            if (returnType == -1)
                            {
                                return (-1);
                            }
                        }
                        else if (itemSelect == 1)
                        {
                            int returnType = ShopFlameBoi(App);
                            if (returnType == -1)
                            {
                                return (-1);
                            }
                        }
                        else if (itemSelect == 2)
                        {
                            int returnType = ShopDrumGuy(App);
                            if (returnType == -1)
                            {
                                return (-1);
                            }
                        }
                        else if (itemSelect == 3)
                        {
                            return (1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        //Highlight selected item
        if (itemSelect == 0)
        {
            Item1.setFillColor(sf::Color::White);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 1)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::White);
            Item3.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 2)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::White);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 3)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::White);
        }

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(Item1);
        App.draw(Item2);
        App.draw(Item3);
        App.draw(Return);

        App.display();
    }
}
//Same functionality, see above
int shopScreen::ShopPianoGuy(sf::RenderWindow &App)
{
    sf::Event Event;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;

    sf::Sprite frame1;
    sf::Sprite frame2;
    sf::Sprite frame3;
    sf::Sprite frame4;
    sf::Texture textureFrame;
    sf::Sprite purplePG;
    sf::Texture purPG;
    sf::Sprite oldPG;
    sf::Texture olPG;
    sf::Sprite pianoGuy;
    sf::Texture pG;
    sf::Sprite redsilverPG;
    sf::Texture rsPG;

    sf::Text Item1;
    sf::Text Item2;
    sf::Text Item3;
    sf::Text Item4;
    sf::Text Return;
    int itemSelect = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump2.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    Item1.setFont(Font);
    Item1.setCharacterSize(20);
    Item1.setString("Apply Skin");
    Item1.setPosition({200, 50});

    purPG.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuyPurple.png");
    purplePG.setTexture(purPG, true);
    purplePG.setPosition({75, 38});
    textureFrame.loadFromFile("../cmake_modules/Images/frame.png");
    frame1.setTexture(textureFrame, true);
    frame1.setColor(sf::Color(255, 255, 255));
    frame1.setPosition({75, 38});


    Item2.setFont(Font);
    Item2.setCharacterSize(20);
    Item2.setString("Apply Skin");
    Item2.setPosition({200, 135});

    olPG.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuyOld.png");
    oldPG.setTexture(olPG, true);
    oldPG.setPosition({75, 123});
    frame2.setTexture(textureFrame, true);
    frame2.setColor(sf::Color(255, 255, 255));
    frame2.setPosition({75, 123});


    Item3.setFont(Font);
    Item3.setCharacterSize(20);
    Item3.setString("Apply Skin");
    Item3.setPosition({200, 220});

    rsPG.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuyRedsilver.png");
    redsilverPG.setTexture(rsPG, true);
    redsilverPG.setPosition({75, 208});
    frame3.setTexture(textureFrame, true);
    frame3.setColor(sf::Color(255, 255, 255));
    frame3.setPosition({75, 208});


    Item4.setFont(Font);
    Item4.setCharacterSize(20);
    Item4.setString("Apply Skin");
    Item4.setPosition({200, 305});

    pG.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuy.png");
    pianoGuy.setTexture(pG, true);
    pianoGuy.setPosition({75, 293});
    textureFrame.loadFromFile("../cmake_modules/Images/frame.png");
    frame4.setTexture(textureFrame, true);
    frame4.setColor(sf::Color(255, 255, 255));
    frame4.setPosition({75, 293});


    Return.setFont(Font);
    Return.setCharacterSize(20);
    Return.setString("Return");
    Return.setPosition({145, 390});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        if (itemSelect != 0)
                        {
                            itemSelect = itemSelect - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (itemSelect != 4)
                        {
                            itemSelect = itemSelect + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (itemSelect == 0)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/PianoGuyModel.txt");
                            selectEnemyModel << "PurplePianoGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 1)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/PianoGuyModel.txt");
                            selectEnemyModel << "OldPianoGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 2)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/PianoGuyModel.txt");
                            selectEnemyModel << "RedPianoGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 3)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/PianoGuyModel.txt");
                            selectEnemyModel << "PianoGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 4)
                        {
                            return (1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (itemSelect == 0)
        {
            Item1.setFillColor(sf::Color::White);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 1)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::White);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 2)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::White);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 3)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::White);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 4)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::White);

        }

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(Item1);
        App.draw(frame1);
        App.draw(purplePG);
        App.draw(Item2);
        App.draw(frame2);
        App.draw(oldPG);
        App.draw(Item3);
        App.draw(frame3);
        App.draw(redsilverPG);
        App.draw(Item4);
        App.draw(frame4);
        App.draw(pianoGuy);
        App.draw(Return);

        App.display();
    }
}
//Repeats... yeah all of them do
int shopScreen::ShopFlameBoi(sf::RenderWindow &App)
{
    sf::Event Event;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;

    sf::Sprite frame1;
    sf::Sprite frame2;
    sf::Sprite frame3;
    sf::Sprite frame4;
    sf::Texture textureFrame;
    sf::Sprite redsilverFS;
    sf::Texture rsFS;
    sf::Sprite venomFS;
    sf::Texture venFS;
    sf::Sprite purpleFS;
    sf::Texture purFS;
    sf::Sprite flamingSkull;
    sf::Texture flameSkull;

    sf::Text Item1;
    sf::Text Item2;
    sf::Text Item3;
    sf::Text Item4;
    sf::Text Return;
    int itemSelect = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump2.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    Item1.setFont(Font);
    Item1.setCharacterSize(20);
    Item1.setString("Apply Skin");
    Item1.setPosition({200, 50});

    purFS.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkullPur.png");
    purpleFS.setTexture(purFS, true);
    purpleFS.setPosition({75, 38});
    textureFrame.loadFromFile("../cmake_modules/Images/frame.png");
    frame1.setTexture(textureFrame, true);
    frame1.setColor(sf::Color(255, 255, 255));
    frame1.setPosition({75, 38});


    Item2.setFont(Font);
    Item2.setCharacterSize(20);
    Item2.setString("Apply Skin");
    Item2.setPosition({200, 135});

    venFS.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkullVen.png");
    venomFS.setTexture(venFS, true);
    venomFS.setPosition({75, 123});
    frame2.setTexture(textureFrame, true);
    frame2.setColor(sf::Color(255, 255, 255));
    frame2.setPosition({75, 123});


    Item3.setFont(Font);
    Item3.setCharacterSize(20);
    Item3.setString("Apply Skin");
    Item3.setPosition({200, 220});

    rsFS.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkullRS.png");
    redsilverFS.setTexture(rsFS, true);
    redsilverFS.setPosition({75, 208});
    frame3.setTexture(textureFrame, true);
    frame3.setColor(sf::Color(255, 255, 255));
    frame3.setPosition({75, 208});


    Item4.setFont(Font);
    Item4.setCharacterSize(20);
    Item4.setString("Apply Skin");
    Item4.setPosition({200, 305});

    flameSkull.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkull.png");
    flamingSkull.setTexture(flameSkull, true);
    flamingSkull.setPosition({75, 293});
    textureFrame.loadFromFile("../cmake_modules/Images/frame.png");
    frame4.setTexture(textureFrame, true);
    frame4.setColor(sf::Color(255, 255, 255));
    frame4.setPosition({75, 293});


    Return.setFont(Font);
    Return.setCharacterSize(20);
    Return.setString("Return");
    Return.setPosition({145, 390});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        if (itemSelect != 0)
                        {
                            itemSelect = itemSelect - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (itemSelect != 4)
                        {
                            itemSelect = itemSelect + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (itemSelect == 0)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/FlamingSkullModel.txt");
                            selectEnemyModel << "BlueFlamingSkull";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 1)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/FlamingSkullModel.txt");
                            selectEnemyModel << "VenomFlamingSkull";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 2)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/FlamingSkullModel.txt");
                            selectEnemyModel << "RedsilverFlamingSkull";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 3)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/FlamingSkullModel.txt");
                            selectEnemyModel << "FlamingSkull";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 4)
                        {
                            return (1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (itemSelect == 0)
        {
            Item1.setFillColor(sf::Color::White);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 1)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::White);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 2)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::White);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 3)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::White);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 4)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::White);

        }

        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(Item1);
        App.draw(frame1);
        App.draw(purpleFS);
        App.draw(Item2);
        App.draw(frame2);
        App.draw(venomFS);
        App.draw(Item3);
        App.draw(frame3);
        App.draw(redsilverFS);
        App.draw(Item4);
        App.draw(frame4);
        App.draw(flamingSkull);
        App.draw(Return);

        App.display();
    }
}
//Final repitition, this time for the drum guy
int shopScreen::ShopDrumGuy(sf::RenderWindow &App)
{
    sf::Event Event;
    sf::Texture Texture;
    sf::Sprite Sprite;
    sf::Font Font;

    sf::Sprite frame1;
    sf::Sprite frame2;
    sf::Sprite frame3;
    sf::Sprite frame4;
    sf::Texture textureFrame;
    sf::Sprite blueDG;
    sf::Texture bDG;
    sf::Sprite blackDG;
    sf::Texture blDG;
    sf::Sprite purpleDG;
    sf::Texture purDG;
    sf::Sprite drumGuy;
    sf::Texture dG;

    sf::Text Item1;
    sf::Text Item2;
    sf::Text Item3;
    sf::Text Item4;
    sf::Text Return;
    int itemSelect = 0;

    if (!Texture.loadFromFile("../cmake_modules/Images/DJ Jump2.jpg"))
    {
        std::cerr << "Error loading presentation.gif" << std::endl;
        return (-1);
    }
    Sprite.setTexture(Texture);
    if (!Font.loadFromFile("../cmake_modules/Images/stocky.ttf"))
    {
        std::cerr << "Error loading stocky.ttf" << std::endl;
        return (-1);
    }
    Item1.setFont(Font);
    Item1.setCharacterSize(20);
    Item1.setString("Apply Skin");
    Item1.setPosition({200, 50});

    purDG.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuyPur.png");
    purpleDG.setTexture(purDG, true);
    purpleDG.setPosition({75, 38});
    textureFrame.loadFromFile("../cmake_modules/Images/frame.png");
    frame1.setTexture(textureFrame, true);
    frame1.setColor(sf::Color(255, 255, 255));
    frame1.setPosition({75, 38});


    Item2.setFont(Font);
    Item2.setCharacterSize(20);
    Item2.setString("Apply Skin");
    Item2.setPosition({200, 135});

    bDG.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuyBb.png");
    blueDG.setTexture(bDG, true);
    blueDG.setPosition({75, 123});
    frame2.setTexture(textureFrame, true);
    frame2.setColor(sf::Color(255, 255, 255));
    frame2.setPosition({75, 123});


    Item3.setFont(Font);
    Item3.setCharacterSize(20);
    Item3.setString("Apply Skin");
    Item3.setPosition({200, 220});

    blDG.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuyBl.png");
    blackDG.setTexture(blDG, true);
    blackDG.setPosition({75, 208});
    frame3.setTexture(textureFrame, true);
    frame3.setColor(sf::Color(255, 255, 255));
    frame3.setPosition({75, 208});


    Item4.setFont(Font);
    Item4.setCharacterSize(20);
    Item4.setString("Apply Skin");
    Item4.setPosition({200, 305});

    dG.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuy.png");
    drumGuy.setTexture(dG, true);
    drumGuy.setPosition({75, 293});
    textureFrame.loadFromFile("../cmake_modules/Images/frame.png");
    frame4.setTexture(textureFrame, true);
    frame4.setColor(sf::Color(255, 255, 255));
    frame4.setPosition({75, 293});


    Return.setFont(Font);
    Return.setCharacterSize(20);
    Return.setString("Return");
    Return.setPosition({145, 390});

    while (running)
    {
        // Verifying events
        while (App.pollEvent(Event))
        {
            // Window closed
            if (Event.type == sf::Event::Closed)
            {
                return (-1);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                switch (Event.key.code)
                {
                    case sf::Keyboard::Up:
                        if (itemSelect != 0)
                        {
                            itemSelect = itemSelect - 1;
                        }
                        break;
                    case sf::Keyboard::Down:
                        if (itemSelect != 4)
                        {
                            itemSelect = itemSelect + 1;
                        }
                        break;
                    case sf::Keyboard::Return:
                        if (itemSelect == 0)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/DrumGuyModel.txt");
                            selectEnemyModel << "PurpleDrumGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 1)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/DrumGuyModel.txt");
                            selectEnemyModel << "BlueDrumGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 2)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/DrumGuyModel.txt");
                            selectEnemyModel << "BlackDrumGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 3)
                        {
                            ofstream selectEnemyModel;
                            selectEnemyModel.open("../cmake_modules/Local_Game_Data/DrumGuyModel.txt");
                            selectEnemyModel << "DrumGuy";
                            selectEnemyModel.close();
                            return (0);
                        }
                        else if (itemSelect == 4)
                        {
                            return (1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        if (itemSelect == 0)
        {
            Item1.setFillColor(sf::Color::White);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 1)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::White);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 2)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::White);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 3)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::White);
            Return.setFillColor(sf::Color::Black);
        }
        else if (itemSelect == 4)
        {
            Item1.setFillColor(sf::Color::Black);
            Item2.setFillColor(sf::Color::Black);
            Item3.setFillColor(sf::Color::Black);
            Item4.setFillColor(sf::Color::Black);
            Return.setFillColor(sf::Color::White);

        }
        //Clearing the screen
        App.clear();
        //Drawing
        App.draw(Sprite);
        App.draw(Item1);
        App.draw(frame1);
        App.draw(purpleDG);
        App.draw(Item2);
        App.draw(frame2);
        App.draw(blueDG);
        App.draw(Item3);
        App.draw(frame3);
        App.draw(blackDG);
        App.draw(Item4);
        App.draw(frame4);
        App.draw(drumGuy);
        App.draw(Return);

        App.display();
    }
}
