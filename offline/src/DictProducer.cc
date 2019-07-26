#include "DictProducer.h"
#include "SplitTool.h"
#include <sys/types.h>
#include <dirent.h>

#define ERROR_CHECK(ret, retVal, funcName){\
    if(ret == retVal){\
        printf("errno=%d\n", errno);\
        perror(funcName);\
    }\
}

namespace wd
{

DictProducer::DictProducer(const string & dir)
: _dir(dir)
//, _splitTool()
{
    
}
void DictProducer::build_dict()
{
    getDir(_dir.c_str());
}

void DictProducer::getDir(char * path)
{
    DIR * dir;
    dir = opendir(path);
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
            _files.push_back(tmpPath);
        }
    }
    closedir(dir);
}
}
