#include <iostream>
#include <gtest/gtest.h>

#include "Parser.h"
#include "Analyzers/ClikeAnalyzer.h"
#include "Schedulers/GostScheduler.h"

#include "Primitives/Follow.h"
#include "Primitives/Fork.h"
#include "Primitives/Cycle.h"
#include "Primitives/SubScheme.h"

#include "Figures/BegEnd.h"
#include "Figures/Hrombus.h"
#include "Figures/Rectangle.h"
#include "Figures/BorderedRect.h"

#include "Figures/Arrow.h"
#include "Figures/Line.h"






TEST(clike_analyzer_test, common) {
  ClikeAnalyzer analyzer;

  std::string input = "Begin\n\n"
                      "Follow\n\n"
                      "if (smth)\n "
                      "{ qwer }\n"
                      "for (i = 1; i < 10; i++)\n"
                      "{nothing}\n"
                      "End\n\n";

  std::vector<AbstractPrimitive *> answer = analyzer.analyze(input);
  std::vector<AbstractPrimitive *> right_answer = {
      new Follow("Begin"),
      new Follow("Follow"),
      new Fork("smth", 1, 0),
      new Follow("qwer"),
      new Cycle("i = 1; i < 10", "i++", 1),
      new Follow("End")
  };

  EXPECT_EQ(answer, right_answer);
}

TEST(gost_schedule_test, common) {
  GostScheduler scheduler;

  std::vector<AbstractPrimitive *> input = {
      new Follow("Begin"),
      new Follow("Follow"),
      new Fork("smth", 1, 0),
      new Follow("qwer"),
      new Cycle("i = 1; i < 10", "i++", 1),
      new Follow("End"),
  };

  std::vector<AbstractPrimitive *> answer = scheduler.schedule(input);
  std::vector<AbstractPrimitive *> right_answer = {
      new Beg("Begin"),
      new Follow("Follow"),
      new Fork("smth", 1, 0),
      new Follow("qwer"),
      new Cycle("i = 1; i < 10", "i++", 1),
      new Follow("End")
  };

  EXPECT_EQ(answer, right_answer);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}