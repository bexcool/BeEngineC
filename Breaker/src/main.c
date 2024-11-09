#include <stdio.h>
#include "BeEngine.h"

int main(int argc, const char* argv[]) {
    engineCore_startGameEngine("Breaker (BeEngineC)", argc, argv);

    LOG("Logging from main!");
}