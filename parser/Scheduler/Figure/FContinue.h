//
// Created by arthur on 27.11.2019.
//

#ifndef FCONTINUE_H
#define FCONTINUE_H

#include <utility>

#include "DoubleMeasureFigure.h"

class FContinue: public DoubleMeasureFigure
{
public:
    explicit FContinue(Rect rect, size_t page = 1);

    static void reset();
    void acceptJsonFormer(JsonFormer &jFormer) override;
    std::string figureType() const override;
    AFigure *tryToConvertToFBegEnd() override;

private:

    static char name[2];
    static size_t counter;

    friend class FEmborderScheduler_connectForkPartsLeftPageLess_Test;
    friend class FEmborderScheduler_connectForkPartsRightPageLess_Test;
};

#endif //FCONTINUE_H
