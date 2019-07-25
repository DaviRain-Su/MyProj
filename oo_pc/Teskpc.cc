#include "TaskQueue.h"
#include "Consumer.h"
#include "Producer.h"

#include <memory>
using std::unique_ptr;

#include <iostream>
using std::endl;
using std::cout;

int main()
{
    TaskQueue taskque(10);
    unique_ptr<Thread> prodeucer1(new Producer(taskque));
    unique_ptr<Thread> prodeucer2(new Producer(taskque));
    unique_ptr<Thread> consumer1(new Consumer(taskque));
    unique_ptr<Thread> consumer2(new Consumer(taskque));

    prodeucer1->start();
    prodeucer2->start();
    consumer1->start();
    consumer2->start();
    
    prodeucer1->join();
    prodeucer2->join();
    consumer1->join();
    consumer2->join();

    return 0;
}

