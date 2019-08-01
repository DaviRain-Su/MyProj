#include "Configuration.h"
#include "DirScanner.h"
#include <iostream>
using std::endl;
using std::cout;
using namespace wd;
int main()
{

    //DirScanner scanner("../data/stopword");
    //scanner();
    //scanner.show_files();
    
    Configuration::getInstance()->show_stopWord();
    Configuration::getInstance()->showAll();
    return 0;
}

