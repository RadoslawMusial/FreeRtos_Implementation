#ifndef OSAPI_MUTEX_FREERTOS_H
#define OSAPI_MUTEX_FREERTOS_H
#include "osapi.h"
#include "osapi_mutex_interferance.h"

namespace osapi {
	class Mutex: {
public:
bool locked;

public:
Mutex() : locked(false) {}


bool lock(unsigned int timeout) {
    if (locked) {
        return false;
    } else {
        locked = true;
        return true;
    }
}

void unlock() {
    locked = false;
}
};
	}
#endif // OSAPI_H