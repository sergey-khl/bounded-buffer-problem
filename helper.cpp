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
#include "tands.c"

using namespace std;

mutex sigmtx;
condition_variable sig;
TransCont transCont;

void checkArgs(int argc, char **argv, int &numThreads, int &logId) {
    if (argc == 3) {
        try {
            numThreads = stoi(argv[1]);
            logId = stoi(argv[2]);
        } catch (...) {
            cout << "incorrect calling arguments" << endl;
        }
    } else if (argc == 2) {
        try {
            numThreads = stoi(argv[1]);
            logId = 0;
        } catch (...) {
            cout << "incorrect calling arguments" << endl;
        }
    } else {
        cout << "incorrect calling arguments... exiting program" << endl;
        exit(0);
    }
}

void processTransaction() {
    while (1) {
        // lock and wait till we have a transaction to process
        unique_lock<mutex> sigLock(sigmtx);
        sig.wait(sigLock, []{return transCont.getCurrTrans() > 0;});
        string val = transCont.pop();
        // execute transaction
        if (val[0] == 'S') {
            Sleep(stoi(val.substr(1)));
        } else if (val[0] == 'T') {
            Trans(stoi(val.substr(1)));
        } else {
            cout << "invalid argument" << endl;
        }

        cout << "done " << val << endl;
    }
}