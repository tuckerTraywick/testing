#ifndef LOGGING_H
#define LOGGING_H

#include <stdbool.h>
#include <stdio.h>

#define LOG_FORMAT " %s:%d:%s: "
#define DEBUG_PREFIX   "[DEBUG]  "
#define INFO_PREFIX    "[INFO]   "
#define WARNING_PREFIX "[WARNING]"
#define ERROR_PREFIX   "[ERROR]  "

#define logDebug(string) if (enableDebug) {fprintf(debugOut, DEBUG_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfDebug(string, ...) if (enableDebug) {fprintf(debugOut, DEBUG_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logInfo(string) if (enableInfo) {fprintf(infoOut, INFO_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfInfo(string, ...) if (enableInfo) {fprintf(infoOut, INFO_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logWarning(string) if (enableWarning) {fprintf(warningOut, WARNING_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfWarning(string, ...) if (enableWarning) {fprintf(warningOut, WARNING_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logError(string) if (enableError) {fprintf(errorOut, ERROR_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfError(string, ...) if (enableError) {fprintf(errorOut, ERROR_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define putsDebug(string) if (enableDebug) {fputs((string), debugOut);}
#define printfDebug(string, ...) if (enableDebug) {fprintf(debugOut, (string), __VA_ARGS__);}

#define putsInfo(string) if (enableInfo) {fputs((string), infoOut);}
#define printfInfo(string, ...) if (enableInfo) {fprintf(infoOut, (string), __VA_ARGS__);}

#define putsWarning(string) if (enableWarning) {fputs((string), debugOut);}
#define printfWarning(string, ...) if (enableWarning) {fprintf(debugOut, (string), __VA_ARGS__);}

#define putsError(string) if (enableError) {fputs((string), debugOut);}
#define printfError(string, ...) if (enableError) {fprintf(debugOut, (string), __VA_ARGS__);}

// These variables need to be set by code that uses this header.
FILE* debugOut = NULL;
FILE *infoOut = NULL;
FILE *warningOut = NULL;
FILE *errorOut = NULL;
bool enableDebug = true;
bool enableInfo = true;
bool enableWarning = true;
bool enableError = true;

#endif // LOGGING_H
