#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>

#include "transcont.h"
#include "helper.h"


using namespace std;

int main(int argc, char **argv) {
    // i used mutex for critical sections and a condition variable to wait for transactions

    // start measuring time
    transCont.startTime();

    int numThreads;
    string logId;
    // validate args and get number of w
    checkArgs(argc, argv, numThreads, logId);

    int maxQueue = numThreads * 2;

    // init my sem monitor
    transCont.setMaxQueue(maxQueue);
    // open output file
    transCont.openOut(logId);

    // init threads
    thread consumers[numThreads];
    for (int i = 0; i < numThreads; i++) {
        consumers[i] = thread(processTransaction, i + 1);
        transCont.writeOut(i+1, 0, "Ask");
    }

    string cmd;
    while(getline(cin, cmd)) {
        // start critical section and unlock when need to wait or execute command
        unique_lock<mutex> sigLock(sigmtx);
        int n = stoi(cmd.substr(1));
        // add transaction to queue
        if (cmd[0] == 'S') {
            transCont.writeOut(0, n, "Sleep");
            sigLock.unlock();
            transCont.helpSleep(n);
            sigLock.lock();
        } else {
            sigLock.unlock();
            while (transCont.getCurrTrans() >= transCont.getMaxQueue()) {}
            sigLock.lock();
            transCont.increment(cmd);
            transCont.writeOut(0, n, "Work");
            // signal a waiting thread to start doing stuff
            sigLock.unlock();
            sig.notify_one();
            sigLock.lock();
        }
    }
    // once input is ended let the threads know
    unique_lock<mutex> sigLock(sigmtx);
    transCont.writeOut(0, 0, "End");
    doneInp = true;
    sigLock.unlock();
    sig.notify_all();
    
    
    // join all threads for clean exit
    for (int i = 0; i < numThreads; i++) {
        consumers[i].join();
    }
    // add end input
    transCont.writeSummary();

    // close output File
    transCont.closeOut();
    return(0);
}