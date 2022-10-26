#ifndef __TRANSCONT_H__
#define __TRANSCONT_H__
#include <queue>
#include <string>

class TransCont {
    public:
        void setMaxQueue(int maxQueue);
        void increment(std::string trans);
        std::string pop();
        int getMaxQueue();
        int getCurrTrans();
    private:
        int maxQueue;
        std::queue<std::string> transactions;
};
extern TransCont transCont;
#endif