#ifndef __LOG_H_
#define __LOG_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifdef _COLOR
/* Want more/other colors? See https://stackoverflow.com/a/3219471 and
 * https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
 */
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#else
#define ANSI_COLOR_RED
#define ANSI_COLOR_GREEN
#define ANSI_COLOR_YELLOW
#define ANSI_COLOR_CYAN
#define ANSI_COLOR_RESET
#endif

#define _LOG(color, prefix, msg, ...)\
    do {\
        fprintf(stderr, color prefix msg ANSI_COLOR_RESET "\n", ##__VA_ARGS__);\
    } while (0)

#ifdef _NOLOGS
    #define ERROR(msg, ...)
    #define SUCCESS(msg, ...)
    #define INFO(msg, ...)
#else
    #define ERROR(msg, ...) _LOG(ANSI_COLOR_RED, "[ERROR] ", msg, ##__VA_ARGS__)
    #define SUCCESS(msg, ...) _LOG(ANSI_COLOR_GREEN, "[SUCCESS] ", msg, ##__VA_ARGS__)
    #define INFO(msg, ...) _LOG(ANSI_COLOR_YELLOW, "[INFO] ", msg, ##__VA_ARGS__)
#endif

#endif // __LOG_H_