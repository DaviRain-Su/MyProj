#include "TaskQueue.h"
#include "Thread.h"

#include <memory>
using std::unique_ptr;

#include <iostream>
using std::endl;
using std::cout;

class Producer
{
public:
    void produce(TaskQueue & taskque)
    {
        ::srand(::time(nullptr));
        int cnt = 20;
        while(cnt--)
        {
    
            int number = ::rand() % 100;
            taskque.push(number);
            MutexLock mutex;
            MutexLockGuard lock(mutex);
            cout << "cnt = " << cnt <<" prodecer thread " << pthread_self()
                << " : producer a number = " << number << endl;
            ::sleep(1);

        }
    };
};
class Consumer
{
public:
    void consumer(TaskQueue & taskque)
    {
        int cnt = 20;
        while(cnt--)
        {
            int number = taskque.pop();
            MutexLock mutex;
            MutexLockGuard lock(mutex);
            cout << "Consumer thread " << pthread_self() <<" : consumer a  numner = " << number <<" cnt = " << cnt << endl;
            ::sleep(1);

        }

    };
};
int main()
{
    TaskQueue taskque(10);
    unique_ptr<Thread> prodeucer1(new Thread(
        std::bind(&Producer::produce, Producer(), std::ref(taskque)
   )));
    unique_ptr<Thread> prodeucer2(new Thread(
       std::bind(&Producer::produce, Producer(), std::ref(taskque)
  )));
  unique_ptr<Thread> consumer1(new Thread(
      std::bind(&Consumer::consumer, Consumer(), std::ref(taskque)
      )));
   unique_ptr<Thread> consumer2(new Thread(
     std::bind(&Consumer::consumer, Consumer(), std::ref(taskque)
      )));

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
