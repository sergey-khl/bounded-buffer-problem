#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>

#include "transcont.h"
#include "helper.h"


using namespace std;

int main(int argc, char **argv) {
    int numThreads, logId;
    // validate args and get number of w
    checkArgs(argc, argv, numThreads, logId);

    int maxQueue = numThreads * 2;

    // open output file

    // init my sem monitor
    transCont.setMaxQueue(maxQueue);

    // init threads
    thread consumers[numThreads];
    for (int i = 0; i < numThreads; i++) {
        consumers[i] = thread(processTransaction);
    }

    string cmd;
    while(getline(cin, cmd)) {
        unique_lock<mutex> sigLock(sigmtx);
        // add transaction to queue
        transCont.increment(cmd);

        // signal a waiting thread to start doing stuff
        sigLock.unlock();
        sig.notify_one();
        sigLock.lock();
    }

    return(0);
}