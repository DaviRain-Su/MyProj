#include "Configuration.h"
#include "DirScanner.h"
#include "FileProcessor.h"
#include "PageLib.h"

#include <iostream>
using std::endl;
using std::cout;
using namespace wd;
int main()
{
    Configuration conf;
    FileProcessor filepro(conf);
    DirScanner dirsc(conf);
    PageLib pag(conf,dirsc, filepro);

    pag.create();
    pag.store();

    return 0;
}

