#include "../../include/DictProducer.h"
#include <iostream>
#include "../../include/Configuration.h"
#include "../../include/SplitTool.h"
using namespace wd;
int main()
{
    wd::SplitToolCppJieba jieba; 
   // SplitTool * base = new SplitToolCppJieba();
#if 1
    DictProducer dir("../data/CN", &jieba);
    /* dir.build_dict(); */
    /* dir.build_index(); */
    dir.build_cn_dict();
    //dir.build_cn_index();
    //dir.show_dict();
    //dir.show_files();
    //dir.show_index();
    //dir.store_dict("../data/wordCN/word_cn_dict.bat");
    //dir.store_index("../data/wordCN/word_cn_hashtable.bat");
#endif
    return 0;
}

