#include "../include/SpellcorrectSever.h"
#include "CacheManger.h"


#include <iostream>
using std::cout;
using std::endl;
using namespace wd;



int main()
{
 

    SpellcorrectSever spellsever("../conf/my.bat");
    CacheManger::initCache();
    CacheManger::periodicUpdateCache();
    spellsever.start();

    return 0;
}

