#ifndef CPU_H
#define CPU_H
#include<iostream>
#include<vector>
#include<array>
#include<cmath>
#include<limits.h>
class akkumulator;
class programCounter;
class Process;
class ram;
class mmu;
class virtualMemory;
class CPU
{
public:
    CPU();
    void block();
    bool idle();
    void addTakt();
    void terminateProcess();
    void execute();
    int getTakt() const;
    std::string getBefehlValue();
    /**
     * @brief execNewProcess as 'X' in script, execute new process
     * @param fileName is file to execute
     */
    void execNewProcess(std::string fileName);
    void printProcess(Process* p);
    Process *getActiveProcess() const;
    void setActiveProcess(Process *newActiveProcess);

    akkumulator *getAkku() const;

    programCounter *getPc() const;
    /**
     * @brief getQuantum get the limited run time
     * @return the run time that a process is allowed to run
     */
    int getQuantum() const;
    /**
     * @brief changeActiveProcess change active process to the first one in wait list
     */
    void changeActiveProcess();
    /**
     * @brief readFromRam read one byte in Ram,  and load that value to akkumulator
     * @param value is the address to read from, is hexadecimal
     */
    void readFromRam(std::string& value);
    /**
     * @brief readFromRam write value of akkumulator to address value
     * @param value is the address to write to ram, is hexadecimal
     */
    void writeToRam(std::string& value);
    /**
     * @brief stringToHex transform string number to hex (z.B 40 -> 64, 10 -> A)
     * @param value
     */
    void stringHexToInt(std::string& value);
    /**
     * @brief calculateOffset calculate offset of address to write or read
     * @param address   address to write or read
     * @return offset
     */
    unsigned int calculateOffset(int address);

    void printDisk();

    void resetReferenceBit();
private:
    int takt;
    /**
     * @brief befehl is command in one line
     */
    std::string befehl;
    /**
     * @brief waitingTakt is the vector of takt,
     * the first value in the vector is when the first process in waiting becomes ready
     */
    std::vector<int> waitingTakt;
    /**
     * @brief activeProcess currently running process
     */
    Process* activeProcess;
    /**
     * @brief waitingProcess is blocked process
     */
    std::vector<Process*> waitingProcess;
    /**
     * @brief readyProcess is wait list of processes that are ready to run
     */
    std::vector<Process*> readyProcess;
    /**
     * @brief akku akkumulator, where calculation happens
     */
    akkumulator* akku;
    /**
     * @brief pc is program counter
     */
    programCounter* pc;
    /**
     * @brief processVerlauf history of processes that have been executed
     */
    std::vector<Process*> processVerlauf;
    const int quantum = 4;   //simulate no quantum limited, set to whatever you want if you want to limit running time
    /**
     * @brief memory is the ram, USHRT_MAX is the max value of unsigned short int (65535)
     */
    std::array<char, USHRT_MAX> memory;
    /**
     * @brief mem this is ram
     */
    ram* mem;

    /**
     * @brief MMU memory management unit
     */
    mmu* MMU;

    virtualMemory* vm;

};

#endif // CPU_H
