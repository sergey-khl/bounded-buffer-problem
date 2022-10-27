#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <string>
#include <sys/time.h>
#include <fstream>
#include <iomanip>

#include "transcont.h"
#include "tands.c"

using namespace std;


void TransCont::increment(string trans) {
    transactions.push(trans);
}

string TransCont::pop() {
    string val = transactions.front();
    transactions.pop();
    return val;
}

int TransCont::getMaxQueue() {
    return maxQueue;
}

int TransCont::getCurrTrans() {
    return transactions.size();
}

void TransCont::setMaxQueue(int mq) {
    maxQueue = mq;
}

void TransCont::openOut(string logId) {
    if (logId != "") {
        out.open("prodcon." + logId + ".log");
    } else {
        out.open("prodcon.log");
    }
}

void TransCont::startTime() {
    gettimeofday(&begin, 0);
}


void TransCont::writeOut(int id, long n, string cmd) {
    //https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    // assuming each line is at most 100 lines
    char outbuf[100];
    if (cmd == "Receive" || cmd == "Work") {    
        snprintf(outbuf, 100, "%.3f ID= %i Q= %i ", elapsed, id, getCurrTrans());
    } else {
        snprintf(outbuf, 100, "%.3f ID= %i      ", elapsed, id);
    }
    out << outbuf << setw(15) << std::left << cmd;
    if (cmd != "Ask") {
        out << n;
    }
    out << '\n';
    out.flush();
}

void TransCont::closeOut() {
    out.close();
}

void TransCont::helpSleep(long n) {
    Sleep(n);
}

void TransCont::helpTrans(long n) {
    Trans(n);
}