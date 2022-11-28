#include "programcounter.h"

programCounter::programCounter()
{
    value = 0;
}

int programCounter::getValue() const
{
    return value;
}

void programCounter::setValue(int newValue)
{
    value = newValue;
}
