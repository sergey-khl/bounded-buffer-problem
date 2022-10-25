#include <pthread.h>
#include <helper.h>

using namespace std;

SemMonitor::SemMonitor() {
    count = 0;
}

void SemMonitor::increment() {
    count += 1;
    pthread_mutex_lock(&sem);
}

void SemMonitor::decrement() {
    count -= 1;
    pthread_mutex_unlock(&sem);
}