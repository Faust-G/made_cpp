#include <gtest/gtest.h>

extern "C" {
    #include "weather.h"
}

wearher_info p[3]={{1,2,3}, {3,0,5},{10,10,10}};

TEST(Weather, TestMinWeather) {
    wearher_info res = get_min_temperature(p, 3);
    wearher_info answer = {1,2,3};
    EXPECT_EQ(answer.temperature + 1, res.temperature);
    //EXPECT_EQ(1, fib(2));
}

//TEST(Weather, Test10) {
  //  EXPECT_EQ(55, fib(10));
//}