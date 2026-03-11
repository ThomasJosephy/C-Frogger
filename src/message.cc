#include "message.hh"


Message::Message(std::string s, Point center, int fontSize, Fl_Color color)
    : s{s}, center{center}, fontSize{fontSize}, color{color} {}

void Message::draw() {
    fl_color(color);
    fl_font(FL_HELVETICA, fontSize);
    int width, height;
    fl_measure(s.c_str(), width, height, false);
    fl_draw(s.c_str(), center.x - width / 2,
            center.y - fl_descent() + height / 2);
}
