#include <stdarg.h>

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

char logFilePath[256];
FILE *logFile;

void logger_init(const char *logFilePath);
void logger_log(LogType type, char *message, ...);