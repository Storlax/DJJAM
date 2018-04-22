//
// Created by Winter on 4/20/2018.
//

#include "songs.h"


using namespace std;
using namespace sf;


int musicStuff::playMusic(int seconds, bool sameTime, int notes) {

    musicNotes = notes;
    timeSame = sameTime;
    sec = seconds;


    if(musicNotes == 3 && sec == 0){
        randomNum = 4 + rand() % 3;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();
        sec = 0;

    }
    else if(musicNotes == 6 && sec == 0){
        randomNum = 7 + rand() % 3;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();
        sec = 0;
    }
    else if(musicNotes == 9 && sec == 0){
        randomNum = 10;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();
        sec = 0;
    }
    else if (sec == 0 && timeSame == false) {
        randomNum = rand() % 4;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();
    }

    if (randomNum == 0 && timeSame == false && sec == 191) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 1 && timeSame == false && sec == 294) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 2 && timeSame == false && sec == 175) {


        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 3 && timeSame == false && sec == 277) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 4 && timeSame == false && sec == 174) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 5 && timeSame == false && sec == 308) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 6 && timeSame == false && sec == 239) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 7 && timeSame == false && sec == 237) {
        sec = 0;
        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 8 && timeSame == false && sec == 320) {
        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    else if (randomNum == 9 && timeSame == false && sec == 227) {

        sec = 0;

        randomNum = rand() % 11;
        backGroundGrug.openFromFile(allSongs[randomNum]);
        backGroundGrug.play();

    }
    return sec;
}
