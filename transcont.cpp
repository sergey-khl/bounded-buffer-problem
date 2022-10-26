#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <string>

#include "transcont.h"

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

void TransCont::setMaxQueue(int maxQueue) {
    maxQueue = maxQueue;
}