//
// Created by Winter on 4/20/2018.
//

#ifndef DJJAM_SONGS_H
#define DJJAM_SONGS_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "SFML/Audio.hpp"
#include <iostream>
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>

class musicStuff{
public:
    int playMusic(int,bool,int);

private:
    //For Sound
    int sec = 0;
    int musicNotes;
    bool timeSame = false;
    Music backGroundGrug;
    string allSongs[11] = {"../cmake_modules/Music/lilZan.ogg", "../cmake_modules/Music/jCole.ogg","../cmake_modules/Music/chillBill.ogg", "../cmake_modules/Music/plugWalk.ogg","../cmake_modules/Music/kendrickLamar.ogg", "../cmake_modules/Music/ricFlair.ogg",
                           "../cmake_modules/Music/fosterThePeople.ogg","../cmake_modules/Music/andersonPaak.ogg", "../cmake_modules/Music/dram.ogg","../cmake_modules/Music/starboy.ogg","../cmake_modules/Music/ss.ogg"};

    int randomNum;
//

};

#endif //DJJAM_SONGS_H