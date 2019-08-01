#pragma once
#include "../include/TcpConnection.h"


#include <json/json.h>
#include <string>
using std::string;
#include <set>
using std::set;
#include <queue>
using std::priority_queue;
#include <vector>
using std::vector;

namespace wd
{

struct MyResult
{
    string _word;
    int _eidt_vaule;
    int _frequency;
    MyResult(const string & word = "", const int & value = 0, const int & frequency = 0)
        : _word(word), _eidt_vaule(value), _frequency(frequency)
    {}
};

class WorkProcess
{
public:
    WorkProcess(const string & msg, const TcpConnectionPtr & conn);

    ~WorkProcess() {}
    
    void process();
    void queryIndexTable();
    void statistic(vector<int> & ivec);
    int distance(const string & lsh, const string & rhs);
//    void response(Cache & cache);
    struct MyCompare
    {
        bool operator()(const MyResult & lhs, const MyResult & rhs)
        {
            //return lhs._eidt_vaule < rhs._eidt_vaule;i
            if(lhs._eidt_vaule > rhs._eidt_vaule)
            {
                return true;
            }else if(lhs._eidt_vaule == rhs._eidt_vaule)
            {
                if(lhs._frequency <  rhs._frequency)
                {
                    return true;
                }
            }
            return false;
        }
    };
private:
    string _queryWord;
    std::priority_queue<MyResult, vector<MyResult>, MyCompare> _resultQue;
    TcpConnectionPtr _conn;
    vector<int> _result_word_indexs;
};

}
