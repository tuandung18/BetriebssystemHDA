#include "process.h"
#include<string>
#define log(x) std::cout << x << std::endl;
Process::Process(std::string fileName) : start(0), end(0), savedAkku (0), savedPC (0)
{
    static int id = 0;
    setPid(id);
    id++;
    name = fileName;
    std::fstream path("/home/edward/git/CPU_Simulator/CPU_sim/test_program/" +fileName);
    readFile(path);
    activeTime = 0;
}

Process::~Process()
{

}

void Process::readFile(std::fstream &path)
{
    if(!path.good()) {
        throw("file can not be opened");
    }
    std::string line;
    while(!path.eof()) {
        getline(path, line);
        befehlsatz.push_back(line);
    }

}

void Process::setStart(int newStart)
{
    start = newStart;
}

void Process::executeCommand()
{

}

int Process::getStart() const
{
    return start;
}

int Process::getPid() const
{
    return pid;
}

void Process::setPid(int newPid)
{
    pid = newPid;
}

int Process::getEnd() const
{
    return end;
}

void Process::setEnd(int newEnd)
{
    end = newEnd;
}

int Process::getSavedAkku() const
{
    return savedAkku;
}

void Process::setSavedAkku(int newSavedAkku)
{
    savedAkku = newSavedAkku;
}

int Process::getSavedPC() const
{
    return savedPC;
}

void Process::setSavedPC(int newSavedPC)
{
    savedPC = newSavedPC;
}

const std::vector<std::string> &Process::getBefehlsatz() const
{
    return befehlsatz;
}

const std::string &Process::getName() const
{
    return name;
}

int Process::getActiveTime() const
{
    return activeTime;
}

void Process::setActiveTime(int newActiveTime)
{
    activeTime = newActiveTime;
}
