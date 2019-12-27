//
// Created by arthur on 28.11.2019.
//

#ifndef FEMBORDERSCHEDULER_H
#define FEMBORDERSCHEDULER_H

#include <gtest/gtest.h>
#include "../Tools/Meta.h"
#include "../Scheduler/EmborderScheduler/GostScheduler.h"

class FEmborderScheduler: public ::testing::Test
{
protected:
  Meta meta;
  GostScheduler *scheduler;

    virtual void SetUp()
    {
      meta = Meta(
          210,
          297,
          0,
          0,
          0,
          0,
          11,
          7,
          5);
      scheduler = new GostScheduler(meta);
      scheduler->initNewPage(1);
    }

    virtual void TearDown()
    {
        delete scheduler;
    }
};

#endif //FEMBORDERSCHEDULER_H
