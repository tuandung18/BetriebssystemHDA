#ifndef RAM_H
#define RAM_H

#include<array>
class Process;
class page;
#define SIZE_OF_PAGE 64
class ram
{
public:
    ram();

    std::array<unsigned char, 256> getRamData();
    void setRamData(int pos, char data);
    std::array<std::pair<Process *, int>, 4> getFrame();
    /**
     * @brief isFull check if frame in ram is already full
     * @return false if not, true if yes
     */
    bool isFull();
    /**
     * @brief getUsedFrame get number of used frame
     * @return number of used frame
     */
    int getUsedFrame();
    void setFrameProcess(int frameIndex, Process* newProcess);
    void setFramePageIndex(int frameIndex, int pageIndexd);

    bool isEmpty();
    void printRAM();
private:
    std::array<unsigned char, 256> ramData;
    std::array<std::pair<Process*, int>, 4> frame;
};

#endif // RAM_H
