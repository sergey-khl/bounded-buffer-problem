#include <queue>
void checkArgs(int argc, char **argv, int &numThreads, int &logId);
void processTransaction(int simulate, std::queue<int> &transactions);
void parentSleep(int time);