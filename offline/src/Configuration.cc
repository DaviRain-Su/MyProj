#include "../include/Configuration.h"

#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ERROR_CHECK(ret, retVal, funcName){\
    if(ret == retVal){\
        printf("errno=%d\n", errno);\
        perror(funcName);\
    }\
}

using std::ifstream;
using std::vector;
using std::string;

namespace  wd
{

Configuration::Configuration(const string & filepath)
: _filepath(filepath)
{
    std::ifstream in(_filepath);
    string line;
    char key[200] = {0};
    char val[1000] = {0};
    while(getline(in, line)){
        sscanf(line.c_str(), "%s%s", key, val );
        _configMap[key] = val;
    }
}
#if 0
void Configuration::getDir(char * path)
{
    DIR * dir;
    dir = opendir(_filepath.c_str());
    ERROR_CHECK(dir, NULL, "opendir");
    struct dirent *p;
    char tmpPath[1024] = {0};
    while((p = readdir(dir)) != NULL)
    {
        if(DT_DIR == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", path, "/",p->d_name);
            getDir(tmpPath);
        }
        if(DT_REG == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", path, "/", p->d_name);

        }
    }
    closedir(dir);
}
#endif
map<string, string>&
Configuration::getConfigMap()
{
    return _configMap;
}

}
