// home_screen.hh
#pragma once
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include <fstream>
#include "score_manager.hh"

class HomeScreen {
    bool gameStarted = false;
    bool resetClicked = false;
    int bestScore;
    // Canvas canvas,

public:
    HomeScreen() : bestScore(loadBestScore()) {}

void draw() {
    fl_font(FL_COURIER_BOLD, 60); 
    fl_color(fl_rgb_color(50, 205, 50)); 
    fl_draw("FROGGER", windowWidth / 2 - 150, 100);  

    fl_font(FL_HELVETICA_BOLD, 36);  
    fl_color(FL_WHITE);
    fl_draw("Start Game", windowWidth / 2 - 100, 200);
    fl_draw("Reset Best Score", windowWidth / 2 - 150, 300);

    fl_font(FL_HELVETICA, 24);
    fl_color(FL_YELLOW);
    fl_draw(("Best Score: " + std::to_string(bestScore)).c_str(), windowWidth / 2 - 100, 400);
}


 void mouseClick(Point mouseLoc) {
    // "Start Game"
    if (mouseLoc.x >= (windowWidth / 2 - 100) && mouseLoc.x <= (windowWidth / 2 + 100) &&
        mouseLoc.y >= 170 && mouseLoc.y <= 220) {
        gameStarted = true;
    } 
    // "Reset Best Score"
    else if (mouseLoc.x >= (windowWidth / 2 - 150) && mouseLoc.x <= (windowWidth / 2 + 150) &&
             mouseLoc.y >= 270 && mouseLoc.y <= 320) {
        resetClicked = true;
    }
}

    bool isGameStarted() const {
        return gameStarted;
    }

    bool isResetClicked() const {
        return resetClicked;
    }

    void resetBestScore() {
        // std::ofstream file("best_score.txt");
        // file << 0;
        // bestScore = 0;
        // resetClicked = false;
        ScoreManager::resetBestScore();
        bestScore = 0;
        resetClicked = false;
    }

private:
    int loadBestScore() {
        // std::ifstream file("best_score.txt");
        // int score = 0;
        // if (file) {
        //     file >> score;
        // }
        // return score;
        return ScoreManager::loadBestScore();
    }
};
