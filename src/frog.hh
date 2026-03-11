#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include "point.hh"
#include "constants.hh"


enum Direction { UP, DOWN, LEFT, RIGHT };

class Frog
{
private:
	Fl_Color frogcolor = fl_rgb_color(9, 106, 9);
	Point center;
	int frogsqr = 34;
	int width = frogsqr;
	int height = frogsqr;
	int speed = 0;
	int row = 1;
	int lives = 3;
	Direction direction;
	
public:
	Frog(Point center, int width, int height, int speed);

	void move(int key);

	void loseLife();

	bool isInside(int left, int right, int row);

	void draw();

	void spawn()
	{
		center.x = ecartX + 7 * taille;
		center.y = ecartY + 12 * taille;
	}
	
	//Getters and setters

	int getLives() { return lives; }

	void resetLives() { lives = 3; }

	int getRow() const { return row; }

	void setRow(int new_row) { row = new_row; }

	int getLeft() const { return center.x - frogsqr / 2; }

	int getRight() const { return center.x + frogsqr / 2; }

	int getX() const { return center.x; }

	int getY() const { return center.y; }

	Fl_Color getFrogColor() { return frogcolor; }

	void setSpeed(int newSpeed) { speed = newSpeed; }
};