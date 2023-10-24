#ifndef _MUTEX_H_
#define _MUTEX_H_
#include <pthread.h>

using namespace std;

class Mutex {
public:
    Mutex();
    ~Mutex();
    bool lock();
    bool unlock();
private:
    pthread_mutex_t _mutex;
};
#endif