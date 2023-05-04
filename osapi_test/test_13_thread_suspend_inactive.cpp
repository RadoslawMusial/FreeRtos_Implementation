#include "CUnit.h"
#include "osapi.h"

class TestThread13 : public osapi::Thread
{
public:
    TestThread13() : Thread(3, 256, osapi::NOT_JOINABLE) { }
private:
    virtual void job() { ; }
};


void TEST_ThreadSuspendInactive(void) {

    printf("Running test 13: thread suspend inactive         ");

    // create thread
    TestThread13 t;
	  // check that the thread is in INACTIVE state
	  CU_ASSERT(osapi::INACTIVE == t.getState());
	
	  // at this point it sould be impossible to suspend the thread
	  CU_ASSERT(false == t.suspend());
	  // nor resume it
	  CU_ASSERT(false == t.resume());
}
