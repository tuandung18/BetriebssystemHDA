#ifndef PROCESS_H
#define PROCESS_H
#include<vector>
#include<iostream>
#include<fstream>
#include<array>
#define MAX_PAGE_OF_PROCESS 16
class page;
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

    /**
     * @brief getPage get a page in the table
     * @param index position of page need
     * @return page required
     */
    page* getPage(int index) const;
    int getPageFrame(int index) const;
    void setPageFrame(int pageIndex, int frame);
    std::array<std::pair<page *, int>, 16> getPageTable() const;
    page* getPageUsingFrame(int frame);


private:
    std::string name;
    int start, end;
    int pid;
    int savedAkku;
    int savedPC;
    std::vector<std::string> befehlsatz;

    //preemtive

    int activeTime;
    std::array<std::pair<page*, int>,MAX_PAGE_OF_PROCESS> pageTable;

};

#endif // PROCESS_H
