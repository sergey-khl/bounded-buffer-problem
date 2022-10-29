#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>
#include <mutex>
#include <condition_variable>

#include "transcont.h"
#include "helper.h"

using namespace std;

mutex sigmtx;
condition_variable sig;
TransCont transCont;
bool doneInp = false;

void checkArgs(int argc, char **argv, int &numThreads, string &logId) {
    if (argc == 3) {
        try {
            numThreads = stoi(argv[1]);
            logId = argv[2];
        } catch (...) {
            cout << "incorrect calling arguments" << endl;
        }
    } else if (argc == 2) {
        try {
            numThreads = stoi(argv[1]);
            logId = "";
        } catch (...) {
            cout << "incorrect calling arguments" << endl;
        }
    } else {
        cout << "incorrect calling arguments... exiting program" << endl;
        exit(0);
    }
}

void processTransaction(int id) {
    while (1) {
       
        // lock and wait till we have a transaction to process
        unique_lock<mutex> sigLock(sigmtx);
        
        sig.wait(sigLock, []{return transCont.getCurrTrans() > 0 || doneInp;});
        if (doneInp && transCont.done()) {
            break;
        }
        transCont.writeOut(id, 0, "Ask");
        // receive the transaction
        string val = transCont.pop();
        long n = stoi(val.substr(1));
        transCont.writeOut(id, n, "Receive");
        sigLock.unlock();
        // execute transaction
        transCont.helpTrans(n);
        // need to lock io
        sigLock.lock();
        transCont.writeOut(id, n, "Complete");
        
    }
}