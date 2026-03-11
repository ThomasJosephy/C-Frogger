#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include "point.hh"
#include "constants.hh"

class Decor
{
private:
	Fl_Color road = FL_BLACK;
	Fl_Color sidewalk = fl_rgb_color(157, 62, 12);
	Fl_Color river = fl_rgb_color(0, 17, 255);
	int w;
	int h;
	int row;
	Point center;

public:
	Decor(Point center, int w, int h, int row);

	void draw();

	Point getCenter() const;

	bool contains(Point p);

};