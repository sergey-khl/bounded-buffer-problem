#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>

#include "helper.h"
#include "tands.c"

using namespace std;

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

void *processTransaction(void *arg) {
    //int simulate, queue<int> &transactions
    //transactions.push(simulate);
    Trans((long)arg);
    
    
    return(0);
}

void parentSleep(int time) {
    Sleep(time);
}