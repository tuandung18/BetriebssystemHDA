#include "page.h"

page::page()
{
    referenziert = 0;
    modifiziert = 0;
    for(unsigned int i{}; i < pageData.size(); i++) {
        pageData.at(i) = 0;
    }
    nruCounter = 0;
}

std::array<unsigned char, 64> page::getPageData() const
{
    return pageData;
}

unsigned int page::getNruCounter() const
{
    return nruCounter;
}

void page::incrementCounter()
{
    nruCounter++;
}

bool page::getModifiziert() const
{
    return modifiziert;
}

void page::setModifiziert(bool newModifiziert)
{
    modifiziert = newModifiziert;
}

bool page::getReferenziert() const
{
    return referenziert;
}

void page::setReferenziert(bool newReferenziert)
{
    referenziert = newReferenziert;
}

void page::setNruCounter(unsigned int newNruCounter)
{
    nruCounter = newNruCounter;
}

void page::setPageData(char data, int index)
{
    this->pageData.at(index) = data;
}

void page::printAll()
{
    for(int i{}; i< 64; i++) {
        std::cout << this->pageData.at(i) << std::endl;
    }
}
