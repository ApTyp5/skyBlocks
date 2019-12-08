//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_DOUBLEMEASUREFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_DOUBLEMEASUREFIGURE_H_

#include "AFigure.h"
#include "Primitives/Rect.h"

class DoubleMeasureFigure: public AFigure
{
public:
    DoubleMeasureFigure(Rect rect, std::string text, size_t page = 1)
        :
        AFigure(std::move(text), page), rect_(rect)
    {}

    Point getCenter() const
    { return rect_.center; }
    size_t getWidth() const
    { return rect_.size.w; }
    size_t getHeight() const
    { return rect_.size.h; }


private:
    Rect rect_;

    friend class FEmborderScheduler_connectForkPartsLeftPageLess_Test;
    friend class FEmborderScheduler_connectForkPartsRightPageLess_Test;
    friend class FEmborderScheduler_addFigureCommon_Test;
    friend class FEmborderScheduler_addFigureBadWidth_Test;
    friend class FEmborderScheduler_addFigureTooTight_Test;
    friend class FEmborderScheduler_addForkCommon_Test;
    friend class FEmborderScheduler_addForkBadWidth_Test;
    friend class FEmborderScheduler_addForkTooTight_Test;

};

#endif //PARSER_SCHEDULER_FIGURE_DOUBLEMEASUREFIGURE_H_
