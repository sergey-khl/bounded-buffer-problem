#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>

void checkArgs(int argc, char **argv, int &numThreads, int &logId);
void processTransaction();
extern std::mutex sigmtx;
extern std::condition_variable sig;