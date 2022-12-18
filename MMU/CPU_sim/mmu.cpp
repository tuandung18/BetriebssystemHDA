#include "mmu.h"
#include<cmath>
#include<process.h>
#include<ram.h>
#include<page.h>
#include<virtualmemory.h>
#include<sstream>
#define log(x) std::cout << x << std::endl;
mmu::mmu(ram* mem, virtualMemory* vm)
{
    this->mem = mem;
    this->vm = vm;
}

void mmu::addPage(Process *activeProcess, std::string value)
{
    if(checkIfExistsPage(activeProcess, calculatePage(convertHexaToInt(value)))) {
        return;
    }
    else {

        int pageIndex = calculatePage(convertHexaToInt(value));
        int frameIndex = mem->getUsedFrame();
        //log("frame: " << frameIndex);

        mem->setFrameProcess(frameIndex, activeProcess);
        mem->setFramePageIndex(frameIndex, pageIndex);
        //std::cout <<  "frame: "<< mem->getFrame().at(frameIndex).first->getName() << " pageIndex: " << mem->getFrame().at(frameIndex).second << " page: " << pageIndex << std::endl;
        mem->getFrame().at(frameIndex).second = pageIndex;
        activeProcess->setPageFrame(pageIndex, frameIndex);
        copyDataPageToFrame(frameIndex, pageIndex, activeProcess);
    }
}
//TODO: truong hop trong page co san frame roi thi khong can phai swap hoac add
void mmu::swapPage(Process* activeProcess, std::string value)
{
    int address = convertHexaToInt(value);
    //log("address: " << address);
    int page = calculatePage(address);

    if(checkIfExistsPage(activeProcess, page)) {
        return;
    }
    if(activeProcess->getPageFrame(page) == -1) {

        //pageNRU is the page that is not recently used in ram, start with 1 -> 4
        int frameNRU = getFrameNRUBasedPriority();

        //log(mem->getFrame().at(frameNRU).first->getName());

        //TODO: set lai pageNRU frame thanh -1, done
        Process* processOnRam = mem->getFrame().at(frameNRU).first;
        int pageIndex = mem->getFrame().at(frameNRU).second;

        processOnRam->setPageFrame(pageIndex, -1);
        //save data from not recently used frame to page first
        saveDataFrameToPage(frameNRU);
        mem->getFrame().at(frameNRU).first->getPage(page)->setNruCounter(0);

        //then copy data from page that required to use ram to the frame
        mem->setFrameProcess(frameNRU, activeProcess);

        mem->setFramePageIndex(frameNRU, page);

        mem->getFrame().at(frameNRU).first->setPageFrame( mem->getFrame().at(frameNRU).second, frameNRU);
        copyDataPageToFrame(frameNRU, page, activeProcess);

        activeProcess->setPageFrame(page, frameNRU);
    }
    else {
        return;
    }
}

int mmu::getFrameNotRecentlyUsed()
{
    unsigned int tmp{}, size{};
    int frameIndex{};
    if(mem->isFull()) {
        size = mem->getFrame().size();
    }
    else {
        size = mem->getUsedFrame();
    }
    tmp = mem->getFrame().at(0).first->getPage(mem->getFrame().at(0).second)->getNruCounter();
    for(unsigned int i{0}; i < size; i++) {
        unsigned int nruCounter = mem->getFrame().at(i).first->getPage(mem->getFrame().at(i).second)->getNruCounter();
        if(tmp < nruCounter) {
        tmp = nruCounter;
        frameIndex = i;
        //std::cout << "counter: " << nruCounter << " frameIndex: "<< frameIndex<< std::endl;

        }
    }
    return frameIndex;
}

int mmu::calculatePage(int address) {
    return address/SIZE_OF_PAGE;
}

int mmu::convertHexaToInt(std::string value)
{
    unsigned short int address{};
    std::stringstream ss;
    ss << std::hex << value;
    ss >> address;

    return address;
}

bool mmu::checkIfExistsPage(Process *activeProcess, int page)
{

    for(unsigned int i{}; i < mem->getFrame().size(); i++) {
        if(mem->getFrame().at(i).first == activeProcess && mem->getFrame().at(i).second == page) {
            return true;
        }
    }
    return false;
}

int mmu::getExistsPage(Process *activeProcess, int page)

{
   // log(activeProcess  << " " << page);
   // log(mem->getFrame().at(0).first << " " << mem->getFrame().at(0).second);
    for(unsigned int i{}; i < mem->getFrame().size(); i++) {

        if(mem->getFrame().at(i).first == activeProcess && mem->getFrame().at(i).second == page) {
            return i;
        }
    }
    return -1;
}

void mmu::copyDataPageToFrame(int frameToUSe, int PageIndex, Process* activeProcess)
{
    for(int i = 0; i < SIZE_OF_PAGE-1; i++) {
        mem->getRamData().at(SIZE_OF_PAGE*frameToUSe + i) = activeProcess->getPage(PageIndex)->getPageData().at(i);
    }
}

void mmu::saveDataFrameToPage(int frameToUse)
{
    for(int i = 0; i < SIZE_OF_PAGE; i++) {
        mem->getFrame().at(frameToUse).first->getPage( mem->getFrame().at(frameToUse).second)->setPageData(mem->getRamData().at(SIZE_OF_PAGE*frameToUse+i), i)  ;
    }
}

int mmu::getFrameNRUBasedPriority()
{
    int priority{999};
    int frame{-1};
    for(unsigned int i{}; i < mem->getFrame().size(); i++) {
        page* p = mem->getFrame().at(i).first->getPageUsingFrame(i);

        if(p == nullptr) {
            continue;
        }
        int tmp = getFrameKlass(p);
        if(priority > tmp) {
            frame = i;
            priority = tmp;
        }
    }

    return frame;
}

int mmu::getFrameKlass(page *p)
{

    if(p->getReferenziert() == 0 && p->getModifiziert() == 0) {
        return 0;
    }
    else if(p->getReferenziert() == 0 && p->getModifiziert() == 1 ) {
        return 1;

    }
    else if(p->getReferenziert() == 1 && p->getModifiziert() == 0) {
        return 2;
    }
    else if(p->getReferenziert() == 1 && p->getModifiziert() == 1) {
        return 3;
    }
//    log("ref: " << p->getReferenziert() << " mod: " << p->getModifiziert());
    return -1;
}





