#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
using std::endl;
using std::cout;

class Mytask
{
public:
    void process()
    {
        ::srand(::time(nullptr));
        int number = ::rand() % 100;
        cout << ">> sub Thread " << pthread_self() << " Mytask: number = " << number << endl;
        ::sleep(1);
    }
    ~Mytask() { cout << "~Mytask()" << endl; }
};
int main()
{
    //智能指针托管

    Threadpool threadpool;
    threadpool.start();
    Mytask task;
    int cnt = 20;
    while(cnt--)
    {
        threadpool.addTask(std::bind(&Mytask::process, &task));
    }
    
    threadpool.stop();

    return 0;
}

