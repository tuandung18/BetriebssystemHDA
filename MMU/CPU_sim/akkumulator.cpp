#include "akkumulator.h"

akkumulator::akkumulator()
{
    value = 0;
}

void akkumulator::load(int newValue)
{
    this->value = newValue;
}
void akkumulator::add(int v) {
    this->value += v;

}
void akkumulator::substract(int v) {
    this->value -= v;
}

int akkumulator::getValue() const
{
    return value;
}

void akkumulator::setValue(int newValue)
{
    value = newValue;
}
