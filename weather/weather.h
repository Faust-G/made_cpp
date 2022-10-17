#ifndef __weather
#define __weather

#include<stdio.h>

#define INF 1e9

typedef struct{
    double temperature;
    double fallout;
    double wind_speed;
} wearher_info;

wearher_info get_min_temperature(wearher_info arr[], size_t size);
wearher_info get_max_temperature(wearher_info arr[], size_t size);
wearher_info get_min_fallout(wearher_info arr[], size_t size);
wearher_info get_max_fallout(wearher_info arr[], size_t size);
wearher_info get_average(wearher_info arr[], size_t size);

#endif