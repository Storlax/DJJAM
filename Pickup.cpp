//
// Created by Wadson on 4/13/2018.
//

#include "Pickup.h"
#include "TextureHolder.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Pickup::Pickup(Sprite& sprite)
{
    m_Spawned = false; //sprite is not spawned yet so this value is false


    m_Sprite = sprite;


    //m_Sprite.setOrigin(25,25); //I dont think I need to set this value bc its random
}

void Pickup:: setArena(int width, int height)
{
    // m_arena.left = left;
    m_arena.width = width - 50;
    // m_arena.top = top;
    m_arena.height = height- 50;

}

void Pickup::spawn()
{

    srand(time(0));
    int xPos =(rand() % m_arena.width);

    srand(time(0));
    int yPos = (rand() % m_arena.height) + 100;

    m_Sprite.setPosition(xPos, yPos);
    setSpawned(1); //if spawn is called then Spawn bool is now true
}

FloatRect Pickup::getPosition()
{
    return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
    return m_Sprite;
}

bool Pickup::getSpawned()
{
    return m_Spawned;
}
void Pickup::setSpawned(int num)
{
    if(num == 1)
    {
        m_Spawned = true;
    }
    else
    {
        m_Spawned = false;
    }
}