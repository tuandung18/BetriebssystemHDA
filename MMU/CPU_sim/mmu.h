#ifndef MMU_H
#define MMU_H
#include<iostream>
class ram;
class virtualMemory;
class Process;
class page;
class mmu

{
public:
    mmu(ram* mem, virtualMemory* vm);
    /**
     * @brief swapPage swap new Page that need to use RAM with not recently used frame in RAM
     * @param activeProcess currently active process
     * @param value address to write or read from
     */
    void addPage(Process* activeProcess, std::string value);
    void swapPage(Process* activeProcess, std::string value);
    int getFrameNotRecentlyUsed();
    int calculatePage(int address);
    int convertHexaToInt(std::string value);
    /**
     * @brief checkIfExistsPage check if page of active process is already in the ram
     * @param activeProcess currently active process
     * @param page  index of page in Process Table
     * @return true if page already exists, otherwise false
     */
    bool checkIfExistsPage(Process* activeProcess, int page);
    int getExistsPage(Process* activeProcess, int page);
    void copyDataPageToFrame(int frameToUSe, int PageIndex, Process* activeProcess);
    void saveDataFrameToPage(int frameToUse);
    /**
     * @brief getFrameNRUBasedPriority get the frame with least priority
     * @return frame with least priority
     */
    int getFrameNRUBasedPriority();


    /**
     * @brief getFrameKlass get priority class (NRU) based on RBit and Mbit
     * @param p is the page in ram frame  to check
     * @return priotiry class of the page
     */
    int getFrameKlass(page* p);


private:
    ram* mem;
    virtualMemory* vm;
};

#endif // MMU_H
