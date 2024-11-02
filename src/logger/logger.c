#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "logger.h"

void logger_init(const char *filePath) {
    strcpy(logFilePath, filePath);
    logFile = fopen(logFilePath, "w+");

    LOG("Logger initialized. Log path: \"%s\"", realpath(logFilePath, NULL));
}

void logger_log(LogType type, char *message, ...) {
    char buffer[256], timeBuffer[16];
    time_t now = time(NULL);
    struct tm tm_now;

    va_list args;
    va_start(args, message);

    localtime_r(&now, &tm_now);
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", &tm_now);

    switch (type)
    {
        case INFO:
            sprintf(buffer, "%s - [INFO] ", timeBuffer);
            break;

        case WARNING:
            sprintf(buffer, "%s - [WARNING] ", timeBuffer);
            break;

        case ERROR:
            sprintf(buffer, "%s - [ERROR] ", timeBuffer);
    }

    printf("%s", buffer); 
    fprintf(logFile, "%s", buffer);

    vprintf(message, args);
    vfprintf(logFile, message, args);
    va_end(args);  

    fprintf(logFile, "\n");
    printf("\n");
}