//
// Created by Michael DelSole on 4/19/18.
//

#include <SFML/Graphics.hpp>
#include "collision.h"
using namespace sf;
using namespace std;

namespace Collision
{
    class BitmaskManager {
    public:
        //Unit 8 is just a very small number. Pixel perfect collision takes a lot of memory, so it's best to use a small
        //number to work with in order to improve program speed
        ~BitmaskManager() {
            map<const Texture*, Uint8*>::const_iterator end = Bitmasks.end();
            for (map<const Texture*, Uint8*>::const_iterator iter = Bitmasks.begin(); iter!=end; iter++)
                delete [] iter->second;
        }

        //We're going to go pixel by pixel
        Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
            if (x>tex->getSize().x||y>tex->getSize().y)
                return 0;

            return mask[x+y*tex->getSize().x];
        }

        //Get the mask of the texture as a starting point for the collision
        Uint8* GetMask (const Texture* tex) {
            Uint8 *mask;
            auto pair = Bitmasks.find(tex);
            if (pair == Bitmasks.end()) {
                Image img = tex->copyToImage();
                mask = CreateMask(tex, img);
            } else {
            mask = pair->second;
            }
            return mask;
        }

        //Set the mask that we just got in the last block of code
        Uint8* CreateMask (const Texture* tex, const Image& img) {
            Uint8* mask = new Uint8[tex->getSize().y*tex->getSize().x];

            for (unsigned int y = 0; y<tex->getSize().y; y++) {
                for (unsigned int x = 0; x<tex->getSize().x; x++) {
                    mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
                }
            }

            Bitmasks.insert(pair<const sf::Texture*, Uint8*>(tex,mask));
            return mask;
        }
    private:
        map<const sf::Texture*, sf::Uint8*> Bitmasks;
    };

    BitmaskManager Bitmasks;
    bool PixelPerfect(const Sprite& Object1, const Sprite& Object2, Uint8 AlphaLimit) {
        FloatRect Intersection;
        //Use the basic sfml collision as a starting point
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            //Get the bounding boxes to work with them
            IntRect O1SubRect = Object1.getTextureRect();
            IntRect O2SubRect = Object2.getTextureRect();

            Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());

            // Loop through our pixels
            for (auto i = static_cast<int>(Intersection.left); i < Intersection.left + Intersection.width; i++) {
                for (auto j = static_cast<int>(Intersection.top); j < Intersection.top + Intersection.height; j++) {
                    Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);

                    // Make sure pixels fall within the sprite's rectangle
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 && o1v.x < O1SubRect.width && o1v.y < O1SubRect.height
                        && o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

                        //This is a mess of an if statement, but all it really does is define the new bounding box
                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), static_cast<unsigned int>((int)(o1v.x) + O1SubRect.left),
                                              static_cast<unsigned int>((int)(o1v.y) + O1SubRect.top)) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), static_cast<unsigned int>((int)(o2v.x) + O2SubRect.left),
                                              static_cast<unsigned int>((int)(o2v.y) + O2SubRect.top)) > AlphaLimit)
                            return true;
                    }
                }
            }
        }
        return false;
    }
};