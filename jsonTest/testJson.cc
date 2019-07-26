#include <iostream>
#include <fstream>
#include <string>
#include <json/json.h>
using namespace std;

int main()
{
    ifstream ifs;
    ifs.open("test.json");
    if(!ifs.good()){
        cout << "cann't open file " << endl;
        return -1;
    }
    Json::Reader readr;
    Json::Value root;
    if(!readr.parse(ifs,root,false))
    {
        return -1;
    }
    Json::Value add_value = root["address"];
    for(size_t i = 0; i < add_value.size(); ++i)
    {
        Json::Value temp_value = add_value[i];
        string strName = temp_value["name"].asString();
        string strMail = temp_value["email"].asString();
        cout << "name: " << strName << " email: " << strMail << endl;
    }
    return 0;
}

