#ifndef __TRANSCONT_H__
#define __TRANSCONT_H__
#include <queue>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <map>

class TransCont {
    public:
        void setMaxQueue(int mq);
        void increment(std::string trans);
        void incInp();
        std::string pop();
        int getMaxQueue();
        int getCurrTrans();
        bool done();
        void openOut(std::string logId);
        void closeOut();
        void startTime();
        void writeOut(int id, long n, std::string cmd);
        void writeSummary();
        void helpSleep(long n);
        void helpTrans(long n);
    private:
        struct timeval begin, end;
        int maxQueue;
        int numInput = 0;
        std::queue<std::string> transactions;
        std::ofstream out;
        std::map<std::string, int> summary;
};
extern TransCont transCont;
#endif