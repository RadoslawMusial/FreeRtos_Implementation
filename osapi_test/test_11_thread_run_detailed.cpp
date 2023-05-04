#include "CUnit.h"
#include "osapi.h"

static volatile int testFlag;
static volatile int runFlag = 1;

class TestThread11 : public osapi::Thread
{
public:
    TestThread11() : Thread(3, 256, osapi::JOINABLE) { ; }
private:
    virtual void job() {
        testFlag = 1;
			  while(runFlag) {
					sleep(5);
				}
    }
};

void TEST_ThreadRunDetailed(void) {

    printf("Running test 11: detailed thread run                ");
        
    // set initial test flag value
    testFlag = 0;
    // create thread
    TestThread11 t;
	  // thread should not be running at this point
    CU_ASSERT(false == t.isRunning());
	  // get number of tasks from FreeRTOS
	  unsigned int taskCount = uxTaskGetNumberOfTasks();
    // run the thread
    CU_ASSERT(true == t.run());
	  // this should increase task count in FreeRTOS
	  CU_ASSERT(taskCount+1 == uxTaskGetNumberOfTasks());
	  // it shouldn't be possible to run the thread again
    CU_ASSERT(false == t.run());	
    // wait a while
    vTaskDelay(10);
    // test result
    CU_ASSERT(1 == testFlag);
	  runFlag = 0;
	  CU_ASSERT(true == t.join(100));
	  // thread should not be running at this point
    CU_ASSERT(false == t.isRunning());
}
