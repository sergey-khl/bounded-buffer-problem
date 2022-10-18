#include <queue>
void checkArgs(int argc, char **argv, int &numThreads, int &logId);
void *processTransaction(void *arg);
void parentSleep(int time);