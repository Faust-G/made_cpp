#include "weather.h"

wearher_info get_min_temperature(wearher_info arr[], size_t size){
    wearher_info res = {
        .temperature = INF,
        .fallout = INF,
        .wind_speed = INF
    };

    for(size_t i = 0; i < size; ++i)
        if(arr[i].temperature < res.temperature)
            res = arr[i];
    
    return res;
}

wearher_info get_max_temperature(wearher_info arr[], size_t size){
    wearher_info res = {
        .temperature = -INF,
        .fallout = -INF,
        .wind_speed = -INF
    };

    for(size_t i = 0; i < size; ++i)
        if(arr[i].temperature > res.temperature)
            res = arr[i];
    
    return res;
}

wearher_info get_min_fallout(wearher_info arr[], size_t size){
    wearher_info res = {
        .temperature = INF,
        .fallout = INF,
        .wind_speed = INF
    };

    for(size_t i = 0; i < size; ++i)
        if(arr[i].fallout < res.fallout)
            res = arr[i];
    
    return res;
}

wearher_info get_max_fallout(wearher_info arr[], size_t size){
    wearher_info res = {
        .temperature = -INF,
        .fallout = -INF,
        .wind_speed = -INF
    };

    for(size_t i = 0; i < size; ++i)
        if(arr[i].fallout > res.fallout)
            res = arr[i];
    
    return res;
}

wearher_info get_average(wearher_info arr[], size_t size){
        wearher_info res = {
        .temperature = 0,
        .fallout = 0,
        .wind_speed = 0
    };
    for(size_t i = 0; i < size; ++i){
        res.temperature += arr[i].temperature;
        res.fallout += arr[i].fallout;
        res.wind_speed += arr[i].wind_speed;
    }
    res.temperature /= size;
    res.fallout /= size;
    res.wind_speed /= size;
    return res;
}