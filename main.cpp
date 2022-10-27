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
        transCont.writeOut(i + 1, 0, "Ask");
    }

    string cmd;
    while(getline(cin, cmd)) {
        unique_lock<mutex> sigLock(sigmtx);
        long n = stoi(cmd.substr(1));
        // add transaction to queue
        if (cmd[0] == 'S') {
            transCont.writeOut(0, n, "Sleep");
            sigLock.unlock();
            transCont.helpSleep(n);
            sigLock.lock();
        } else {
            sig.wait(sigLock, []{return transCont.getCurrTrans() < transCont.getMaxQueue();});
            transCont.increment(cmd);
            transCont.writeOut(0, n, "Work");
            // signal a waiting thread to start doing stuff
            
            sigLock.unlock();
            sig.notify_one();
            sigLock.lock();
        }
    }
    doneInp = true;
    
    for (int i = 0; i < numThreads; i++) {
        if (consumers[i].joinable()) {
            cout << i << endl;
            consumers[i].join();
        } else {
            cout << i << "destroy" << endl;
            consumers[i].detach();
        }
    }
    // add end input
    cout << "hofusdba0" << endl;

    // close output File
    // transCont.closeOut();
    return(0);
}