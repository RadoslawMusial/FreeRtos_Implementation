#ifndef OSAPI_H
#define OSAPI_H
#define OSAPI_MUTEX_INTERFACE_H
#include <csignal>

// check if any operating system was selected
#if (!defined _WIN32) && (!defined OSAPI_USE_FREERTOS) && (!defined OSAPI_USE_RTX)
#error "Unable to select operating system for OSAPI. Provide a compiler definition: OSAPI_USE_FREERTOS or OSAPI_USE_RTX"
#endif

#include <csignal>
#include <cstring>


#ifdef _WIN32
#include "Windows.h"
#endif

#ifdef OSAPI_USE_FREERTOS
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#endif

#ifdef OSAPI_USE_RTX
#include "cmsis_os2.h"
#endif

#include "osapi_mutex_interface.h"
#include "osapi_thread_interface.h"

#ifdef _WIN32
// include windows implementation
#include "windows/osapi_mutex_windows.h"
#include "windows/osapi_recursive_mutex_windows.h"
#include "windows/osapi_thread_windows.h"
#endif

#ifdef OSAPI_USE_FREERTOS
// include FreeRTOS implementation
//#include "freertos/osapi_mutex_freertos.h"             //  -- TODO: uncomment this line to enable Mutex API
//#include "freertos/osapi_recursive_mutex_freertos.h"   //  -- TODO: uncomment this line to enable Mutex API
#include "freertos/osapi_thread_freertos.h"
#endif

#ifdef OSAPI_USE_RTX
// include RTX implementation
#include "rtx/osapi_mutex_rtx.h"
#include "rtx/osapi_recursive_mutex_rtx.h"
#include "rtx/osapi_thread_rtx.h"
#endif
#include "osapi_mortal_thread.h"
namespace osapi {
	class Mutex{
public:
bool locked  = false;




bool lock(unsigned int timeout) {
    if (locked) {
        return false;
    } else  {
			locked = true; 
        return true;
    }
}

void unlock() {
    locked = false;
}
};

class RecursiveMutex {
public:
bool locked = false;
int counter =0; 


bool lock (unsigned int timeout)
{
	if (locked  && counter == 0) 
	{
		return false; 
	}
	else
	{
	locked = true;
	counter = counter+1; // increase lock count
	return true;
	}
	}
	void unlock() {
	counter = counter -1; 
	if (locked && counter == 0) 
	{
		locked = false;
	}	
	}
	};


/**
	
 * This system-related function returns the number of system ticks
 * elapsed since the system was started.
 *
 * @return current value of the system tick counter
 */
unsigned int getSystemTime();

} // namespace osapi

#endif // OSAPI_H
