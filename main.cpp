#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>

#include "helper.h"

using namespace std;


int main(int argc, char **argv) {
    int numThreads, logId;
    // validate args and get number of w
    checkArgs(argc, argv, numThreads, logId);

    int maxQueue = numThreads * 2;


    // open output file

    // initialize the queue
    queue<int> transactions;

    string cmd;
    while(getline(cin, cmd)) {

        // get input from user
        if (cmd[0] == 'T') {
            pthread_t tid;
            long arg = stoi(cmd.substr(1));
            if (pthread_create(&tid, NULL, processTransaction, (void *) arg) != 0) {
                perror("could not create thread");
            }
            if (pthread_join(tid, NULL) == 0) {
                cout << tid << " ended" << endl;
            } else {
                cout << "failed to wait thread" << endl;
            }
        }
        if (cmd[0] == 'S') {
            parentSleep(stoi(cmd.substr(1)));
        }
    }

    return(0);
}