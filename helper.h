#ifndef __HELPER_H__
#define __HELPER_H__
#include <mutex>
#include <condition_variable>
#include <string>


void checkArgs(int argc, char **argv, int &numThreads, std::string &logId);
void processTransaction(int id);
extern std::mutex sigmtx;
extern std::condition_variable sig;
extern int TransSave;
#endif