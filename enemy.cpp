////
// Created by Michael DelSole on 4/13/18.

#include "enemy.h"

enemy::enemy(){
    //Save the enemy preferences to a text file so the textures are the same when re-running the program
    std::ifstream applyEnemyModel;
    //Apply whatever model is saved in the text file (normal colors by default)
    applyEnemyModel.open("../cmake_modules/Local_Game_Data/FlamingSkullModel.txt");
    std::string flamingSkullSelect;
    applyEnemyModel >> flamingSkullSelect;
    applyEnemyModel.close();

    //Each enemy has 4 different colors, load a different sprite based on what has been selected
    if (flamingSkullSelect == "BlueFlamingSkull")
    {
        t1.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkullPur.png");
    }
    else if (flamingSkullSelect == "VenomFlamingSkull")
    {
        t1.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkullVen.png");
    }
    else if (flamingSkullSelect == "RedsilverFlamingSkull")
    {
        t1.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkullRS.png");
    }
    else
    {
        t1.loadFromFile("../cmake_modules/Images/FlamingSkull_themes/FlamingSkull.png");
    }


    applyEnemyModel.open("../cmake_modules/Local_Game_Data/PianoGuyModel.txt");
    std::string pianoGuySelect;
    applyEnemyModel >> pianoGuySelect;
    applyEnemyModel.close();

    if (pianoGuySelect == "PurplePianoGuy")
    {
        t2.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuyPurple.png");
    }
    else if (pianoGuySelect == "OldPianoGuy")
    {
        t2.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuyOld.png");
    }
    else if (pianoGuySelect == "RedPianoGuy")
    {
        t2.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuyRedsilver.png");
    }
    else
    {
        t2.loadFromFile("../cmake_modules/Images/pianoGuy_themes/pianoGuy.png");
    }


    applyEnemyModel.open("../cmake_modules/Local_Game_Data/DrumGuyModel.txt");
    std::string drumGuySelect;
    applyEnemyModel >> drumGuySelect;
    applyEnemyModel.close();

    if (drumGuySelect == "PurpleDrumGuy")
    {
        t3.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuyPur.png");
    }
    else if (drumGuySelect == "BlueDrumGuy")
    {
        t3.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuyBb.png");
    }
    else if (drumGuySelect == "BlackDrumGuy")
    {
        t3.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuyBl.png");
    }
    else
    {
        t3.loadFromFile("../cmake_modules/Images/drumGuy_themes/drumGuy.png");
    }

    t4.loadFromFile("../cmake_modules/Images/guitarGuy.png");

}

//Set the sprite which also sets the behavior of each specific enemy
Sprite enemy::setBehavior(int newType) {
    if (newType == 1)
    {
        Sprite enemyT(t1);
        return enemyT;
    }
    else if (newType == 2)
    {
        Sprite enemyT(t2);
        return enemyT;
    }
    else if (newType == 3){
        Sprite enemyT(t3);
        return enemyT;
    }
    else if (newType == 4){
        Sprite enemyT(t4);
        return enemyT;
    }
}