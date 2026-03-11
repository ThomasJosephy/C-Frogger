#include "cell.hh"

Cell::Cell(Point center, int w, int h, int row):
  r(center, w, h, row) {}		


void Cell::draw() {
  r.draw(); // Draw le décor
}

bool Cell::contains(Point p) {
    return p.x >= r.getCenter().x - size / 2 &&
           p.x < r.getCenter().x + size / 2 &&
           p.y >= r.getCenter().y - size / 2 &&
           p.y < r.getCenter().y + size / 2;
}