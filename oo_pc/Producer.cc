#include "Producer.h"
#include "TaskQueue.h"

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
using std::endl;
using std::cout;

void Producer::run()
{
    ::srand(::time(nullptr));
    int cnt = 20;
    while(cnt--)
    {
        int number = ::rand() % 100;
        _que.push(number);
        cout << "cnt = " << cnt <<" prodecer thread " << pthread_self()
            << " : producer a number = " << number << endl;
//        ::sleep(1);
    }
}

