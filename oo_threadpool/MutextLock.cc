#include "MutextLock.h"

MutexLock::MutexLock()
:_isLocking(false)
{
    CHECK(!pthread_mutex_init(&_mutex, NULL));
}
MutexLock::~MutexLock()
{
    assert(!_isLocking);
    CHECK(!pthread_mutex_destroy(&_mutex));
}

void MutexLock::lock()
{
    CHECK(!pthread_mutex_lock(&_mutex));
    _isLocking = true;
}
void MutexLock::unlock()
{
    _isLocking = false;
    CHECK(!pthread_mutex_unlock(&_mutex));
}
