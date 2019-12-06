#ifndef LINE_H
#define LINE_H

#include "Figure.h"
#include <string>

struct LineData : public FigureData {
    int beginX;
    int beginY;
    int endX;
    int endY;
    std::string text;

    LineData() : beginX(0), beginY(0), endX(0), endY(0),
        text() {}
};

class Line : public Figure {
public:
    explicit Line() : beginX(0), beginY(0), endX(0), endY(0),
        text() {}
    ~Line() override {}

    int getBeginX() const { return beginX; }
    int getBeginY() const { return beginY; }
    int getEndX() const { return endX; }
    int getEndY() const { return endY; }
    std::string getText() const { return text; }

    void setBeginX(const int &value) { beginX = value; }
    void setBeginY(const int &value) { beginY = value; }
    void setEndX(const int &value) { endX = value; }
    void setEndY(const int &value) { endY = value; }
    void setText(const std::string &value) { text = value; }

    void Draw() override {} ;
private:
    int beginX;
    int beginY;
    int endX;
    int endY;
    std::string text;
};

#endif // LINE_H
