
#include "Configuration.h"
#include <iostream>
using std::cout;
using std::endl;


int main()
{
    wd::Configuration conf;

    cout << "ip = " << conf.ip() << endl;
    cout << "port = " << conf.port() << endl;
    cout << "datafile = " << conf.datafileName() << endl;
    return 0;
}

