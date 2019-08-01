#include <iostream>
#include <json/json.h>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    ifstream ifs("cache.bat");
    if(!ifs.good()){
        perror(">> faill open file ");
    }
    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(ifs, root, false))
    {
        return -1;
    }
#if 1
    for(Json::iterator it = root.begin(); it != root.end(); ++it)
    {

        Json::Value add_vale = root["key"];
        for(size_t i = 0; i != add_vale.size(); ++i)
        {
            Json::Value temp_val = add_vale[i];
            string temp_word = temp_val["we"].asString();
            cout << "word " << temp_word << endl;
        }
    }
#endif
    return 0;
}

