//
// Created by arthur on 24.11.2019.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>
#include "../Scheduler/Figure/FContinue.h"
#include "../Fixtures/FEmborderScheduler.h"
#include "../Scheduler/Figure/FLine.h"

TEST_F(FEmborderScheduler, addForkTooTight)
{
    scheduler->curState.setW(98);
    scheduler->curState.setY(260);
    std::string text = "Some text of any size\n" // 21
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    scheduler->addFFork(text, 70, 140);
    EXPECT_EQ(8, scheduler->figures.size());

    for (int i = 0; i < 4; i++) {
        delete scheduler->figures.pop_back();
    }

    auto *fork = dynamic_cast<DoubleMeasureFigure *>(scheduler->figures.back());
    EXPECT_DOUBLE_EQ(2 * 7 * meta.lh() + 2 * meta.yp(), fork->rect_.size.h);
    EXPECT_DOUBLE_EQ(2 * 14 * meta.sw() + 2 * meta.xp(), fork->rect_.size.w);
    EXPECT_DOUBLE_EQ(meta.ym() + fork->rect_.size.h / 2 + meta.bs() + scheduler->continueBlockSize().h,
                     fork->rect_.center.y);
    EXPECT_DOUBLE_EQ(scheduler->curState.x(), fork->rect_.center.x);
}
TEST_F(FEmborderScheduler, addForkCommon)
{
    std::string text = "Some text of any size\n" // 21
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    scheduler->addFFork(text, 70, 140);
    EXPECT_EQ(5, scheduler->figures.size());

    delete scheduler->figures.pop_back();
    delete scheduler->figures.pop_back();
    delete scheduler->figures.pop_back();
    delete scheduler->figures.pop_back();

    auto *follow = dynamic_cast<DoubleMeasureFigure *>(scheduler->figures.back());
    EXPECT_DOUBLE_EQ(2 * 4 * meta.lh() + 2 * meta.yp(), follow->rect_.size.h);
    EXPECT_DOUBLE_EQ(2 * 22 * meta.sw() + 2 * meta.xp(), follow->rect_.size.w);
    EXPECT_DOUBLE_EQ(meta.ym() + follow->rect_.size.h / 2, follow->rect_.center.y);
    EXPECT_DOUBLE_EQ(scheduler->curState.x(), follow->rect_.center.x);
}
TEST_F(FEmborderScheduler, addFigureTooTight)
{
    scheduler->curState.setW(98);
    scheduler->curState.setY(270);
    std::string text = "Some text of any size\n" // 21
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    scheduler->addFigure(FigureType::Follow, text);
    EXPECT_EQ(5, scheduler->figures.size());

    delete scheduler->figures.pop_back();
    auto *follow = dynamic_cast<DoubleMeasureFigure *>(scheduler->figures.back());
    EXPECT_DOUBLE_EQ(7 * meta.lh() + 2 * meta.yp(), follow->rect_.size.h);
    EXPECT_DOUBLE_EQ(14 * meta.sw() + 2 * meta.xp(), follow->rect_.size.w);
    EXPECT_DOUBLE_EQ(meta.ym() + follow->rect_.size.h / 2 + scheduler->continueBlockSize().h + meta.bs(),
                     follow->rect_.center.y);
    EXPECT_DOUBLE_EQ(scheduler->curState.x(), follow->rect_.center.x);
    EXPECT_DOUBLE_EQ(2, scheduler->curState.page());
}
/*TEST_F(FEmborderScheduler, addFigureBadWidth)
{
    scheduler->curState.setW(5);
    std::string text = "Some text of any size\n" // 21
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    scheduler->addFigure(FigureType::Follow, text);
    EXPECT_EQ(2, scheduler->figures.size());

    delete scheduler->figures.pop_back();
    auto *follow = dynamic_cast<DoubleMeasureFigure *>(scheduler->figures.back());
    EXPECT_DOUBLE_EQ(14 * meta.lh() + 2 * meta.yp(), follow->rect_.size.h);
    EXPECT_DOUBLE_EQ(5 * meta.sw() + 2 * meta.xp(), follow->rect_.size.w);
    EXPECT_DOUBLE_EQ(meta.ym() + follow->rect_.size.h / 2, follow->rect_.center.y);
    EXPECT_DOUBLE_EQ(scheduler->curState.x(), follow->rect_.center.x);
}*/
TEST_F(FEmborderScheduler, addFigureCommon)
{
    std::string text = "Some text of any size\n" // 21
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    scheduler->addFigure(FigureType::Follow, text);
    EXPECT_EQ(2, scheduler->figures.size());

    delete scheduler->figures.pop_back();
    auto *follow = dynamic_cast<DoubleMeasureFigure *>(scheduler->figures.back());
    EXPECT_DOUBLE_EQ(4 * meta.lh() + 2 * meta.yp(), follow->rect_.size.h);
    EXPECT_DOUBLE_EQ(22 * meta.sw() + 2 * meta.xp(), follow->rect_.size.w);
    EXPECT_DOUBLE_EQ(meta.ym() + follow->rect_.size.h / 2, follow->rect_.center.y);
    EXPECT_DOUBLE_EQ(scheduler->curState.x(), follow->rect_.center.x);
}
TEST_F(FEmborderScheduler, connectForkPartsRightPageLess)
{
    FContinue::reset();
    EmborderScheduler::State left(70, 70, 20, 5);
    EmborderScheduler::State right(30, 50, 20, 2);


    scheduler->connectForkParts(left, right);

    EXPECT_EQ(scheduler->figures.size(), 5);
    EXPECT_EQ(2, scheduler->figures[0]->getPage());

    auto contin1 = dynamic_cast<FContinue *>(scheduler->figures[0]);
    EXPECT_EQ(right.x(), contin1->rect_.center.x);
    EXPECT_STREQ("A", contin1->getText().data());
    EXPECT_EQ(2, contin1->getPage());

    auto contin2 = dynamic_cast<FContinue *>(scheduler->figures[1]);
    EXPECT_EQ(right.x(), contin2->rect_.center.x);
    EXPECT_DOUBLE_EQ(meta.ym() + scheduler->continueBlockSize().h / 2, contin2->rect_.center.y);
    EXPECT_STREQ("A", contin2->getText().data());
    EXPECT_EQ(5, contin2->getPage());

    auto vertLine = dynamic_cast<FLine *>(scheduler->figures[3]);
    EXPECT_EQ(5, vertLine->getPage());
    EXPECT_EQ(right.x(), vertLine->begin.x);
    EXPECT_EQ(meta.ym() + scheduler->continueBlockSize().h + meta.bs(), vertLine->begin.y);
    EXPECT_EQ(right.x(), vertLine->end.x);
    EXPECT_EQ(left.y(), vertLine->end.y);

    auto horizLine = dynamic_cast<FLine *>(scheduler->figures[4]);
    EXPECT_EQ(5, vertLine->getPage());
    EXPECT_EQ(left.x(), horizLine->begin.x);
    EXPECT_EQ(left.y(), horizLine->begin.y);
    EXPECT_EQ(right.x(), horizLine->end.x);
    EXPECT_EQ(left.y(), horizLine->end.y);
}
TEST_F(FEmborderScheduler, connectForkPartsLeftPageLess)
{
    FContinue::reset();
    EmborderScheduler::State left(30, 50, 20, 2);
    EmborderScheduler::State right(70, 70, 20, 5);

    scheduler->connectForkParts(left, right);

    EXPECT_EQ(scheduler->figures.size(), 5);
    EXPECT_EQ(2, scheduler->figures[0]->getPage());

    auto contin1 = dynamic_cast<FContinue *>(scheduler->figures[0]);
    EXPECT_EQ(left.x(), contin1->rect_.center.x);
    EXPECT_STREQ("A", contin1->getText().data());
    EXPECT_EQ(2, contin1->getPage());

    auto contin2 = dynamic_cast<FContinue *>(scheduler->figures[1]);
    EXPECT_EQ(left.x(), contin2->rect_.center.x);
    EXPECT_EQ(meta.ym() + scheduler->continueBlockSize().h / 2, contin2->rect_.center.y);
    EXPECT_STREQ("A", contin2->getText().data());
    EXPECT_EQ(5, contin2->getPage());

    auto vertLine = dynamic_cast<FLine *>(scheduler->figures[3]);
    EXPECT_EQ(5, vertLine->getPage());
    EXPECT_EQ(left.x(), vertLine->begin.x);
    EXPECT_EQ(meta.ym() + scheduler->continueBlockSize().h + meta.bs(), vertLine->begin.y);
    EXPECT_EQ(left.x(), vertLine->end.x);
    EXPECT_EQ(right.y(), vertLine->end.y);

    auto horizLine = dynamic_cast<FLine *>(scheduler->figures[4]);
    EXPECT_EQ(5, vertLine->getPage());
    EXPECT_EQ(left.x(), horizLine->begin.x);
    EXPECT_EQ(right.y(), horizLine->begin.y);
    EXPECT_EQ(right.x(), horizLine->end.x);
    EXPECT_EQ(right.y(), horizLine->end.y);
}
TEST_F(FEmborderScheduler, pushForkLines)
{
    Rect forkRect{10, 10, 30, 15};
    size_t left = 5, right = 15;
    scheduler->pushForkLines(forkRect, left, right);

    EXPECT_EQ(4, scheduler->figures.size());
    auto *rightVert = dynamic_cast<FLine *>(scheduler->figures.pop_back());
    auto *rightHoriz = dynamic_cast<FLine *>(scheduler->figures.pop_back());
    auto *leftVert = dynamic_cast<FLine *>(scheduler->figures.pop_back());
    auto *leftHoriz = dynamic_cast<FLine *>(scheduler->figures.pop_back());

    EXPECT_EQ(rightHoriz->begin.x, forkRect.center.x + forkRect.size.w / 2);
    EXPECT_EQ(rightHoriz->begin.y, forkRect.center.y);
    EXPECT_EQ(rightHoriz->end.x, right);
    EXPECT_EQ(rightHoriz->end.y, forkRect.center.y);

    EXPECT_EQ(rightVert->begin.x, right);
    EXPECT_EQ(rightVert->begin.y, forkRect.center.y);
    EXPECT_EQ(rightVert->end.x, right);
    EXPECT_EQ(rightVert->end.y, forkRect.center.y + forkRect.size.h / 2 + meta.bs());

    EXPECT_EQ(leftHoriz->begin.x, forkRect.center.x - forkRect.size.w / 2);
    EXPECT_EQ(leftHoriz->begin.y, forkRect.center.y);
    EXPECT_EQ(leftHoriz->end.x, left);
    EXPECT_EQ(leftHoriz->end.y, forkRect.center.y);

    EXPECT_EQ(leftVert->begin.x, left);
    EXPECT_EQ(leftVert->begin.y, forkRect.center.y);
    EXPECT_EQ(leftVert->end.x, left);
    EXPECT_EQ(leftVert->end.y, forkRect.center.y + forkRect.size.h / 2 + meta.bs());
}
TEST_F(FEmborderScheduler, pushSpaceLine)
{
    EXPECT_EQ(0, scheduler->figures.size());
    EmborderScheduler::State state = scheduler->getCurState();

    scheduler->pushSpaceLine("qwer");
    EXPECT_EQ(1, scheduler->figures.size());
    EXPECT_EQ(state.y() + meta.bs(), scheduler->curState.y());
    EXPECT_STREQ("qwer", scheduler->figures[0]->getText().data());
}
TEST_F(FEmborderScheduler, pushContinueFigure)
{
    EXPECT_EQ(0, scheduler->figures.size());
    EmborderScheduler::State state = scheduler->getCurState();

    scheduler->pushContinueFigure();
    EXPECT_EQ(1, scheduler->figures.size());
    EXPECT_EQ(state.width(), scheduler->curState.width());
    EXPECT_EQ(state.x(), scheduler->curState.x());
    EXPECT_EQ(state.y() + scheduler->continueBlockSize().h, scheduler->curState.y());
}
TEST_F(FEmborderScheduler, rectXFitSizeWithMarginGoodWidth)
{
    scheduler->curState.setW(5 * meta.sw());
    std::string text = "Hoo\n"
                       "Hoo\n"
                       "Hoo\n"
                       "Hoo";

    sRect output = scheduler->rectXFitSize(text, true);
    EXPECT_DOUBLE_EQ(3 * meta.sw() + meta.xp() * 2, output.w);
    EXPECT_DOUBLE_EQ(4 * meta.lh() + meta.yp() * 2, output.h);
}
/*TEST_F(FEmborderScheduler, rectXFitSizeWithMarginBadWidth)
{
    scheduler->curState.setW(5);
    std::string text = "Some text of any size\n" // 26
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    std::string rightOutput = "Some \n"
                              "text \n"
                              "of an\n"
                              "y siz\n"
                              "e\n"
                              "Don-v\n"
                              "an tr\n"
                              "ied t\n"
                              "o spe\n"
                              "ak\n"
                              "Hoo!\n"
                              "Ano c\n"
                              "onjun\n"
                              "ction";

    sRect output = scheduler->rectXFitSize(text, true);
    EXPECT_DOUBLE_EQ(5 * meta.sw() + meta.xp() * 2, output.w);
    EXPECT_DOUBLE_EQ(14 * meta.lh() + meta.yp() * 2, output.h);
}*/
/*TEST_F(FEmborderScheduler, rectXFitSizeWithoutMarginBadWidth)
{
    scheduler->curState.setW(5);
    std::string text = "Some text of any size\n" // 26
                       "Don-van tried to speak\n" // 22
                       "Hoo!\n" // 4
                       "Ano conjunction"; // 15

    std::string rightOutput = "Some \n"
                              "text \n"
                              "of an\n"
                              "y siz\n"
                              "e\n"
                              "Don-v\n"
                              "an tr\n"
                              "ied t\n"
                              "o spe\n"
                              "ak\n"
                              "Hoo!\n"
                              "Ano c\n"
                              "onjun\n"
                              "ction";

    sRect output = scheduler->rectXFitSize(text, false);
    EXPECT_DOUBLE_EQ(5 * meta.sw(), output.w);
    EXPECT_DOUBLE_EQ(14 * meta.lh(), output.h);
}*/
TEST_F(FEmborderScheduler, rectXFitSizeWithoutMarginGoodWidth)
{
    scheduler->curState.setW(5 * meta.sw());
    std::string text = "Hoo\n"
                       "Hoo\n"
                       "Hoo\n"
                       "Hoo";

    sRect output = scheduler->rectXFitSize(text, false);
    EXPECT_DOUBLE_EQ(3 * meta.sw(), output.w);
    EXPECT_DOUBLE_EQ(4 * meta.lh(), output.h);
}
TEST(FContinue, alphabet_check)
{
    FContinue::reset();
    FContinue fContinue1(Rect{});
    FContinue fContinue2(Rect{});
    FContinue fContinue3(Rect{});

    EXPECT_STREQ("A", fContinue1.getText().data());
    EXPECT_STREQ("A", fContinue2.getText().data());
    EXPECT_STREQ("B", fContinue3.getText().data());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop