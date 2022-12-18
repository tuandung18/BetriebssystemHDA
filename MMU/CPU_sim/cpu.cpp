#include "cpu.h"
#include"programcounter.h"
#include"akkumulator.h"
#include"process.h"
#include<unistd.h>
#include<ram.h>
#include<mmu.h>
#include<virtualmemory.h>
#include<page.h>
#define tab "\t"
#define log(x) std::cout << x << std::endl;
CPU::CPU() :takt(0)
{
    akku = new akkumulator;
    pc = new programCounter;
    Process* init = new Process("test_init");
    activeProcess = init;

    //TODO: delete this
    for(unsigned int i{}; i < memory.size(); i++) {
        memory.at(i) = 0;
    }
    //prak 3
    mem = new ram;
    vm = new virtualMemory;
    MMU = new mmu(mem, vm);


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
//    if(!mem->isEmpty()){
//        for(unsigned int i{}; i < mem->getFrame().size(); i++) {
//            if(mem->getFrame().at(i).first != nullptr) {
//                page* p = mem->getFrame().at(i).first->getPage(mem->getFrame().at(i).second);
//                if(p->getReferenziert()) {
//                    p->setReferenziert(0);
//                    p->setNruCounter(0);
//                }
//                else {
//                    p->incrementCounter();
//                }
//            }
//        }
//    }
    resetReferenceBit();
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
                case 'R': {
                    value = getBefehlValue();
                    readFromRam(value);
                    activeProcess->setSavedPC(pc->getValue());
                    break;
                }
                case 'W': {
                    value = getBefehlValue();
                    writeToRam(value);
                    activeProcess->setSavedPC(pc->getValue());
                    break;
                }
            default:
                break;
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
    std::cout << "number" << tab << "Data" << tab << "Page" <<
                 tab << "RBit" << tab << "MBit" << tab << "nruCounter" << std::endl;
    printDisk();
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
    std::fstream path("/home/edward/git/CPU_SIM/CPU_Simulator/CPU_sim/test_program/" + fileName);
    Process* n_Process = new Process(fileName);
    n_Process->setStart(takt);
    activeProcess->setSavedPC(pc->getValue());
    activeProcess->setSavedAkku(akku->getValue());
    akku->setValue(0);
    pc->setValue(0);
    readyProcess.push_back(activeProcess);
    activeProcess = n_Process;
    vm->addNewProcess(activeProcess);

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


//TODO: change the value that is saved and read from RAM to hex, we here we still write and read as int
//also read should only read one byte and write only write 1 byte to the address
void CPU::readFromRam(std::string& value) {
    //address is position (in array) of the address that we need

    //this->akku->load((int)memory.at(address));
    //std::cout << (int)memory.at(address) << std::endl;
    int frameIndex{};
    bool ifExist = MMU->checkIfExistsPage(activeProcess, MMU->calculatePage( MMU->convertHexaToInt(value)));
    //frameIndex = MMU->getExistsPage(activeProcess, MMU->calculatePage( MMU->convertHexaToInt(value)));
    //if page already on the ram
    if(ifExist){
        //log("yes");
        this->akku->load(mem->getRamData().at(frameIndex*SIZE_OF_PAGE + calculateOffset(MMU->convertHexaToInt(value))));
    }
    else {
        if(!mem->isFull()) {
            MMU->addPage(activeProcess, value);
        }
        else {
            MMU->swapPage(activeProcess, value);
        }
        frameIndex = MMU->checkIfExistsPage(activeProcess, MMU->calculatePage( MMU->convertHexaToInt(value)));
        this->akku->load(mem->getRamData().at(frameIndex*SIZE_OF_PAGE + calculateOffset(MMU->convertHexaToInt(value))));
    }
    int pageIndex = MMU->calculatePage( MMU->convertHexaToInt(value));

    activeProcess->getPage(pageIndex)->setReferenziert(1);

}
void CPU::writeToRam(std::string& value) {

    //memory.at(address) = (char)this->akku->getValue();
    //std::cout << address << std::endl;
    int frameIndex{};
    bool ifExist = MMU->checkIfExistsPage(activeProcess, MMU->calculatePage( MMU->convertHexaToInt(value)));
    //frameIndex = MMU->getExistsPage(activeProcess, MMU->calculatePage( MMU->convertHexaToInt(value)));

    //if page already on the ram
    if(ifExist){

        //mem->setRamData(pos, (char)this->akku->getValue());
        mem->getRamData().at(frameIndex*SIZE_OF_PAGE + calculateOffset(MMU->convertHexaToInt(value))) = (char)this->akku->getValue();
    }
    else {

        if(!mem->isFull()) {
            MMU->addPage(activeProcess, value);

        }
        else {
            MMU->swapPage(activeProcess, value);
            //log("swapped");
        }
        //int pos = frameIndex*SIZE_OF_PAGE + calculateOffset(MMU->convertHexaToInt(value));
        frameIndex = MMU->getExistsPage(activeProcess, MMU->calculatePage( MMU->convertHexaToInt(value)));
        int pos = frameIndex*SIZE_OF_PAGE + calculateOffset(MMU->convertHexaToInt(value));
        //log(frameIndex);
        mem->setRamData(pos, (char)this->akku->getValue());
        //mem->getRamData().at(frameIndex*SIZE_OF_PAGE + calculateOffset(MMU->convertHexaToInt(value))) = (char)this->akku->getValue();
    }
//    log(MMU->calculatePage( MMU->convertHexaToInt(value)));
    int pageIndex = MMU->calculatePage( MMU->convertHexaToInt(value));
    activeProcess->getPage(pageIndex)->setReferenziert(1);
    activeProcess->getPage(pageIndex)->setModifiziert(1);

}

unsigned int CPU::calculateOffset(int address)
{
    return address%SIZE_OF_PAGE;
}

void CPU::printDisk()
{
    processVerlauf.at(0)->getPage(0)->printAll();
    for(volatile unsigned int i{}; i < vm->getDisk().size(); i++) {
        for(volatile unsigned int z{}; z < MAX_PAGE_OF_PROCESS; z ++) {
            for(volatile unsigned int x{}; x < SIZE_OF_PAGE; x++) {
                std::cout << x << tab << vm->getDisk().at(i)->getPage(z)->getPageData().at(x)
                          << tab << z
                          << tab << vm->getDisk().at(i)->getPage(z)->getReferenziert()
                          << tab << vm->getDisk().at(i)->getPage(z)->getModifiziert()
                          << tab <<  vm->getDisk().at(i)->getPage(z)->getNruCounter()
                          <<std::endl;
            }
        }
    }
}

void CPU::resetReferenceBit()
{
    if(!mem->isEmpty()) {
        for(auto& p : mem->getFrame()) {
            if(p.second == -1) {
                return;
            }
            page* f = p.first->getPageUsingFrame(p.second);
            if(f == nullptr) {
                break;
            }
            if(f->getReferenziert()) {
                if(f->getNruCounter() == 2) {
                    f->setReferenziert(0);
                    f->setNruCounter(0);
                }
                else {
                    f->incrementCounter();
                }
            }
        }
    }
}
