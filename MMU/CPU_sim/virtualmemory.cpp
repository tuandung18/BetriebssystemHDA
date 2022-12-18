#include "virtualmemory.h"
#include<page.h>
#include<process.h>
virtualMemory::virtualMemory()
{

}

std::vector<Process*> virtualMemory::getDisk() const
{
    return disk;
}

void virtualMemory::addNewProcess(Process* newProcess)
{
    disk.push_back(newProcess);
}

Process *virtualMemory::getProcess(int index)
{
    return disk.at(index);
}

page *virtualMemory::getPageUsingFrameAll(int frame)
{
    for(unsigned int i{}; i < this->disk.size(); i++) {
        if(this->disk.at(i)->getPageUsingFrame(frame) != nullptr) {
            return this->disk.at(i)->getPageUsingFrame(frame);
        }
    }
    return nullptr;
}
