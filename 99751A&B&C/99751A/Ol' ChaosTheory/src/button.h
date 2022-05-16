#include "auton.h"

class Button {
public:
  Button(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }

  Button(int x, int y, int width, int height, color colr) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->colr = colr;
  }

  void setText(string text) {
    this->text = text;
    cstr = new char[text.length() + 1];
    strcpy(cstr, text.c_str());
  }

  void draw() {
    int text;
    Brain.Screen.drawRectangle(x, y, width, height, colr);
  }

  bool pressing() {
    int xPos = Brain.Screen.xPosition(), yPos = Brain.Screen.yPosition();

    return (Brain.Screen.pressing() && (xPos >= x && xPos <= x + width) &&
            (yPos >= y && yPos <= y + height));
  }

private:
  int x, y, width, height;
  string text;
  color colr;
  char *cstr;
};
