#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <vector>
#include <iostream>
#include <fstream>

#include <set>
#include "frog.hh"
#include "text.hh"
#include "cell.hh"
#include "car.hh"
#include "log.hh"
#include "turtle.hh"
#include "message.hh"
#include "lilypads.hh"
#include "score_manager.hh"

class Canvas
{
    Text text;                   // instance pour afficher du texte
    std::vector<Cell> cells;     // vecteur des cellules de la grille
    std::vector<Car> cars;       // vecteur des voitures
    std::vector<Log> logs;       // vecteur des troncs d'arbre
    std::vector<Turtle> turtles; // vecteur des tortues

    int x;          // ne modifie rien
    int y = ecartY; // modifie l'écart avec le titre de la page fltk

    int row = 1;       // rangée actuelle
    int ecartcar = 50; // écart entre les voitures
    int fspeed;        // vitesse des objets (non utilisé ici)

    bool frogHitCar = false;   // Variable pour suivre l'état de la collision
    bool frogHitRiver = false; // Variable pour suivre l'état de la collision avec la rivière
    bool frogHitGreen = false;

    std::set<int> visitedRows;

    int score = 0;  
    int bestScore = 0; 

    
    bool showRestartMessage = false;

    std::vector<Lilypads> lilypads = {
        Lilypads{68, 5},
        Lilypads{187, 5},
        Lilypads{306, 5},
        Lilypads{425, 5},
        Lilypads{544, 5}};



    
    void drawWall(int &x_left, int size_wall_part) {
        Fl_Color wall = fl_rgb_color(34, 139, 34);
        fl_draw_box(FL_FLAT_BOX, x_left, 0, size_wall_part, taille, wall);
        x_left += size_wall_part;
    }

    void drawRiver(int &x_left, int size_lilypad_part, Frog &frog, std::vector<Lilypads> &lilypads, bool &frogged_this_turn) {
        Fl_Color river = fl_rgb_color(0, 0, 255);
        fl_draw_box(FL_FLAT_BOX, x_left, 0, size_lilypad_part, taille, river);
                
        for (auto &lily : lilypads) {
            lily.draw();
        }
        
        x_left += size_lilypad_part;
    }


    void resetLilypads(Frog &frog, std::vector<Lilypads> &lilypads) {
        if (frog.getLives() == 0) {
            for (auto &lily : lilypads) {
                lily.gotFrogged = false;
            }
        }
    }

    bool lastRow(Frog &frog, std::vector<Lilypads> &lilypads) {
    int x_left = 0;
    int size_wall_part = 51;
    int size_lilypad_part = 68;
    bool frogged_this_turn = false;
    bool previous_is_wall = false;

    while (x_left < windowWidth) {
        if (!previous_is_wall) {
            drawWall(x_left, size_wall_part);
            previous_is_wall = true;
        } else {
            drawRiver(x_left, size_lilypad_part, frog, lilypads, frogged_this_turn);
            previous_is_wall = false;
        }
    }

    if (frogged_this_turn) {
        return true;
    }

    resetLilypads(frog, lilypads);
    return false;
}




    void drawCells();
    void drawCars();
    void drawLogs();
    void drawTurtles();
    void checkCollisions();
    void checkRiver();
    void checkLilypads();
    void handleGameOver();
    void drawText();
    
public:
    //FIX !!!! SHOUL BE PRIVATE
    Frog f;                      // instance de la grenouille
    bool gameOver = false;

    Canvas();

    /**
     * @brief vérifie la collision entre la grenouille et une voiture.
     * @return true si collision détectée, sinon false.
     */
    bool checkCollision(const Frog &frog, const Car &car);

    /**
     * @brief dessine tous les éléments du jeu à l'écran.
     */
    void draw();

    /**
     * @brief gère les mouvements de la grenouille en fonction des touches pressées.
     * @param key la touche pressée.
     */
    void keyPressed(int key);

    void isInRiver(bool &res, Frog &frog) const
    {

        std::set<int> riverRows = {8, 9, 10, 11, 12};

        if (riverRows.count(frog.getRow()) > 0)
        {

            bool onLog = false;
            bool onTurtle = false;

            for (const auto &l : logs)
            {

                if (frog.isInside(l.getLeft(), l.getRight(), l.getRow()))
                {
                    onLog = true;
                    break; // La grenouille est sur un log, pas besoin de vérifier plus loin
                }
            }

            for (const auto &t : turtles)
            {
                if (frog.isInside(t.getLeft(), t.getRight(), t.getRow()))
                {
                    onTurtle = true;
                    break; // La grenouille est sur une tortue, pas besoin de vérifier plus loin
                }
            }

            // Si la grenouille n'est pas sur un log ni une tortue, elle est dans la rivière
            if (!onLog && !onTurtle)
            {
                res = true;
                return;
            }
        }

        // La grenouille n'est pas dans la rivière ou est sur un log/tortue
        res = false;
        return;
    }


    void lose();

    void checkLogsAndTurtles();

    bool checkOutOfBounds(Frog &frog) {
    return frog.getX() < 0 || frog.getX() > windowWidth;
}

    bool allLilypadsOccupied();
    void handleVictory();

    bool isOnLastRow(Frog &f); 
    bool isLilyPadOccupied(Frog &f, std::vector<Lilypads> &lilypads, bool &onLilyPad);
    void handleLilyPadResult(bool lilyOccupied, bool onLilyPad, Frog &f);

    void resetGame(Frog &frog)
    {   
        loadBestScore();
        std::cout << "hi hi reset\n";
        f.spawn();
        f.setRow(1);
        frog.resetLives();

        // tout remettre à false
        frogHitCar = false;
        frogHitRiver = false;
        frogHitGreen = false;

        for (int i = 0; i < 5; i++)
        {
            lilypads[i].gotFrogged = false;
        }

        for (auto &c : cells)
        {
            c.draw();
        }

        score = 0;
        visitedRows.clear();
        
    }

        void drawScore();  // Affiche le score
        void scoreHandler();
        void drawBestScore();  // Affiche le meilleur score
        void updateBestScore();  //  Mets à jour le meilleur score
        void saveBestScore();    // Save le meilleur score dans un fichier
        void loadBestScore();    // Charge le meilleur score depuis un fichier


        bool isGameOver() const {
            return gameOver; 
        }
};
