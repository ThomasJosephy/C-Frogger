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
#include "frog.hh"
#include "lilypads.hh"
#include "car.hh"
#include "log.hh"
#include "turtle.hh"
#include "decor.hh"
#include "text.hh"
#include "cell.hh"
#include "message.hh"
#include "canvas.hh"
#include "home_screen.hh"

using namespace std;


class MainWindow : public Fl_Window {
    HomeScreen homeScreen;
    Canvas canvas;
    bool inGame = false;
    bool hasStarted = false;  // Nouvelle variable pour suivre l'état du début

public:
    MainWindow() : Fl_Window(0, 0, windowWidth, windowHeight, "Frogger") {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        color(FL_BLACK);
    }

    void draw() override {
        Fl_Window::draw();
        if (!hasStarted) {
            homeScreen.draw();
        } else {
            canvas.draw();
        }
    }

    int handle(int event) override {
        switch (event) {
        case FL_KEYDOWN:
            if (inGame) {
                int key = Fl::event_key();
                if (key == FL_Enter && canvas.isGameOver()) {
                    canvas.resetGame(canvas.f);
                    //inGame = false;
                    return 1;
                }
                canvas.keyPressed(key);
            }
            break;
        case FL_PUSH:
            if (!hasStarted) {
                Point mouseLoc{Fl::event_x(), Fl::event_y()};
                homeScreen.mouseClick(mouseLoc);
                if (homeScreen.isGameStarted()) {
                    inGame = true;
                    hasStarted = true;  // marquer que le jeu a commencé
                }
                if (homeScreen.isResetClicked()) {
                    homeScreen.resetBestScore();
                }
            }
            break;
        default:
            return Fl_Window::handle(event);
        }
        return 1;
    }

    static void Timer_CB(void* userdata) {
        MainWindow* o = static_cast<MainWindow*>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }

private:
    void resetGame() {
        canvas.resetGame(canvas.f);
        inGame = false;  
};
};

int main(int argc, char* argv[]) {
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
}

