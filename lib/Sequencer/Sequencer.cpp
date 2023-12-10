#include "Sequencer.hpp"

#include <Arduino.h>

#include "HeaderMatrix.hpp"

void Sequencer_init()
{
}

void Sequencer_run()
{
    static uint32_t lastPrintTimeMs = 0;
    uint32_t currTimeMs = millis();

    if( ( currTimeMs - lastPrintTimeMs ) > 500 )
    {
        HeaderMatrix_PrintMatrix();
        lastPrintTimeMs = currTimeMs;
    }
}
