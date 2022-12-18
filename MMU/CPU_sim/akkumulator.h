#ifndef AKKUMULATOR_H
#define AKKUMULATOR_H


class akkumulator
{
public:
    akkumulator();
    void load(int newValue);
    void add(int value);
    void substract(int value);
    int getValue() const;
    void setValue(int newValue);

private:
    int value;

};

#endif // AKKUMULATOR_H
