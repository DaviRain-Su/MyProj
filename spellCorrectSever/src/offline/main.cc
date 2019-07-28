#include "../../include/DictProducer.h"
#include <iostream>
using namespace wd;

int main()
{
    DictProducer dir;
    dir.build_dict();
    dir.build_index();
    dir.show_dict();
    dir.show_files();
    dir.show_index();
    dir.store_dict("./data/wordEN/word_en_dict.bat");
    dir.store_index("./data/wordEN/word_en_hashtable.bat");
    return 0;
}

