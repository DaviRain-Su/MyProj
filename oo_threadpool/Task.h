#pragma once

class Task
{
public:
    virtual void process()=0;
    virtual ~Task() {}
};

