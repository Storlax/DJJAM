//
// Created by Michael DelSole on 4/19/18.
//

#ifndef DJJAM_COLLISION_H
#define DJJAM_COLLISION_H

#include <SFML/Graphics.hpp>
using namespace sf;
namespace Collision {
    // Test for collision between two thingys by comparing the alpha values of overlapping pixels
    bool PixelPerfect(const Sprite& Object1 ,const Sprite& Object2, Uint8 AlphaLimit = 0);
}

#endif //DJJAM_COLLISION_H
