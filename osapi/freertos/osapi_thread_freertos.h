#ifndef OSAPI_THREAD_FREERTOS_H
#define OSAPI_THREAD_FREERTOS_H

#include "osapi_thread_interface.h"
#include "osapi_mutex_interface.h"

namespace osapi {

/** Thread interface implementation for FreeRTOS. */
class Thread : public ThreadInterface
{
    public:
				int thread_priority;
				const char* thread_name;
				unsigned int thread_size;
				TaskHandle_t thread_handle;
				ThreadState threadState;
				SemaphoreHandle_t ThreadSemaphore;
				Joinable isThreadJoinable;
				
				
        /** Thread constructor.
         *  @param[in] priority thread priority
         *  @param[in] stackSize thread stack size in bytes
         *  @param[in] isJoinable decides if the thread supports join operation or not
         *  @param[in] name optional thread name
         */
        Thread(int priority, unsigned int stackSize, Joinable isJoinable, const char* name = "unnamed") {
            // TODO
						this->thread_priority = priority;
						this->thread_size = stackSize;
						this->thread_name = name;
						this->thread_handle = NULL;
						this->threadState = INACTIVE;
					  this->ThreadSemaphore = NULL;
						if(isJoinable == JOINABLE){
								ThreadSemaphore = xSemaphoreCreateBinary();
						}
						else 
						{
							ThreadSemaphore = NULL; 
						}
        }
				
			
				
				static void threadFunction(void* argument) {
						Thread* osapiThreadObject = reinterpret_cast<Thread*>(argument);
						if (osapiThreadObject) {
								osapiThreadObject->job();
						}
						if (osapiThreadObject->ThreadSemaphore != NULL){
								xSemaphoreGive(osapiThreadObject->ThreadSemaphore);
						}
						vTaskDelete(NULL); 
				}

        /** Virtual destructor required to properly destroy derived class objects. */
        virtual ~Thread() { }

        /** Runs the thread.
        *  @retval true if the thread was started successfully, 
        *  @retval false if the thread was not started successfully, or the thread was already running
        */
        virtual bool run() {
            // TODO
					
            if (this->threadState == INACTIVE) {
								BaseType_t xReturned = xTaskCreate(threadFunction, this->thread_name, this->thread_size, this, this->thread_priority, &this->thread_handle);
								if (xReturned == pdTRUE) {
										this->threadState = RUNNING;
										return true;
								}
						}
						return false;
        }

        /** Checks if the thread is running.
        *  @retval true if the thread is running
        *  @retval false if the thread is not running
        */
        virtual bool isRunning() {
						if (this->thread_handle != NULL) {
								if(eTaskGetState(thread_handle)==eRunning){
									
										return true;
										}
								else if (eTaskGetState(thread_handle)== eReady)
								{
										return true;
								}
								else if (eTaskGetState(thread_handle)== eBlocked)
								{
									
										return true;
								}
									else 
									{
									
										return false;
									}
									
								}
						return false;
						}
					
				
				

        /** Waits for the thread to finish executing, with a given timeout.
         *  @param timeout[in] number of milliseconds to wait for the thread to finish executing
         *  @retval true if the thread was successfully joined in the given time
         *  @retval false if the thread was not joined within the given time or the thread is not joinable at all
         */
        virtual bool join(unsigned int timeout) {
					if (this->ThreadSemaphore != NULL){
							if (xSemaphoreTake(this->ThreadSemaphore, timeout / portTICK_PERIOD_MS) == pdTRUE){
									this->threadState = INACTIVE;
									return true;
							}
							else{
									return false;
							}
					}
            return false;
        }

        /** Checks, if the thread is joinable.
         *  @retval true if the thread is joinable
         *  @retval false if the thread is not joinable
         */
        virtual bool isJoinable() {
						return (this->ThreadSemaphore != NULL);
				}

        /** Suspends thread execution.
         *  @retval true if the thread was suspended successfully
         *  @retval false if the thread was not suspended for some reason
         */
        virtual bool suspend() {
            if(this->thread_handle != NULL){
								vTaskSuspend(this->thread_handle);
								if(eTaskGetState(this->thread_handle) == eSuspended){
									return true;
								}
								else{
									return false;
								}
						}
						return false;
					}		

        /** Resumes thread execution.
         *  @retval true if the thread was resumed successfully
         *  @retval false if the thread was not resumed for some reason
         */
        virtual bool resume() {
            if(this->thread_handle != NULL){
								vTaskResume(this->thread_handle);
								return isRunning();
						}
            return false;
        }

        /** Sets thread priority
         *  @param[in] priority new thread priority
         *  @retval true if the priority for the thread was set successfully
         *  @retval false if the priority for the thread was not set successfully for some reason
         */
        virtual bool setPriority(int priority) {
          if(this->thread_handle != NULL){
							this->thread_priority = priority;
							vTaskPrioritySet(this->thread_handle, this->thread_priority);
							return true;
							}
							return false;
				}

        /** Gets the thread priority
         *  @return current thread priority
         */
        virtual int getPriority() {
            return uxTaskPriorityGet(this->thread_handle);
        }

        /** Gets thread name
         *  @return name of the thread
         */
        virtual const char* getName() {
            return this->thread_name ;
        }

        /** Gets the current state of the thread
         *  @return current state of the thread
         */
        virtual ThreadState getState() {
            if(this->threadState == INACTIVE){
							return this->threadState = INACTIVE;
						}
						else if (eTaskGetState(this->thread_handle)==eRunning) {
								
									return this->threadState = RUNNING;
						}
						else if (eTaskGetState(this->thread_handle)== eReady)
						{
									return this->threadState = READY;
						}
								else if (eTaskGetState(this->thread_handle)== eBlocked)
								{
									return this->threadState = BLOCKED;
								}
								else if (eTaskGetState(this->thread_handle)== eSuspended)
								{
									return this->threadState = SUSPENDED;
								}
								else 
								{
									return this->threadState = INACTIVE;
							}
								return this->threadState = INACTIVE;
						}
					
                      

        /** Gets the total size of the stack assigned for this thread
         *  @return total stack size in number of bytes
         */
        virtual unsigned int getTotalStackSize() {
            return this->thread_size;
        }

        /** Gets the size of the used stack for this thread
         *  @return number of bytes used on the stack
         */
        virtual unsigned int getUsedStackSize() {
						if(this->thread_handle != NULL) {
							return this->thread_size - uxTaskGetStackHighWaterMark(thread_handle);
						}
						return 0;
        }

    protected:

        /** Delays thread execution for a given time.
         *  @param time[in] number of milliseconds to delay thread execution
         */
        virtual void sleep(unsigned int time) {
            vTaskDelay(time);
        }
				
		private:
				//int priority;
				int stackSize;
				

};



} 

#endif // OSAPI_THREAD_FREERTOS_H
