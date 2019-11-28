//
// Created by arthur on 28.11.2019.
//

#ifndef FEMBORDERSCHEDULER_H
#define FEMBORDERSCHEDULER_H

#include <gtest/gtest.h>
#include "../Tools/Meta.h"
#include "../Scheduler/EmborderScheduler/EmborderScheduler.h"

class FEmborderScheduler: public ::testing::Test
{
protected:
    Meta meta;
    EmborderScheduler *scheduler;

    virtual void SetUp()
    {
        scheduler = new EmborderScheduler(meta);
        scheduler->initNewPage(1);
    }

    virtual void TearDown()
    {
        delete scheduler;
    }

};

#endif //FEMBORDERSCHEDULER_H
