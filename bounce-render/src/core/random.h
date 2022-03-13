//
// Created by tvallentin on 11/03/2022.
//

#ifndef BOUNCE_RANDOM_H
#define BOUNCE_RANDOM_H

#include "Bounce.h"

#include <random>

static std::default_random_engine globalRandomGenerator;


template <typename T>
T RandomReal(const T &min=0, const T &max=1) {
    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(globalRandomGenerator);
}

template <typename T>
Imath::Vec2<T> RandomVector2(const T &min = 0, const T &max = 1) {
    std::uniform_real_distribution<T> distribution(min, max);
    return Imath::Vec2<T>(distribution(globalRandomGenerator),
                          distribution(globalRandomGenerator));
}


template <typename T>
Imath::Vec3<T> RandomVector3(const T &min = 0, const T &max = 1) {
    std::uniform_real_distribution<T> distribution(min, max);
    return Imath::Vec3<T>(distribution(globalRandomGenerator),
                          distribution(globalRandomGenerator),
                          distribution(globalRandomGenerator));
}


template <typename T>
T RandomInteger(const T &min, const T &max) {
    std::uniform_int_distribution<T> distribution(min, max);
    return distribution(globalRandomGenerator);
}


#endif //BOUNCE_RANDOM_H
