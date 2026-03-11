#include "decor.hh"

Decor::Decor(Point center, int w, int h, int row)
{
    this->center = center;
    this->w = w;
    this->h = h;
    this->row = row;
}

void Decor::draw()
{
    switch (row)
    {
        // Sidewalk 7 et 13
    case 13:
    case 7:
        fl_draw_box(FL_FLAT_BOX, center.x - taille / 2, center.y - taille / 2, taille, taille, sidewalk);
        break;
    // River  1 - 6
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        fl_draw_box(FL_FLAT_BOX, center.x - taille / 2, center.y - taille / 2, taille, taille, river);
        break;
        // Road  8 - 12
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        fl_draw_box(FL_FLAT_BOX, center.x - taille / 2, center.y - taille / 2, taille, taille, road);
        break;
        // case 1:
        // fl_draw_box(FL_FLAT_BOX, center.x-taille/2, center.y-taille/2, taille, taille, river);
        // lastRow();
        // break;
    }
}

Point Decor::getCenter() const { return center; }

bool Decor::contains(Point p)
{
    return p.x >= center.x - w / 2 &&
           p.x < center.x + w / 2 &&
           p.y >= center.y - h / 2 &&
           p.y < center.y + h / 2;
}

