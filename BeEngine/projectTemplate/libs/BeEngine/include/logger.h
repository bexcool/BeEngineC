#include <stdarg.h>
#include <stdio.h>

// Info
#define LOG(message, ...) logger_log(INFO, message, ## __VA_ARGS__) // If the variable arguments are empty, ty ## removes "," in the preprocessor
// Warning
#define LOG_W(message, ...) logger_log(WARNING, message, ## __VA_ARGS__) 
// Error
#define LOG_E(message, ...) logger_log(ERROR, message, ## __VA_ARGS__) 

typedef enum {
    INFO,
    WARNING,
    ERROR
} LogType;

extern char logger_logPath[256];
extern FILE *logger_logFile;

void logger_init(const char *logFilePath);
void logger_log(LogType type, const char *message, ...);
void logger_stop();