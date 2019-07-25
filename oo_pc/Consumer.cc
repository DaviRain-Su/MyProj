#include "Consumer.h"
#include "TaskQueue.h"

#include <unistd.h>

#include <iostream>
using std::endl;
using std::cout;

void Consumer::run()
{
    int cnt = 20;
    while(cnt--)
    {
        int number = _que.pop();
        cout << "Consumer thread " << pthread_self() <<" : consumer a  numner = " << number <<" cnt = " << cnt << endl;
        ::sleep(1);
    }
}
