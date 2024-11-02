#include <stdio.h>
#include <stdlib.h>
#include "logger/logger.h"
#include "gameLoop.h"

int main() {
    logger_init("./log.txt");

    LOG("Starting application...");

    LOG("Test: %d", 10);
exi
    LOG_W("Varuji tě číslicí %d", 69);
    return 0;
}