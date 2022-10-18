#include <gtest/gtest.h>

extern "C" {
#include "weather.h"
}

wearher_info p[3] = {{1, 2, 3}, {3, 0, 5}, {10, 10, 10}};

TEST(Weather, TestMinWeather) {
  wearher_info res = get_min_temperature(p, 3);
  wearher_info answer = {1, 2, 3};
  EXPECT_EQ(answer.temperature, res.temperature);
  EXPECT_EQ(answer.fallout, res.fallout);
  EXPECT_EQ(answer.wind_speed, res.wind_speed);
}

TEST(Weather, TestMaxWeather) {
  wearher_info res = get_max_temperature(p, 3);
  wearher_info answer = {10, 10, 10};
  EXPECT_EQ(answer.temperature, res.temperature);
  EXPECT_EQ(answer.fallout, res.fallout);
  EXPECT_EQ(answer.wind_speed, res.wind_speed);
}

TEST(Weather, TestMinFallout) {
  wearher_info res = get_min_fallout(p, 3);
  wearher_info answer = {3, 0, 5};
  EXPECT_EQ(answer.temperature, res.temperature);
  EXPECT_EQ(answer.fallout, res.fallout);
  EXPECT_EQ(answer.wind_speed, res.wind_speed);
}

TEST(Weather, TestMaxFallout) {
  wearher_info res = get_max_fallout(p, 3);
  wearher_info answer = {10, 10, 10};
  EXPECT_EQ(answer.temperature, res.temperature);
  EXPECT_EQ(answer.fallout, res.fallout);
  EXPECT_EQ(answer.wind_speed, res.wind_speed);
}

TEST(Weather, TestAverage) {
  wearher_info res = get_average(p, 3);
  wearher_info answer = {4.666667, 4, 6};
  EXPECT_EQ(abs(answer.temperature - res.temperature) < 1e-5, true);
  EXPECT_EQ(answer.fallout, res.fallout);
  EXPECT_EQ(answer.wind_speed, res.wind_speed);
}
