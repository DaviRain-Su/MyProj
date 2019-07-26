#include "../include/Configuration.h"

#include <iostream>
#include <map>
using std::map;

using std::cout;
using std::endl;
using namespace wd;
int main()
{
    Configuration conf;
    map<string, string> mmap;
    mmap = conf.getConfigMap();
    
    for(auto iter = mmap.begin(); iter != mmap.end(); ++iter)
        cout << "key : " << iter->first << " val : " << iter->second << endl;
    return 0;
}

