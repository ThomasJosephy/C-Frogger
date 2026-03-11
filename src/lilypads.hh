#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>

struct Lilypads {
	bool gotFrogged = false;
	int x_lily;
	int y_lily;
	Fl_Color frog_on = fl_rgb_color(9, 106, 9);
	Fl_Color lilypad = fl_rgb_color(1, 215, 88);
	Fl_Color color = lilypad;  // current color

	Lilypads(int x_lily, int y_lily) : x_lily(x_lily), y_lily(y_lily) {}

	void frogOnLily() { gotFrogged = true; }

	int getLilyX() { return x_lily; }

	void setColor(Fl_Color newColor) { color = newColor; }

	void draw() {
		if (!gotFrogged) {
      		fl_draw_box(FL_FLAT_BOX, x_lily, y_lily, 34, 34, lilypad); 			
		} else if (gotFrogged) {
      		fl_draw_box(FL_FLAT_BOX, x_lily, y_lily, 34, 34, frog_on); 
		}
	}
};