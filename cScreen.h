//
// Created by miami on 4/13/2018.
//

#ifndef DJJAM_CSCREEN_H
#define DJJAM_CSCREEN_H
//screen interface
class cScreen
{
public :
    virtual int Run (sf::RenderWindow &App) = 0;
};

#endif //DJJAM_CSCREEN_H
