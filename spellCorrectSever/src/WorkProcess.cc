#include "../include/WorkProcess.h"
#include "../include/Mydict.h"
#include "../include/EditDistance.h"

namespace  wd
{
WorkProcess::WorkProcess(const string & queryword, const TcpConnectionPtr & conn)
    : _queryWord(queryword)
    , _conn(conn)
    {}

//处理与要比对的单词单词， 将候选此的索记录下来
void WorkProcess::queryIndexTable()
{
    string response = _queryWord;
    map<string, set<int>> hash_table = Mydict::getInstance()->getIndecTable();
    for(auto & ch : _queryWord)
    {
        for(auto iter = hash_table.begin(); iter != hash_table.end(); ++iter)
        {
            //英文的一个单词的字符和hash_table中的第一个key值进行比较
            if(string(1,ch) == iter->first)
            {
                auto insertIn = _result_word_indexs.end();
                auto Input_first = iter->second.cbegin();
                auto Input_last = iter->second.cend();
               _result_word_indexs.insert(insertIn, Input_first, Input_last); 
            }
        }
    }
}

void WorkProcess::statistic(vector<int> & ivec)
{
    //
    for(auto elem : ivec)
        std::cout << "elem " << elem << std::endl;
    //
    //
    //etc
    vector<pair<string, int>> dict = Mydict::getInstance()->getDict();
    
    for(int idx : ivec){
        pair<string, int> temp_ret = dict[idx];
        string temp_word = temp_ret.first;
        std::cout << "the word : " <<temp_word << std::endl;
        int temp_frequency = temp_ret.second;
        int min_len_temp_word;
        min_len_temp_word = distance(_queryWord, temp_word);
        _resultQue.push(MyResult(temp_word, min_len_temp_word, temp_frequency));
    }
}

int WorkProcess::distance(const string & lhs, const string & rhs)
{
    return editDistance(lhs, rhs);
}
//运行在线程池中的一个子线程中
void WorkProcess::process()
{

    //decode
    //computer
    //encode
    //处理业务逻辑
    //要返回给客户端的消息由线程计算线程）完成数据的发送， 在设计上来说，是不合理的
    //数据发送的工作要交给IO线程（Reactor所在的线程)完成
    //将send的函数的执行延迟到IO线程去操作
    queryIndexTable();
    statistic(_result_word_indexs);
    int cnt = 3;
    Json::Value val;
    //Json::Value arr;
    std::cout<<"process begin"<<std::endl;
    for(int i = 0; i != cnt; i++)
    {
        //MyResult result = _resultQue.top();
      //  val[""] = Json::Value(_resultQue.top()._word);
      //  arr.append(Json::Value(val));
    std::cout<<"process begin1111"<<_queryWord<<std::endl;
        std::cout<<_resultQue.size()<<std::endl;
        string str=_resultQue.top()._word;
        val[_queryWord.c_str()].append(str.c_str());
    std::cout<<"process begin222"<<std::endl;
        _resultQue.pop();
    std::cout<<"process begin333"<<std::endl;
    }
    

    Json::StyledWriter sw;

    string res_str = sw.write(val);
    //
    //
    //
    _conn->sendInLoop(res_str);
}



}
