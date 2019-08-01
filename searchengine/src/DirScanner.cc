#include "DirScanner.h"
#include "Configuration.h"

#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#define ERROR_CHECK(ret, retVal, funcName)\
{\
    if(ret == retVal)\
    {\
        printf("errno = %d\n", errno);\
        perror(funcName);\
    }\
}

#include <iostream>
using std::endl;
using std::cout;

namespace wd
{

DirScanner::DirScanner(const string & filepath)
: _filepath(filepath)
{
   cout << "DirScanner(const string & filepath)" << _filepath << endl;     
}

DirScanner::~DirScanner()
{
    cout << "~DirScanner()" << endl;
}
/*重载函数调用运算符*/
void DirScanner::operator()()
{
    traverse(_filepath);
}
/*返回设定的目录下的文件的路径集合*/
vector<string> & DirScanner::files()
{
    return _vecfiles;
}
/*遍历某个目录，得到这个目录下的文件路径的集合*/
void DirScanner::traverse(const string & dirname)
{
    DIR *dir;
    dir = opendir(dirname.c_str());
    ERROR_CHECK(dir, NULL, "opendir");
    struct dirent *p;
    char tmpPath[1024] = {0};
    while( (p = readdir(dir)) != NULL)
    {
        if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
        { continue;  }
        if(DT_DIR == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", dirname.c_str(), "/", p->d_name);
        }else if(DT_REG == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", dirname.c_str(), "/", p->d_name);
            _vecfiles.push_back(tmpPath); 
        }
    }
    closedir(dir);
}

void DirScanner::show_files()
{
    for(auto it = _vecfiles.begin(); it != _vecfiles.end(); ++it)
    {
        cout << " >> files " << *it << endl;
    }
}





}
