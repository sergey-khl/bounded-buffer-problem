#include <queue>
#include <pthread.h>

class SemMonitor {
    public:
        SemMonitor();
        void increment();
        void decrement();
    private:
        // init semaphore as global
        pthread_mutex_t sem;
        // count number of process
        int count;
};
extern SemMonitor semMonitor();
void checkArgs(int argc, char **argv, int &numThreads, int &logId);
void *processTransaction(void *arg);
void parentSleep(int time);
