//
// Created by Wadson on 4/13/2018.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

class Pickup {
private:

    //sprites
    Sprite m_Sprite;
    int m_Value;

    //where the sprite is
    IntRect m_arena;



    //Spawning
    bool m_Spawned;

public:
    explicit Pickup(Sprite& sprite);

    void setArena(int width, int height);

    void spawn();

    FloatRect getPosition();

    Sprite getSprite();

    bool getSpawned();

    void setSpawned(int num);


};