//
// Created by Wadson on 4/16/2018.
//
#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
using namespace sf;
using namespace std;

class TextureHolder
{
private:
    map<string, Texture> m_Textures; //find a way to make this static so that all objects can use one

public:
    // TextureHolder();

    Texture& GetTexture(string const& filename);

};

#endif
