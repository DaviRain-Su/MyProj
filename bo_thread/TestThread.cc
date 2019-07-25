#include "Thread.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;

class Mytask
{
public:
    void run()
    {
        ::srand(::clock());
        int cnt  = 20;
        while(cnt--){
            int num = ::rand() % 100;
            cout << "su thread id " << pthread_self()
                << ": number = " << num  << "-- IsRuninng:  "  << endl;
            ::sleep(1);
        }
    }
};

void task()
{
    ::srand(::clock());
    int cnt  = 20;
    while(cnt--){
        int num = ::rand() % 100;
        cout << "su thread id " << pthread_self()
            << ": number = " << num  << "-- IsRuninng:  "  << endl;
        ::sleep(1);
    }
}
int main()
{
    std::unique_ptr<Thread> thread(new Thread(
   //  std::bind(&Mytask::run, Mytask())
        task
      ));
    thread->start();

    thread->join();

    //MyThread thread1;
    //MyThread thread2 = thread1;

    return 0;
}

