#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include "point.hh"

//Classe prise dans le TP n°3 afin de la réadapter comme suggéré.
class Message {
    std::string s;
    Point       center;
    int         fontSize;
    Fl_Color    color;

public:
    // Constructor
    Message(std::string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK);

    // Draw
    void draw();

    // Setters and getters
    std::string getString() { return s; }
    void setString(const std::string &newString) { s = newString; }
    int getFontSize() { return fontSize; }
    void setFontSize(int newFontSize) { fontSize = newFontSize; }
    Point getCenter() { return center; }
    void setCenter(Point newCenter) { center = newCenter; }
};
