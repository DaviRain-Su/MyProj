#include "../include/SpellcorrectSever.h"


#include <iostream>
using std::cout;
using std::endl;
using namespace wd;



int main()
{
    
    SpellcorrectSever spellsever("../conf/my.bat");
    spellsever.start();

    return 0;
}

