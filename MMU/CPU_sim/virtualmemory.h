#ifndef VIRTUALMEMORY_H
#define VIRTUALMEMORY_H

#include<vector>
class Process;
class page;
class virtualMemory
{
public:
    virtualMemory();

    std::vector<Process*> getDisk() const;
    void addNewProcess(Process* newProcess);
    Process* getProcess(int index);
    page *getPageUsingFrameAll(int frame);
private:
    std::vector<Process*> disk;
};

#endif // VIRTUALMEMORY_H
