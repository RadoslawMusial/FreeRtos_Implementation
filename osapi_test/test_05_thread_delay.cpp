#include "CUnit.h"
#include "osapi.h"

class TestThread5 : public osapi::Thread
{
public:
    TestThread5() : Thread(3, 256, osapi::JOINABLE) { run(); }
private:    
    virtual void job() {
        sleep(5000);
    }
};


void TEST_ThreadDelay(void) {
    unsigned int start, stop;

    printf("Running test 5: thread delay                     ");

    // mark start time
    start = osapi::getSystemTime();
    // create thread - it should begin execution
    TestThread5 t;
    t.join(10000);
    // mark stop time
    stop = osapi::getSystemTime();
    // check timings
    CU_ASSERT(stop - start > 4900);
    CU_ASSERT(stop - start < 6000);
}
