#pragma once
#include "decor.hh"

// Classe prise dans le TP n°2 afin de la réadapter comme suggéré.

class Cell {
  Decor r;
  bool on = true;
  int size;

 public:

  Cell(Point center, int w, int h, int row);

  void draw();

  bool contains(Point p);


};
