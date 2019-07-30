#include "../include/WorkProcess.h"
#include "../include/Mydict.h"
#include "../include/EditDistance.h"
#include "../include/Thread.h"
#include "CacheManger.h"
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
#if 0
    std::cout << "hash_table size = " << hash_table.size() << std::endl;
    std::cout << "hash_table---second size = " << hash_table["a"].size() << std::endl;
    for(auto iter = hash_table.begin(); iter != hash_table.end();++iter)
        std::cout << "hash_table---second size = " << iter->second.size() << std::endl;
#endif
    for(auto & ch : _queryWord)
    {
        for(auto iter = hash_table.begin(); iter != hash_table.end(); ++iter)
        {
#if 0
            printf("*****************\n");
#endif
            //英文的一个单词的字符和hash_table中的第一个key值进行比较
            string tmp_char(1, ch);
            std::cout << iter->first << std::endl;
            if(tmp_char == iter->first)
            {

                std::cout << "===" <<  iter->first << std::endl;
                auto insertIn = _result_word_indexs.end();
                set<int> iset =  iter->second;
                std::cout << " iset size === " << iset.size() << std::endl;
                auto Input_first = iset.begin();
                auto Input_last = iset.end();
#if 0
                for(auto iter = Input_first; iter != Input_last; ++iter)
                    std::cout << *iter << " ";
                std::cout << std::endl;
#endif
               _result_word_indexs.insert(insertIn, Input_first, Input_last); 
            }
        }
    }
#if 0
    for(auto iter = _result_word_indexs.begin(); iter!= _result_word_indexs.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;
#endif
}

void WorkProcess::statistic(vector<int> & ivec)
{
#if 1
    std::cout << "ivec size = " << ivec.size() << std::endl;
#endif
    //
    //
    //etc
    vector<pair<string, int>> dict = Mydict::getInstance()->getDict();
    
    for(int idx : ivec){
        pair<string, int> temp_ret = dict[idx];
        string temp_word = temp_ret.first;
#if 0
        std::cout << "the word : " <<temp_word << std::endl;
#endif
        int temp_frequency = temp_ret.second;
        int min_len_temp_word;
        min_len_temp_word = distance(_queryWord, temp_word);
        if(_resultQue.size() == 0)
        {
            _resultQue.push(MyResult(temp_word, min_len_temp_word, temp_frequency));
        }else 
        {
            if(temp_word == _resultQue.top()._word)
            {
                continue;
            }else
            {
                _resultQue.push(MyResult(temp_word, min_len_temp_word, temp_frequency));
            }
        }
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
    string str_idx = wd::current_thread::threadName;
    int cache_idx;
    try{
        cache_idx = std::stoi(str_idx);
    }catch(std::invalid_argument const & e)
    {
        std::cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const &e)
    {
        std::cout << "Integer overgflow: std::out_of_range thrown" << '\n';
    }

#if 1
    std::cout << "cache id " << cache_idx << std::endl;
#endif
    /*在cache 中查找 是否存在，若是不存在
     * 再去文件中查找，然后将查找到的数据存入cahce
     * 在将结果返回给客户端
     * 
     * */
    string temp_cache_result_queryWord = CacheManger::getCache(cache_idx).get(_queryWord);
    if(temp_cache_result_queryWord == "")
    {

        queryIndexTable();
        statistic(_result_word_indexs);
        int cnt = 3;
        Json::Value arr;
        Json::Value val;
        //Json::Value arr;
        //
        //处理队列为0


        std::cout<<"process begin"<<std::endl;
        for(int i = 0; i != cnt; i++)
        {
            //MyResult result = _resultQue.top();
            //  val[""] = Json::Value(_resultQue.top()._word);
            //  arr.append(Json::Value(val));
            //std::cout<<"process begin1111"<<_queryWord<<std::endl;
            std::cout<<_resultQue.size()<<std::endl;
            if(_resultQue.size() !=0)
            {
#if 0
                string str=_resultQue.top()._word;
                val[_queryWord.c_str()].append(str.c_str());
                //std::cout<<"process begin222"<<std::endl;
                _resultQue.pop();
#endif
#if 1
                val[_queryWord.c_str()] = Json::Value(_resultQue.top()._word.c_str());
                arr["key"].append(val);
                _resultQue.pop();
#endif
            }
            //std::cout<<"process begin333"<<std::endl;
            //出队列如果为0， 直接发送过去
            if(_resultQue.size() == 0)
            {
                val[_queryWord.c_str()].append("no answer");
                break;
            }
        }


        Json::StyledWriter sw;

        string res_str = sw.write(arr);
        //
        //先添加到缓存中在发送过去
        CacheManger::getCache(cache_idx).addElement(_queryWord, res_str);
    #if 1
        //持久化
        CacheManger::getCache(cache_idx).writeToFile();
    #endif 
        _conn->sendInLoop(res_str);
    }else{
        _conn->sendInLoop(temp_cache_result_queryWord);
    }

}



}
