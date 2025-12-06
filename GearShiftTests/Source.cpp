/**
 * \file Source.cpp
 * \brief Punctul de intrare pentru suita de teste GoogleTest/GoogleMock.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
