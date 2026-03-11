#include "frog.hh"

Frog::Frog(Point center, int width, int height, int speed){
    this->center = center;
    this->width = width;
    this->height = height;
    this->speed = speed;
}


void Frog::move(int key){		
	if ((key == 'z' || key == 'Z' || key == 'W' || key == 'w') && (center.y >= (taille + ecartY))) {
		center.y -= taille;
		row += 1;
		direction = UP;

	} else if ((key == 'q' || key == 'Q' || key == 'A' || key == 'a') && (center.x >= (2*taille + ecartX)))  {
		center.x -= taille;
		direction = LEFT;
	} else if ((key == 'd' || key == 'D') && (center.x <= (13*taille + ecartX)))  {
		center.x += taille;
		direction = RIGHT;
	} else if ((key == 's' || key == 'S') && (center.y <= (11*taille + ecartY)))  {
		center.y += taille;
		row -= 1;
		direction = DOWN;

	}  else if (key == FL_Tab) {
		exit(0);
	}
	
	if (speed != 0) {
		speed = 0;
	}	
}

void Frog::loseLife() {
    lives-= 1;
    speed = 0;
}

bool Frog::isInside(int left, int right, int row){
	        return left <= center.x && right >= center.x && getRow() == row;
    	}

void Frog::draw() {
    fl_color(frogcolor);

    fl_begin_polygon();
    switch (direction) {
        case UP:
            fl_vertex(center.x, center.y - frogsqr / 2);
            fl_vertex(center.x - frogsqr / 2, center.y + frogsqr / 2);
            fl_vertex(center.x + frogsqr / 2, center.y + frogsqr / 2);
            break;
        case DOWN:
            fl_vertex(center.x, center.y + frogsqr / 2);
            fl_vertex(center.x - frogsqr / 2, center.y - frogsqr / 2);
            fl_vertex(center.x + frogsqr / 2, center.y - frogsqr / 2);
            break;
        case LEFT:
            fl_vertex(center.x - frogsqr / 2, center.y);
            fl_vertex(center.x + frogsqr / 2, center.y - frogsqr / 2);
            fl_vertex(center.x + frogsqr / 2, center.y + frogsqr / 2);
            break;
        case RIGHT:
            fl_vertex(center.x + frogsqr / 2, center.y);
            fl_vertex(center.x - frogsqr / 2, center.y - frogsqr / 2);
            fl_vertex(center.x - frogsqr / 2, center.y + frogsqr / 2);
            break;
    }
	center.x += speed;
    fl_end_polygon();
}

