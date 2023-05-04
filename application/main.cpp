#include <cstdio>
#include "FreeRTOS.h"
#include "task.h"
#include "test_osapi.h"

extern "C" void exit(int status) {
  while(1) { ; }
}

int main(void) {
  std::printf("Running tests\n");
  xTaskCreate(taskOSAPI_TEST, "test", configMINIMAL_STACK_SIZE + 512, NULL, 3, NULL);
  vTaskStartScheduler();
}















/*
#include "CUnit.h"
#include "Basic.h"
#include "FreeRTOS.h"
#include "task.h"
#include <cstdio>


int myPow(int x, unsigned int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result = result*x;
    }
    return result;
}



void TEST_myPow(void) {
    // test using standard test macro
    CU_ASSERT(1 == myPow(1,1));
    CU_ASSERT(0 == myPow(0,1));
    CU_ASSERT(1 == myPow(1,0));
    // test using macro better suited for comparing numbers:
    CU_ASSERT_EQUAL(4, myPow(2,2));
    CU_ASSERT_EQUAL(10, myPow(10,1));
    // this should fail:
    CU_ASSERT_EQUAL(0, myPow(2,2));
}



void threadCUnit(void* param) {
    CU_pSuite myTestSuite;
    // initialize CUnit
    CU_initialize_registry();
    // create new test suite
    myTestSuite = CU_add_suite("my test suite", NULL, NULL);
    // add test to test suite
    CU_add_test(myTestSuite, "my test", TEST_myPow);
    // set verbose mode
    CU_basic_set_mode(CU_BRM_VERBOSE);
    // run all tests
    CU_basic_run_tests();
    printf("\n");
    // print results
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    // deinitialize CUnit
    CU_cleanup_registry();
    vTaskDelete(NULL);
}





void threadHelloWorld(void* arg) {
    while (1) {
        std::printf("Hello world from %s\n", (char*)arg);
        vTaskDelay(1000);
    }
}  

int main(void) {
    std::printf("Hello world\n");
    //xTaskCreate(threadHelloWorld, "HELLO1", configMINIMAL_STACK_SIZE, (void*)"thread 1", 3, NULL);
    //xTaskCreate(threadHelloWorld, "HELLO2", configMINIMAL_STACK_SIZE, (void*)"thread 2", 3, NULL);
    //xTaskCreate(threadHelloWorld, "HELLO3", configMINIMAL_STACK_SIZE, (void*)"thread 3", 3, NULL);
    
    
    xTaskCreate(threadCUnit, "HELLO testing", configMINIMAL_STACK_SIZE, (void*)"thread 3", 3, NULL);
    vTaskStartScheduler();
}

extern "C" void exit(int status) {
    while(1) {
        ;
    }
}
*/







