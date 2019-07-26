#include "Configuration.h"

#include <stdlib.h>

#include <fstream>
using std::ifstream;
#include <iostream>
//using namespace std;

namespace wd{
Configuration::Configuration(const string & confName)
: _confName(confName)
{
    establish();
}
//读取ip port datafile
void Configuration::establish()
{
    string  line;
    char ip[100] = {0};
    char port[10] = {0};
    char datafile[1000] = {0};

    std::ifstream in(_confName);
    if(!in.good())
    {
        perror("can't open file");
    }
    getline(in, line);
    sscanf(line.c_str(), "%s %s %s", ip, port, datafile);

    _ip = ip;
    _port = port;
    _datafile = datafile;

}

int Configuration::port()
{
    int port = 0;
    try{
        port = stoi(_port);
    }catch(std::invalid_argument const &e)
    {
        std::cout << "Bad input: std::invalid_argument thrown" << '\n';
    }catch(std::out_of_range const & e)
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
    }
    return port;
}





}
