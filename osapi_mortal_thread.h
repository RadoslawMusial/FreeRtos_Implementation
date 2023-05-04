#ifndef OSAPI_MORTAL_THREAD_H
#define OSAPI_MORTAL_THREAD_H
 
namespace osapi {
class MortalThread : public Thread
{
  private:
  sig_atomic_t killSignal;  
    
  public:
    MortalThread(int priority, unsigned int stackSize, const char* name = "unnamed") : Thread(priority, stackSize, JOINABLE, name) {
     killSignal = 0 ;
    }
 
    virtual ~MortalThread() {
      ;
    }                   
                        
    /** Sends termination signal to the thread. */
    void kill() {
      killSignal = 1;
    }
                        
  private:
    /** Implementation of the job method */
       void job(void) {
        begin();
    while( killSignal != 1){
        loop();
    }
        end();      
    } 
  protected:
        /** Initializes the thread. */
    virtual void begin() = 0;
                
        
        /** Lets the thread work. */
   virtual void loop() = 0;
           
        /** Cleans up the resources. */
   virtual void end() = 0;
};
};
#endif // OSAPI_MORTAL_THREAD_H