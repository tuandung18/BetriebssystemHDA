#ifndef PAGE_H
#define PAGE_H

#include<array>
#include<iostream>
class page
{
public:
    page();

    std::array<unsigned char, 64> getPageData() const;

    unsigned int getNruCounter() const;

    void incrementCounter();

    bool getModifiziert() const;
    void setModifiziert(bool newModifiziert);

    bool getReferenziert() const;
    void setReferenziert(bool newReferenziert);

    void setNruCounter(unsigned int newNruCounter);
    void setPageData(char data, int index);
    void printAll();
private:
    std::array<unsigned char, 64> pageData;
    bool referenziert;
    bool modifiziert;
    unsigned int nruCounter;
};

#endif // PAGE_H
