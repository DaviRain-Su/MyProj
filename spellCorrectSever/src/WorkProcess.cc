#include "../include/WorkProcess.h"
#include "../include/Mydict.h"
#include "../include/EditDistance.h"
#include "../include/Thread.h"
#include "CacheManger.h"
using std::wstring;

namespace  wd
{
WorkProcess::WorkProcess(const string & queryword, const TcpConnectionPtr & conn)
    : _queryWord(queryword)
    , _conn(conn)
    {}

std::wstring WorkProcess::StringToWstring(const std::string str)
{
    unsigned len = str.size() * 2;//预留字节数
    setlocale(LC_CTYPE, "");//必须调用此函数
    wchar_t *p = new wchar_t[len];//申请一段内存存放装换后的字符串
    mbstowcs(p,str.c_str(), len);//装换
    std::wstring str1(p);
    delete[] p;//释放申请的内存
    return str1;
}
std::string WorkProcess::WstringToString(const std::wstring str)
{
    //wstring to stirng
    unsigned len = str.size() * 4;
    setlocale(LC_CTYPE, "");
    char * p = new char[len];
    wcstombs(p, str.c_str(),len);
    std::string str1(p);
    delete []p;
    return str1;
}
//处理与要比对的单词单词， 将候选此的索记录下来
void WorkProcess::queryIndexTable()
{
    std::wstring response = StringToWstring(_queryWord);

    map<string, set<int>>& hash_table = Mydict::getInstance()->getIndecTable();
    
    int bitmap[100000] = {0};

    for(auto it = response.begin(); it != response.end();++it)
    {
        wstring wstr;
        wstr.push_back(*it);
        string str = WstringToString(wstr);
        statistic(hash_table[str], bitmap);
    }
#if 0
    for(auto iter = _result_word_indexs.begin(); iter!= _result_word_indexs.end(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;
#endif
}

void WorkProcess::statistic(set<int> & iset, int bitmap[])
{
#if 1
    std::cout << "ivec size = " << iset.size() << std::endl;
#endif
    //
    //
    //etc
    vector<pair<string, int>> dict = Mydict::getInstance()->getDict();
    
    for(int idx : iset)
    {
        if(bitmap[idx] == 0)
        {

            pair<string, int> temp_ret = dict[idx];
            string temp_word = temp_ret.first;
#if 0
            std::cout << "the word : " <<temp_word << std::endl;
#endif
            int temp_frequency = temp_ret.second;
            int min_len_temp_word;
            min_len_temp_word = distance(temp_word);
            _resultQue.push(MyResult(temp_word, min_len_temp_word, temp_frequency));
            bitmap[idx] = 1;
        }
    }
}

int WorkProcess::distance(const string & rhs)
{
    return editDistance(_queryWord, rhs);
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
        //statistic(_result_word_indexs);
        int cnt = 3;
        Json::Value arr;
        Json::Value val;
        //处理队列为0
        std::cout<<"process begin"<<std::endl;
        for(int i = 0; i != cnt; i++)
        {
            std::cout<<_resultQue.size()<<std::endl;
            if(_resultQue.size() !=0)
            {
#if 1
                string str=_resultQue.top()._word;
                arr[_queryWord.c_str()].append(str.c_str());
                //std::cout<<"process begin222"<<std::endl;
                _resultQue.pop();
#endif
#if 0
                val[""] = Json::Value(_resultQue.top()._word.c_str());
                arr[_queryWord.c_str()].append(val);
                _resultQue.pop();
#endif
            }
            //std::cout<<"process begin333"<<std::endl;
            //出队列如果为0， 直接发送过去
            if(_resultQue.size() == 0)
            {
                arr[_queryWord.c_str()].append("noAnswer");
                break;
            }
        }


        //Json::StyledWriter sw;
        Json::FastWriter writer;

        string res_str_noStytle = writer.write(arr);
        //
        //先添加到缓存中在发送过去
        std::cout << "cache_idx = " << cache_idx << std::endl;
        CacheManger::getCache(cache_idx).addElement(_queryWord, res_str_noStytle);
#if 0
        //持久化
        CacheManger::getCache(cache_idx).writeToFile();
#endif 
        _conn->sendInLoop(res_str_noStytle);
    }else{
        _conn->sendInLoop(temp_cache_result_queryWord);
    }
}



}
