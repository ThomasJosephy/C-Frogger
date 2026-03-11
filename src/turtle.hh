#pragma once
#include "mobile.hh"

class Turtle : public Mobile{
	private:
		int x;
	public:
		Turtle(int startposX, int y, int speed, int row) : Mobile(startposX, y, speed, row), x(startposX) {
			color = fl_rgb_color(115, 8, 0);
		}


		int getRight() const override { 
			if (row == 8) {
				return x + 3 * mobilesize + 6;
			} else if (row == 11) {
				return x + 2 * mobilesize + 3;
			}
			return 1;
		}

		int getLeft() const override {	return x; }

		int getSpeed() { return speed; }

		int getRow() const override { return row; }

		void draw() override {
			if (row==11){
				fl_draw_box(FL_FLAT_BOX, x, y, mobilesize, mobilesize, color);
				fl_draw_box(FL_FLAT_BOX, x + mobilesize + 3, y, mobilesize, mobilesize, color);

			} else if (row==8){
				fl_draw_box(FL_FLAT_BOX, x, y, mobilesize, mobilesize, color);
				fl_draw_box(FL_FLAT_BOX, x + mobilesize + 3, y, mobilesize, mobilesize, color);
				fl_draw_box(FL_FLAT_BOX, x + mobilesize + mobilesize + 6, y, mobilesize, mobilesize, color);			
			}
			if (x < ecartX - 3 * taille) {
				x = ecartX + 16 * taille;
			}			
			x += speed;
		}
};