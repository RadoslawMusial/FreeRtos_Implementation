#include "CUnit.h"
#include "osapi.h"

static volatile int runFlag;

class TestThread4 : public osapi::Thread
{
public:
    TestThread4() : Thread(3, 256, osapi::JOINABLE) { run(); }
private:
    virtual void job() {
        while (runFlag) {
            sleep(100);
        }
    }
};


void TEST_ThreadPriority(void) {

    printf("Running test 4: thread priority set and get      ");

    // set initial flag values
    runFlag = 1;
    // create thread - it should begin execution
    TestThread4 t;
    // test thread priority setting from outside the thread
    CU_ASSERT(true == t.setPriority(4));
    CU_ASSERT(4 == t.getPriority());
    // terminate thread
    runFlag = 0;
    t.join(1000);
}
