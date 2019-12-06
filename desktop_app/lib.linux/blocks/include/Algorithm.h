#ifndef DESKTOP_APP_ALGORITHM_H
#define DESKTOP_APP_ALGORITHM_H

#include "Figure.h"
#include "vector"

class Algorithm : public Figure {
public:
    Algorithm() = default;
    ~Algorithm() override {
        for (auto figure : figures)
            delete(figure);
    }

    void Draw() override;
    void Add(Figure *figure);

private:
    std::vector<Figure *> figures;
};

#endif //DESKTOP_APP_ALGORITHM_H
