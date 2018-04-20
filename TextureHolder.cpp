//
// Created by Wadson on 4/16/2018.
//


#include "TextureHolder.h"
#include <cassert>

using namespace sf;
using namespace std;

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
    auto& m = m_Textures; //finds the m_Textures using the m_s_Instance pointer. auto is kinda the same a the map type


    auto keyValuePair = m.find(filename); //looks to see if file (key) is already in the map

    if (keyValuePair != m.end())
    {
        return keyValuePair->second; //if the the keys match the return the value (or the second part of the map which is the texture)
    }
    else
    {
        //if key not find the make a new one and add the texture as the key's value the return the value (the texture)
        auto& texture = m[filename];
        texture.loadFromFile(filename);
        return texture;
    }

}