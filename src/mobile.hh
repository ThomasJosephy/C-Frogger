#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "constants.hh"

class Mobile {
protected:
    int mobilesize = 40;
    Fl_Color color;
    int speed;
    int startposX = ecartX - mobilesize;
    int row;
    int y;

public:
    Mobile(int startposX, int y, int speed, int row)
        : startposX(startposX), row(row), speed(speed), y((13 - row) * taille + ecartY - mobilesize / 2) {}

    virtual void draw() = 0; //Draw virtuel, pour s'en servir dans les classes en dessous
    virtual int getLeft() const = 0;
    virtual int getRight() const = 0;
    virtual int getRow() const = 0;
};