#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H


class programCounter
{
public:
    programCounter();
    int getValue() const;
    void setValue(int newValue);

private:
    int value;
};

#endif // PROGRAMCOUNTER_H
