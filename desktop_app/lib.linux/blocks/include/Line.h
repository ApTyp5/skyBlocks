#ifndef LINE_H
#define LINE_H

#include "Figure.h"
#include <string>

struct LineData : public FigureData {
    double beginX;
    double beginY;
    double endX;
    double endY;
    std::string text;

    LineData() : beginX(0), beginY(0), endX(0), endY(0),
        text() {}
};

class Line : public Figure {
public:
    explicit Line() : beginX(0), beginY(0), endX(0), endY(0),
        text() {}
    ~Line() override {}

    double getBeginX() const { return beginX; }
    double getBeginY() const { return beginY; }
    double getEndX() const { return endX; }
    double getEndY() const { return endY; }
    std::string getText() const { return text; }

    void setBeginX(const double &value) { beginX = value; }
    void setBeginY(const double &value) { beginY = value; }
    void setEndX(const double &value) { endX = value; }
    void setEndY(const double &value) { endY = value; }
    void setText(const std::string &value) { text = value; }

    DrawData *Draw() override;
private:
    double beginX;
    double beginY;
    double endX;
    double endY;
    std::string text;
};

#endif // LINE_H
