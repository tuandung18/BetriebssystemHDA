#include "ram.h"
#include<iostream>
ram::ram()
{
    for(unsigned int i{}; i < ramData.size(); i++) {
        ramData.at(i) = 0;
    }
    for(unsigned int i{}; i < frame.size(); i++) {
        frame.at(i).first = nullptr;
        frame.at(i).second = -1;
    }
}

std::array<unsigned char, 256> ram::getRamData()
{
    return ramData;
}

void ram::setRamData(int pos, char data)
{
    this->ramData.at(pos) = data;
}

std::array<std::pair<Process *, int>, 4> ram::getFrame()
{
    return frame;
}

bool ram::isFull()
{
    for(unsigned int i{}; i < frame.size(); i++) {
        if(frame.at(i).first == nullptr) {
            return false;
        }
    }
    return true;
}

int ram::getUsedFrame()
{
    int usedFrame = 0;
    if(!isFull()) {
        for(unsigned int i{}; i < frame.size(); i++) {

            if(frame.at(i).first != nullptr) {
                usedFrame++;
            }
        }
    }
    return usedFrame;
}
void ram::setFrameProcess(int frameIndex, Process* newProcess) {
    this->frame.at(frameIndex).first = newProcess;
}

void ram::setFramePageIndex(int frameIndex, int pageIndexd)
{
    this->frame.at(frameIndex).second = pageIndexd;
}

bool ram::isEmpty()
{
    for(unsigned int i{}; i < frame.size(); i++ ){
        if(frame.at(i).first != nullptr) {
            return false;
        }
    }
    return true;
}

void ram::printRAM()
{

}
