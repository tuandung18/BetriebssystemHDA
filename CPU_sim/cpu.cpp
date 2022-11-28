#include "cpu.h"
#include"programcounter.h"
#include"akkumulator.h"
#include"process.h"
#include<unistd.h>
#define tab "\t"
CPU::CPU() :takt(0)
{
    akku = new akkumulator;
    pc = new programCounter;
    Process* init = new Process("init");
    activeProcess = init;
    execute();
}

void CPU::block()
{
    waitingTakt.push_back(takt+5);
    if(activeProcess!= nullptr) {
        activeProcess->setSavedAkku(akku->getValue());
        activeProcess->setSavedPC(pc->getValue());
        waitingProcess.push_back(activeProcess);
        if(!readyProcess.empty()) {
            activeProcess = readyProcess.at(0);
            akku->setValue(activeProcess->getSavedAkku());
            pc->setValue(activeProcess->getSavedPC());
            readyProcess.erase(readyProcess.begin());
        }
        else {setActiveProcess(nullptr);}
    }
}

bool CPU::idle()
{
    if(activeProcess == nullptr) {
        if(waitingProcess.empty()) {
            if(readyProcess.empty()) {
                return true;
            }
        }
    }
    return false;

}

void CPU::addTakt()
{
    takt++;
    if(activeProcess!= nullptr ) {
        if(activeProcess->getActiveTime() == quantum) {
            changeActiveProcess();
        }
        else {
            activeProcess->setActiveTime(activeProcess->getActiveTime()+1);
        }
    }
    if(!waitingTakt.empty()) {
        if(takt == waitingTakt.at(0)) {
            readyProcess.push_back(waitingProcess.at(0));
            waitingProcess.erase(waitingProcess.begin());
            waitingTakt.erase(waitingTakt.begin());
        }
    }
    if(activeProcess == nullptr) {
        if(!readyProcess.empty()) {
            activeProcess = readyProcess.at(0);
            akku->setValue(activeProcess->getSavedAkku());
            pc->setValue(activeProcess->getSavedPC());
            readyProcess.erase(readyProcess.begin());
        }
    }
}

void CPU::terminateProcess()
{
    activeProcess->setEnd(takt);
    activeProcess->setSavedAkku(akku->getValue());
    processVerlauf.push_back(activeProcess);
    activeProcess = nullptr;

}

void CPU::execute()
{
    while(!idle()) {
        if(activeProcess!=  nullptr) {
            befehl = activeProcess->getBefehlsatz().at(activeProcess->getSavedPC());
            std::string value;
            std::cout << takt << tab << activeProcess->getPid() << tab << activeProcess->getName() << tab << activeProcess->getSavedPC() <<
                         tab << akku->getValue() << tab << befehl <<std::endl;
            pc->setValue(pc->getValue()+1);
            switch(befehl.front()) {
                case'L': {
                    value = getBefehlValue();
                    akku->load(std::stoi(value));
                    activeProcess->setSavedPC(pc->getValue());
                    break;
                }
                case'A': {
                    value = getBefehlValue();
                    akku->add(std::stoi(value));
                    activeProcess->setSavedPC(pc->getValue());
                    break;
                }
                case'S': {
                    value = getBefehlValue();
                    akku->substract(std::stoi(value));
                    activeProcess->setSavedPC(pc->getValue());
                    break;
                }
                case'X': {
                    value = getBefehlValue();
                    execNewProcess(value);
                    activeProcess->setSavedPC(pc->getValue());
                    break;
                }
                case'Z': {
                    terminateProcess();
                    break;
                }
                case'P': {
                    activeProcess->setSavedPC(pc->getValue());
                    block();
                break;
                }


            }


        }
        else {
            std::cout << takt << tab << "-" << tab << "----" << tab << "----" << tab << "----" << std::endl;
        }
        addTakt();
        usleep(20000);
    }
    std::cout << "PID" << tab << "Name" << tab << "Start" <<
                 tab << "End" << tab << "Akku" << tab << "pc" << std::endl;
    for(uint i{}; i < processVerlauf.size(); i++) {
        printProcess(processVerlauf.at(i));
    }
}

int CPU::getTakt() const
{
    return takt;
}

std::string CPU::getBefehlValue()
{
    if(befehl.front()!= 'P' && befehl.front() != 'Z') {
        std::string value = befehl.substr(befehl.find(" ")+1, befehl.size());
        return value;
    }
    else
        return "";
}

void CPU::execNewProcess(std::string fileName)
{
    std::fstream path("/home/trung/BS/CPU_sim/test_program/" + fileName);
    Process* n_Process = new Process(fileName);
    n_Process->setStart(takt);
    activeProcess->setSavedPC(pc->getValue());
    activeProcess->setSavedAkku(akku->getValue());
    akku->setValue(0);
    pc->setValue(0);
    readyProcess.push_back(activeProcess);
    activeProcess = n_Process;

}

void CPU::printProcess(Process *p)
{
    std::cout << p->getPid() << tab << p->getName() << tab
              << p->getStart() << tab << p->getEnd() << tab
              << p->getSavedAkku() << tab << p->getSavedPC() << std::endl;
}

Process *CPU::getActiveProcess() const
{
    return activeProcess;
}

void CPU::setActiveProcess(Process *newActiveProcess)
{
    activeProcess = newActiveProcess;
}

akkumulator *CPU::getAkku() const
{
    return akku;
}

programCounter *CPU::getPc() const
{
    return pc;
}

int CPU::getQuantum() const
{
    return quantum;
}

void CPU::changeActiveProcess()
{
    readyProcess.push_back(activeProcess);
    activeProcess->setSavedPC(pc->getValue());
    activeProcess->setSavedAkku(akku->getValue());
    activeProcess = readyProcess.at(0);
    akku->setValue(activeProcess->getSavedAkku());
    pc->setValue(activeProcess->getSavedPC());
    readyProcess.erase(readyProcess.begin());
}
