#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>

#include "helper.h"

using namespace std;


int main(int argc, char **argv) {
    int numThreads, logId;
    // validate args and get number of w
    checkArgs(argc, argv, numThreads, logId);

    int maxQueue = numThreads * 2;

    // init threads

    // open output file

    // initialize the queue
    queue<int> transactions;

    string cmd;
    while(getline(cin, cmd)) {

        // get input from user
        if (cmd[0] == 'T') {
            processTransaction(stoi(cmd.substr(1)), transactions);
        }
        if (cmd[0] == 'S') {
            parentSleep(stoi(cmd.substr(1)));
        }
    }

    return(0);
}