//
// Created by arthur on 24.11.2019.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>

TEST(test, 1)
{
    EXPECT_EQ(1, 2);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop