#ifndef PROCESS_H
#define PROCESS_H
#include<vector>
#include<iostream>
#include<fstream>
class Process
{
public:
    Process(std::string);
    ~Process();
    void readFile(std::fstream& path);
    void setStart(int newStart);
    void executeCommand();
    int getStart() const;

    int getPid() const;
    void setPid(int newPid);

    int getEnd() const;
    void setEnd(int newEnd);

    int getSavedAkku() const;
    void setSavedAkku(int newSavedAkku);

    int getSavedPC() const;
    void setSavedPC(int newSavedPC);

    const std::vector<std::string> &getBefehlsatz() const;

    const std::string &getName() const;

    int getActiveTime() const;
    void setActiveTime(int newActiveTime);

private:
    std::string name;
    int start, end;
    int pid;
    int savedAkku;
    int savedPC;
    std::vector<std::string> befehlsatz;

    //preemtive

    int activeTime;

};

#endif // PROCESS_H
