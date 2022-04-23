//
// Created by Thomas Vallentin on 13/04/2022.
//

#ifndef RBND_REBOUND_H
#define RBND_REBOUND_H

#define GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define FOR_EACH_0(_call, ...)
#define FOR_EACH_1(_call, x, ...) _call(x)
#define FOR_EACH_2(_call, x, ...) _call(x) FOR_EACH_1(_call, __VA_ARGS__)
#define FOR_EACH_3(_call, x, ...) _call(x) FOR_EACH_2(_call, __VA_ARGS__)
#define FOR_EACH_4(_call, x, ...) _call(x) FOR_EACH_3(_call, __VA_ARGS__)
#define FOR_EACH_5(_call, x, ...) _call(x) FOR_EACH_4(_call, __VA_ARGS__)
#define FOR_EACH_6(_call, x, ...) _call(x) FOR_EACH_5(_call, __VA_ARGS__)
#define FOR_EACH_7(_call, x, ...) _call(x) FOR_EACH_6(_call, __VA_ARGS__)
#define FOR_EACH_8(_call, x, ...) _call(x) FOR_EACH_7(_call, __VA_ARGS__)

#define CALL_MACRO_FOR_EACH(x, ...) \
    GET_NTH_ARG("ignored", ##__VA_ARGS__, \
    FOR_EACH_8, FOR_EACH_7, FOR_EACH_6, FOR_EACH_5, FOR_EACH_4, \
    FOR_EACH_3, FOR_EACH_2, FOR_EACH_1, FOR_EACH_0)(x, ##__VA_ARGS__)



#endif //RBND_REBOUND_H
