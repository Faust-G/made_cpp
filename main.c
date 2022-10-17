#include<stdio.h>


#define INF 1e9
#include "weather.h"

int main(){
    //wearher_info* p;
    wearher_info p[3]={{1,2,3}, {3,0,5},{10,10,10}};

    wearher_info res = get_min_temperature(p, 3);
    printf("%f %f %f\n", res.temperature,res.fallout,res.wind_speed);


    res = get_max_temperature(p, 3);
    printf("%f %f %f\n", res.temperature,res.fallout,res.wind_speed);

    res = get_min_fallout(p, 3);
    printf("%f %f %f\n", res.temperature,res.fallout,res.wind_speed);

    res = get_max_fallout(p, 3);
    printf("%f %f %f\n", res.temperature,res.fallout,res.wind_speed);
    
    res = get_average(p, 3);
    printf("%f %f %f\n", res.temperature,res.fallout,res.wind_speed);
}