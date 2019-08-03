#include "Configuration.h"
#include "DirScanner.h"
#include "FileProcessor.h"
#include "PageLib.h"
#include "WordSegmentation.h"
#include "PageLibPreprocessor.h"

#include <iostream>
using std::endl;
using std::cout;
using namespace wd;
#if 1
void test0()
{
    /*未处理去重生成网页库，和网页偏移库*/
    Configuration conf;
    
    FileProcessor filepro(conf);
    DirScanner dirsc(conf);
    PageLib pag(conf,dirsc, filepro);
    

    pag.create();
    pag.store();
    conf.show_stopWord();

}
#endif
void test1()
{
    /*网页库的预处理， 去除重复的网页库*/
    Configuration conf;
    WordSegmentation jieba; 
    
    
    
    PageLibPreprocessor pageProcess(conf,jieba); 
    pageProcess.doProcess();
    
}
int main()
{
    //test0();
    test1();

    return 0;
}

