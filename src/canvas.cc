#include "canvas.hh"
#include <iostream>

/* Constructeur de la classe Canvas */

Canvas::Canvas()
    : f(Point{ecartX + 7*taille, ecartY + 12*taille}, taille*(3/4), taille*(3/4), 0)
{

    //Load best score

    loadBestScore();

    // Initialisation des cellules
    for (int i = 0; i < 13; i++) {
        x = ecartX;
        for (int j = 0; j < 14; j++) {
            x += taille;
            cells.push_back(Cell{Point{x, y}, taille, taille, row});
        }
        row += 1;
        y += taille;
    }

    // Initialisation des voitures
    for (int i = 0; i < 3; i++) {
        cars.push_back(Car(ecartX - taille - 6 * ecartcar * i, ecartY + 12 * taille, -2, 2));  // Car(X, Y, speed, row) //2
        cars.push_back(Car(ecartX + 14 * taille + 4 * ecartcar * i, ecartY + 11 * taille, -3, 3)); //-3
        cars.push_back(Car(ecartX - 3 * taille - 4 * ecartcar * i, ecartY + 10 * taille, 1, 4)); //1
        cars.push_back(Car(ecartX + 14 * taille + 5 * ecartcar * i, ecartY + 9 * taille, -2, 5)); //-2
    }

    // Initialisation des voitures supplémentaires
    for (int i = 0; i < 2; i++) {
        cars.push_back(Car(ecartX - 2 * taille - 6 * ecartcar * i, ecartY + 8 * taille, 2, 6));
    }

    // Initialisation des tortues et des troncs d'arbre
    for (int i = 0; i < 4; i++) {
        turtles.push_back(Turtle(ecartX + 14 * taille + 4 * ecartcar * i, ecartY + 6 * taille, -1, 8));
        turtles.push_back(Turtle(ecartX + 14 * taille + 7 * ecartcar * i, ecartY + 3 * taille, -1, 11));
        logs.push_back(Log(ecartX - taille - 4 * ecartcar * i, ecartY + 5 * taille, 1, 9));
    }

    for (int i = 0; i < 3; i++) {
        logs.push_back(Log(ecartX - taille - 5 * ecartcar * i, ecartY + 4 * taille, 3, 10));
        logs.push_back(Log(ecartX - taille - 4 * ecartcar * i, ecartY + 2 * taille, 2, 12));
    }
}

// Méthode pour vérifier la collision entre la grenouille et une voiture
bool Canvas::checkCollision(const Frog& frog, const Car& car) {
    int frogLeft = frog.getLeft();
    int frogRight = frog.getRight();
    int frogRow = frog.getRow();

    int carLeft = car.getLeft();
    int carRight = car.getRight();
    int carRow = car.getRow();

    // Vérifie si les coordonnées se chevauchent
    if (frogLeft < carRight && frogRight > carLeft && frogRow == carRow) {
        return true;  // Collision détectée
    }

    return false;  // Pas de collision
}


void Canvas::lose(){
        f.loseLife();
        f.spawn();
        f.setRow(1);
        visitedRows.clear();
}   
void Canvas::draw() {

    if (f.getLives() == 0) {
        gameOver = true;
        drawCells();
        text.textGameOver();  // Affiche le message Game Over
        text.textRestart();  // Affiche l'instruction de redémarrage
        updateBestScore();

        std::cout << " LOSTTT\n";
        return;
    }

    else if (allLilypadsOccupied()) {
        handleVictory();  
        return;
    }

    scoreHandler();
    drawCells();
    bool frog_arrived = lastRow(f, lilypads);  
    drawCars();
    drawLogs();
    drawTurtles();
    checkCollisions();
    checkRiver();
    checkLilypads();
    drawText();
    drawScore();
    loadBestScore();
    drawBestScore();

    if (frog_arrived) {
        f.spawn();
        f.setRow(1);
        visitedRows.clear();
    }

}

void Canvas::drawCells() {
    for (auto &c : cells) {
        c.draw();
    }
}

void Canvas::drawCars() {
    for (auto &c : cars) {
        c.draw();
        if (checkCollision(f, c)) {
            if (!frogHitCar) {
                lose();
                frogHitCar = true;

            }
            return;
        } else {
            frogHitCar = false;
        }
    }
}

void Canvas::drawLogs() {
    for (auto &l : logs) {
        Fl_Color a = fl_rgb_color(50, 50, 50);
        Fl_Color b = fl_rgb_color(150, 150, 150);
        Fl_Color c = fl_rgb_color(250, 250, 250);
        l.draw();
        if (f.isInside(l.getLeft(), l.getRight(), l.getRow()) && (l.getRow() == 9 || l.getRow() == 10 || l.getRow() == 12)) {
            f.setSpeed(l.getSpeed());
        }
        if (f.isInside(l.getLeft(), l.getRight(), l.getRow())) {
            frogHitRiver = false;
        }
        //si grenouille reste sur log et log sort de l'ecran
        if (checkOutOfBounds(f)) {
            lose();
            return;
        }
    }
}

void Canvas::drawTurtles() {
    for (auto &t : turtles) {
        t.draw();
        if (f.isInside(t.getLeft(), t.getRight(), t.getRow()) || f.isInside(t.getLeft(), t.getRight(), t.getRow()) && (t.getRow() == 8 || t.getRow() == 11)) {
            f.setSpeed(t.getSpeed());
        }
        if (f.isInside(t.getLeft(), t.getRight(), t.getRow())) {
            frogHitRiver = false;
        }
        //si grenouille reste sur log et log sort de l'ecran
        if (checkOutOfBounds(f)) {
            lose();
            return;
        }
    }
}

void Canvas::checkCollisions() {
    // Fonction pour vérifier les collisions
    if (frogHitRiver) {
        lose();
    }
}

void Canvas::checkRiver() {
    isInRiver(frogHitRiver, f);
    if (frogHitRiver) {
        lose();
    }
}


bool Canvas::isOnLastRow(Frog &f) {
    return f.getRow() == 13;
}

bool Canvas::isLilyPadOccupied(Frog &f, std::vector<Lilypads> &lilypads, bool &onLilyPad) {
    for (auto& lily : lilypads) {
        if (f.isInside(lily.x_lily, lily.x_lily + taille, 13)) {
            if (lily.gotFrogged) {
                return true;  // le nénuphar est occupé
            } else {
                lily.frogOnLily();  // marquer le nénuphar comme occupé
                onLilyPad = true;
                score += 90;
                return false;
            }
        }
    }
    // std::cout << "Grenouille n'est sur aucun nénuphar\n";
    // return false;  // pas de nénuphar sous la grenouille
}



void Canvas::handleLilyPadResult(bool lilyOccupied, bool onLilyPad, Frog &f) {
    if (lilyOccupied || !onLilyPad) {
        lose();
    } else {
        f.spawn();
        f.setRow(1);
        visitedRows.clear();

    }
}


void Canvas::checkLilypads() {
    if (isOnLastRow(f)) {
        bool onLilyPad = false;
        bool lilyOccupied = isLilyPadOccupied(f, lilypads, onLilyPad);
        
        handleLilyPadResult(lilyOccupied, onLilyPad, f);


    }
}

bool Canvas::allLilypadsOccupied() {
    for (const auto& lily : lilypads) {
        if (!lily.gotFrogged) {
            return false;  
        }
    }
    return true; 

}


void Canvas::scoreHandler() {
    int currentRow = f.getRow();
    // Ajouter des points seulement si la rangée n'a pas encore été visitée
    if (currentRow != 1 && visitedRows.find(currentRow) == visitedRows.end()) {
        std::cout << "handling score "<< currentRow << "\n";
        score += 10;
        visitedRows.insert(currentRow);  // Marquer la rangée comme visitée
    }
    currentRow = f.getRow();
}


void Canvas::drawText() {
    f.draw();
    text.drawLives(f);
}

void Canvas::drawScore() {
    std::string scoreText = "Score: " + std::to_string(score);
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 16);


    int x_position = 145;  
    int y_position = 575;  

    fl_draw(scoreText.c_str(), x_position, y_position);
}


void Canvas::updateBestScore() {
    if (score > bestScore) {
        bestScore = score;
        saveBestScore();  // Sauvegarde du meilleur score
    }
}

void Canvas::drawBestScore() {
    std::string bestScoreText = "Best Score: " + std::to_string(bestScore);
    fl_color(FL_YELLOW);
    fl_font(FL_HELVETICA_BOLD, 16);

    // Position du meilleur score en bas à droite
    int x_position = 10;  
    int y_position = windowHeight - 20; 
    fl_draw(bestScoreText.c_str(), x_position, y_position);
}

void Canvas::saveBestScore() {
    // std::ofstream outFile("best_score.txt");
    // if (outFile.is_open()) {
    //     outFile << bestScore;
    //     outFile.close();
    // }
    ScoreManager::saveBestScore(bestScore);
}

void Canvas::loadBestScore() {
    // std::ifstream inFile("best_score.txt");
    // if (inFile.is_open()) {
    //     inFile >> bestScore;
    //     inFile.close();
    // }
    bestScore = ScoreManager::loadBestScore();
}


// Méthode pour gérer les mouvements de la grenouille en fonction des touches pressées
void Canvas::keyPressed(int key)
{
    switch (key)
    {
    case FL_Up:
        f.move('w');
        break;
    case FL_Down:
        f.move('s');
        break;
    case FL_Left:
        f.move('a');
        break;
    case FL_Right:
        f.move('d');
        break;
    default:
        f.move(key);
        break;
    }
}



void Canvas::handleVictory() {
    text.textVictory();
    gameOver = true;
}