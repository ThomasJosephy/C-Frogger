#pragma once

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include "frog.hh"



struct Text {
    Fl_Color colortext = FL_WHITE;
    Text() {}

void drawLives(Frog f) {
    int lives = f.getLives();
    std::string frog_text = std::to_string(lives) + " vies";
    
    fl_font(FL_HELVETICA, 18);  // Assurez-vous que la police et la taille sont définies ici
    fl_color(FL_WHITE);         // Définir la couleur du texte
    fl_draw(frog_text.c_str(), 13 * taille - 20 , 6 * taille, windowWidth, windowHeight, FL_ALIGN_LEFT);
}


    // void textGameOver() {
    //     fl_font(FL_HELVETICA_BOLD, 28);
    //     fl_draw("Game Over :(", windowWidth/2, windowHeight/2, 0, 0, FL_ALIGN_CENTER, nullptr, colortext);
    // }

    // bool textRestart() {
    //     fl_font(FL_HELVETICA_BOLD, 28);
    //     fl_draw("Press enter to play a new game!", windowWidth/2, windowHeight/2 + 50, 0, 0, FL_ALIGN_CENTER, nullptr, FL_WHITE);
    //     return false;
    // }

    void drawCenteredText(const char* message, int fontSize, Fl_Color textColor, int yOffset = 0) {
    fl_font(FL_HELVETICA_BOLD, fontSize);
    int textWidth = fl_width(message);
    int textHeight = fl_height();

    fl_color(textColor);
    fl_draw(message, windowWidth / 2, windowHeight / 2 + yOffset, 0, 0, FL_ALIGN_CENTER);
    }

    void textGameOver() {
        drawCenteredText("Game Over :(", 36, fl_rgb_color(255, 120, 120));
    }

    bool textRestart() {
        drawCenteredText("Press enter to play a new game!", 28, FL_WHITE, 50);
        return false;
    }


    void textVictory() {
    // Dessiner un fond coloré pour la victoire
    fl_color(fl_rgb_color(50, 100, 50));  // Vert lime vif
    fl_rectf(0, 0, windowWidth, windowHeight);  // Remplit toute la fenêtre

    // Dessiner un texte de victoire humoristique
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 36);
    fl_draw("YAY!\n", windowWidth / 2, windowHeight / 2 - 20, 0, 0, FL_ALIGN_CENTER);

    fl_font(FL_HELVETICA, 24);
    fl_draw("You conquered every lilypad!", windowWidth / 2, windowHeight / 2 + 30, 0, 0, FL_ALIGN_CENTER);
    fl_draw("Press Enter to play again", windowWidth / 2, windowHeight / 2 + 70, 0, 0, FL_ALIGN_CENTER);

    }
};
/*

textYouWin("You Win!", {250, 250}, 80, FL_GREEN)
 */