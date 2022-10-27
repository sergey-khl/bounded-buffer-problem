#ifndef __TRANSCONT_H__
#define __TRANSCONT_H__
#include <queue>
#include <string>
#include <fstream>
#include <sys/time.h>

class TransCont {
    public:
        void setMaxQueue(int maxQueue);
        void increment(std::string trans);
        std::string pop();
        int getMaxQueue();
        int getCurrTrans();
        void openOut(std::string logId);
        void closeOut();
        void startTime();
        void writeOut(int id, long n, std::string cmd);
        void helpSleep(long n);
        void helpTrans(long n);
    private:
        struct timeval begin, end;
        int maxQueue;
        std::queue<std::string> transactions;
        std::ofstream out;
};
extern TransCont transCont;
#endif