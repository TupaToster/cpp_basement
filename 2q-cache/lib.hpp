/**
 * @file config.hpp
 * @author TupaToster
 * @brief Use this file to config some program wide constants and include new libs
 * @brief Include in every file in project!
 * @version 1.1
 * @date 2024-03-26
 */

#pragma once
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <cassert>
#include <cmath>

extern const double EPS;

extern const char LogFileName[];

extern FILE* LogFilePtr;

extern const unsigned int HashMult;

int cmp (const double par1, const double par2);

unsigned int cntHash (void* from, void* to);

void logIntern (const void* val, const char* varType, const char* varName, size_t varSize, const char* fileName, const char* funcName, size_t line);

const char* getFormatIntern (const char* varType);

#define getFormat(var) getFormatIntern (typeid (var).name ())

/**
 * @brief logs using some magick and logIntern
 */
#define Log_(a)                                                                                                         \
            {if (LogFilePtr == NULL){                                                                                   \
                LogFilePtr = fopen ("logs_out.html", "w");                                                              \
                setvbuf (LogFilePtr, NULL, _IONBF, 0);                                                                  \
                fprintf (LogFilePtr, "<pre>----------------------------------------\n"                                  \
                "<style> body {padding: 25px; background-color: #252525; color: white; font-size: 25px;} </style>"      \
                "Logging session at compiled time : %s %s<br><br></pre>\n\n", __TIME__, __DATE__);                      \
            }                                                                                                           \
            logIntern (&a, typeid (a).name (), #a, sizeof (a), __FILE__, __FUNCTION__, __LINE__);}

/**
 * @brief writes as printf to log file
 */
#define Log_printf(...)                                                                                                 \
    {if (LogFilePtr == NULL){                                                                                           \
                LogFilePtr = fopen ("logs_out.html", "w");                                                              \
                setvbuf (LogFilePtr, NULL, _IONBF, 0);                                                                  \
                fprintf (LogFilePtr, "<pre>----------------------------------------\n"                                  \
                "<style> body {padding: 25px; background-color: #252525; color: white; font-size: 25px;} </style>"      \
                "Logging session at compiled time : %s %s<br><br></pre>\n\n", __TIME__, __DATE__);                      \
    }                                                                                                                   \
    fprintf (LogFilePtr, __VA_ARGS__);}

/**
 * @brief log function for classes
 * @note Log function should be defined inside class for it to work
 */
#define Log_c(clas) {clas.Log (#clas, __FILE__, __FUNCTION__, __LINE__);}

/**
 * @brief disables logs if NDEBUG
 */
#ifdef NDEBUG
#define Log_c(clas) {}
#define Log_(a) {}
#define Log_printf (a) {}
#endif
