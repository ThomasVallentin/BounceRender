//
// Created by Thomas Vallentin on 20/03/2022.
//

#ifndef RBND_CORE_H
#define RBND_CORE_H

#include <string>

// Logging
#ifdef RBND_LOG_DEBUG
#define RBND_DEBUG(msg, ...)     fprintf(stdout, (std::string("# Rebound Core DEBUG:    ") + msg + "\n").c_str(), __VA_ARGS__)
#else
#define RBND_DEBUG(msg, ...)
#endif

#define RBND_LOG_INFO
#ifdef RBND_LOG_INFO
#define RBND_INFO(msg, ...)      fprintf(stdout, (std::string("# Rebound Core INFO:     ") + msg + "\n").c_str(), __VA_ARGS__)
#else
#define RBND_INFO(msg, ...)
#endif

#define RBND_WARNING(msg, ...)   fprintf(stderr, (std::string("# Rebound Core WARNING:  ") + msg + "\n").c_str(), __VA_ARGS__)
#define RBND_ERROR(msg, ...)     fprintf(stderr, (std::string("# Rebound Core ERROR:    ") + msg + "\n").c_str(), __VA_ARGS__)
#define RBND_CRITICAL(msg, ...)  fprintf(stderr, (std::string("# Rebound Core CRITICAL: ") + msg + "\n").c_str(), __VA_ARGS__)

// Asserts
#define RBND_ENABLE_ASSERTS
#ifdef RBND_ENABLE_ASSERTS
    #define RBND_ASSERT(check, ...)    if (!(check)) { RBND_ERROR(__VA_ARGS__); }
#else
    #define RBND_ASSERT(...)
#endif //RBND_ENABLE_ASSERTS

#endif //RBND_CORE_H
