#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>


class Frog {
private:
    Fl_Color frogcolor = fl_rgb_color(9, 106, 9);
    Point center;
    int frogsqr = 34;
    int width  = frogsqr;
    int height = frogsqr;
    int speed = 0;
    int row = 1;
    int lives = 3;

public:

    Frog(Point center, int width, int height, int speed);

    void loseLife() { lives-= 1; }

    int getLives() { return lives; }

    int getRow() { return row; }

    void setRow(int new_row) { row = new_row; }

    void spawn() { center.x = ecartX + 7*taille;
        center.y =  ecartY + 12*taille; }

    int getLeft() { return center.x - frogsqr/2; }

    int getRight() { return center.x + frogsqr/2; }

    int getX() const { return center.x; }

    int getY() const { return center.y; }

    Fl_Color getFrogColor() { return frogcolor; }

    void setSpeed(int newSpeed) { speed = newSpeed; }

    void move(int key);

    bool isInside(int left, int right, int row){
        return left <= center.x && right >= center.x && getRow() == row;
    }
    void draw();
};


Frog::Frog(Point center, int width, int height, int speed) {
    this->center = center;
    this->width = width;
    this->height = height;
    this->speed = speed;
}


void Frog::draw() {
    fl_draw_box(FL_FLAT_BOX, center.x - frogsqr/2, center.y - frogsqr/2, frogsqr, frogsqr, frogcolor);
    center.x += speed;
}


/*------------------------------------------------------------------------------------------------------------*/
/*Frog::move est une méthode de la classe Frog permettant le mouvement haut-bas-gauche-droite de la Grenouille*/
/*------------------------------------------------------------------------------------------------------------*/
void Frog::move(int key){
    if ((key == 'z' || key == 'Z' || key == 'W' || key == 'w') && (center.y >= (taille + ecartY))) {
        center.y -= taille;
        row += 1;
        if (speed != 0) {
            speed = 0;
        }
    } else if ((key == 'q' || key == 'Q' || key == 'A' || key == 'a') && (center.x >= (2*taille + ecartX)))  {
        center.x -= taille;
    } else if ((key == 'd' || key == 'D') && (center.x <= (13*taille + ecartX)))  {
        center.x += taille;
    } else if ((key == 's' || key == 'S') && (center.y <= (11*taille + ecartY)))  {
        center.y += taille;
        row -= 1;
        if (speed != 0) {
            speed = 0;
        }
    }  else if (key == FL_Tab) {
        exit(0);
    }
}
