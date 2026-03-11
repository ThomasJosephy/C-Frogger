#pragma once
#include "mobile.hh"

class Log : public Mobile{
	private:
		int x;
	public:
		Log(int startposX, int y, int speed, int row) : Mobile(startposX, y, speed, row), x(startposX) {
			color = fl_rgb_color(136, 66, 29);
		}


		int getRight() const override { 
			if (row == 9) {
				return x + 2 * mobilesize;
			} else if (row == 10) {
				return x + 4 * mobilesize;
			} else if (row == 12) {
				return x + 3 * mobilesize;
			}
			return 1;
		}

		int getLeft() const override {	return x; }

		int getRow() const override { return row; }

		int getSpeed() { return speed; }

		void draw() override {
			if (row==9){
				fl_draw_box(FL_FLAT_BOX, x, y, 2*mobilesize, mobilesize, color);				// faire les cas ou on va de droite à gauche, donc mettre -speed
			} else if (row==10){
				fl_draw_box(FL_FLAT_BOX, x, y, 4*mobilesize, mobilesize, color);			
			} else if (row==12){
				fl_draw_box(FL_FLAT_BOX, x, y, 3*mobilesize, mobilesize, color);			
			}
			if (x > ecartX + 17 * taille) {
				x = ecartX - 4*taille;
			}
			x += speed;
		}
};