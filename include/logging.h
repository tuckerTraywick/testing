#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

#define LOG_FORMAT "[%s:%d:%s] "
#define DEBUG_PREFIX   "DEBUG "
#define INFO_PREFIX    "INFO "
#define WARNING_PREFIX "WARNING "
#define ERROR_PREFIX   "ERROR "

#define logDebug(string) if (logDebugOutput) {fprintf(logDebugOutput, DEBUG_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);} else {}
#define logfDebug(string, ...) if (logDebugOutput) {fprintf(logDebugOutput, DEBUG_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);} else {}

#define logInfo(string) if (logInfoOutput) {fprintf(logInfoOutput, INFO_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);} else {}
#define logfInfo(string, ...) if (logInfoOutput) {fprintf(logInfoOutput, INFO_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);} else {}

#define logWarning(string) if (logWarningOutput) {fprintf(logWarningOutput, WARNING_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);} else {}
#define logfWarning(string, ...) if (logWarningOutput) {fprintf(logWarningOutput, WARNING_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);} else {}

#define logError(string) if (logErrorOutput) {fprintf(logErrorOutput, ERROR_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);} else {}
#define logfError(string, ...) if (logErrorOutput) {fprintf(logErrorOutput, ERROR_PREFIX LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);} else {}

#define putsDebug(string) if (logDebugOutput) {fputs((string), logDebugOutput);} else {}
#define printfDebug(string, ...) if (logDebugOutput) {fprintf(logDebugOutput, (string), __VA_ARGS__);} else {}

#define putsInfo(string) if (logInfoOutput) {fputs((string), logInfoOutput);} else {}
#define printfInfo(string, ...) if (logInfoOutput) {fprintf(logInfoOutput, (string), __VA_ARGS__);} else {}

#define putsWarning(string) if (logWarningOutput) {fputs((string), logWarningOutput);} else {}
#define printfWarning(string, ...) if (logWarningOutput) {fprintf(logWarningOutput, (string), __VA_ARGS__);} else {}

#define putsError(string) if (logErrorOutput) {fputs((string), logErrorOutput);} else {}
#define printfError(string, ...) if (logErrorOutput) {fprintf(logErrorOutput, (string), __VA_ARGS__);} else {}

// These variables need to be set by code that uses this header.
extern FILE *logDebugOutput;
extern FILE *logInfoOutput;
extern FILE *logWarningOutput;
extern FILE *logErrorOutput;

#endif // LOGGING_H
