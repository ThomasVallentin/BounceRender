//
// Created by Thomas Vallentin on 20/03/2022.
//

#ifndef BOUNCE_CORE_H
#define BOUNCE_CORE_H

#include <string>

// Logging
#ifdef BNC_LOG_DEBUG
#define BNC_DEBUG(msg, ...)     fprintf(stdout, (std::string("# Bounce Core DEBUG:    ") + msg + "\n").c_str(), __VA_ARGS__)
#else
#define BNC_DEBUG(msg, ...)
#endif

#define BNC_LOG_INFO
#ifdef BNC_LOG_INFO
#define BNC_INFO(msg, ...)      fprintf(stdout, (std::string("# Bounce Core INFO:     ") + msg + "\n").c_str(), __VA_ARGS__)
#else
#define BNC_INFO(msg, ...)
#endif

#define BNC_WARNING(msg, ...)   fprintf(stderr, (std::string("# Bounce Core WARNING:  ") + msg + "\n").c_str(), __VA_ARGS__)
#define BNC_ERROR(msg, ...)     fprintf(stderr, (std::string("# Bounce Core ERROR:    ") + msg + "\n").c_str(), __VA_ARGS__)
#define BNC_CRITICAL(msg, ...)  fprintf(stderr, (std::string("# Bounce Core CRITICAL: ") + msg + "\n").c_str(), __VA_ARGS__)

// Asserts
#define BNC_ENABLE_ASSERTS
#ifdef BNC_ENABLE_ASSERTS
    #define BNC_ASSERT(check, ...)    if (!(check)) { BNC_ERROR(__VA_ARGS__); }
#else
    #define BNC_ASSERT(...)
#endif //BNC_ENABLE_ASSERTS

#endif //BOUNCE_CORE_H
