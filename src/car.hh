#pragma once

#include "mobile.hh"

class Car : public Mobile{
	private:
		int x;
	public:
			Car(int startposX, int y, int speed, int row) : Mobile(startposX, y, speed, row), x(startposX) {
				color = fl_rgb_color(255, 0, 255);
			}

			void draw() override {
				if (row==6){
					fl_draw_box(FL_FLAT_BOX, x, y, 2*mobilesize, mobilesize, color);
				} else {
					fl_draw_box(FL_FLAT_BOX, x, y, mobilesize, mobilesize, color);			
				}
				if (speed > 0) {
					if (x > ecartX + 15 * taille) {
						x = ecartX - 2*taille;
					}
				} else {
					if (x < ecartX - 2*taille) {
						x = ecartX + 16 * taille;
					}
				}
				x += speed;				
			}

            int getLeft() const override { return x; }

            int getRight() const override {
                if (row == 6) {
                    return x + 2 * mobilesize;
                } else {
                    return x + mobilesize;
                }
            }

            int getRow() const override { return row; }

};