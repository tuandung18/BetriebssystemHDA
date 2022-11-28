#ifndef CPU_H
#define CPU_H
#include<iostream>
#include<vector>
class akkumulator;
class programCounter;
class Process;
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
    void execNewProcess(std::string fileName);
    void printProcess(Process* p);
    Process *getActiveProcess() const;
    void setActiveProcess(Process *newActiveProcess);

    akkumulator *getAkku() const;

    programCounter *getPc() const;

    int getQuantum() const;
    void changeActiveProcess();

private:
    int takt;
    std::string befehl;
    std::vector<int> waitingTakt;
    Process* activeProcess;
    std::vector<Process*> waitingProcess;
    std::vector<Process*> readyProcess;
    akkumulator* akku;
    programCounter* pc;
    std::vector<Process*> processVerlauf;
    const int quantum = 9999999;
};

#endif // CPU_H
