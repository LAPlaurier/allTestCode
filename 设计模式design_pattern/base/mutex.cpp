#include "mutex.h"

using namespace std;

Mutex::Mutex() {
    pthread_mutex_init(&_mutex, nullptr);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&_mutex);
}

bool Mutex::lock() {
    return pthread_mutex_lock(&_mutex) == 0;
}

bool Mutex::unlock() {
    return pthread_mutex_unlock(&_mutex) == 0;
}