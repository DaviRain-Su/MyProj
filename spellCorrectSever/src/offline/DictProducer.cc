#include "../../include/DictProducer.h"
#include "../../include/SplitTool.h"

#include <string.h>
#include <sys/types.h>
#include <dirent.h>

//#include <sys/stat.h>
//#include <fcntl.h>

#define ERROR_CHECK(ret, retVal, funcName){\
    if(ret == retVal){\
        printf("errno=%d\n", errno);\
        perror(funcName);\
    }\
}

#include <iostream>
#include <fstream>
#include <cctype>
#include <utility>
using std::pair;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;

namespace wd
{

DictProducer::DictProducer(const string & dir)
: _dir(dir)
, _splitTool(nullptr)
{
    cout << "_dir >> " << _dir << endl;   
}
void DictProducer::build_dict()
{
    get_files();

    //process vector<string> _files;
    for(auto & iter : _files)
    {
       cout << ">> file: " << iter << endl;
       operatorEN(iter); 
    }
}

void DictProducer::build_index()
{
    vector<pair<string, int>> dics;
    for(auto iter = _dict.begin(); iter != _dict.end();++iter)
    {
        dics.push_back(make_pair(iter->first, iter->second));
    }

    size_t idx = 0;
    for(auto iter = dics.begin(); iter != dics.end(); ++iter)
    {
        auto word = iter->first;
        for(auto & ch : word)
        {
            //string 构造函数的使用sting(size_t count, charT );
            //将一个char 构造为string
            _hashtable[string(1,ch)].insert(idx);
        }
        idx++;
    }

}
void DictProducer::push_dict(const string & word)
{
    auto findIter = _dict.find(word);
   if(findIter == _dict.end())
       _dict[word]++;
   else{
        findIter->second++;
   }
}
void DictProducer::store_dict(const char * filepath)
{
    //涉及到了文件IO的使用输出到文件中
    ofstream output(filepath);
    if(!output.good()){
        cout << ">> ofstream open file error " << filepath << endl;
        return;
    }

    for(auto iter = _dict.begin(); iter != _dict.end(); ++iter)
    {
        output <<  iter->first << " " <<  iter->second << "\n";
    }
    output.close();
}
void DictProducer::store_index(const char * filepath)
{
    ofstream output(filepath);
    if(!output.good())
    {
        cout << ">> ofstream open file error " << filepath << endl;
        return;
    }
    for(auto iter = _hashtable.begin(); iter != _hashtable.end(); ++iter)
    {
        output  << iter->first << " ";
        for(auto it = (iter->second).begin(); it != (iter->second).end(); ++it )
        {
            output << *it << " ";
        }
        output << "\n";
    }
    output.close();

}
void DictProducer::show_files() const
{
#if 1
    for(auto iter : _files)
        cout << ">> file: " << iter << endl;
#endif

}
void DictProducer::show_dict() const
{
#if 1
    for(auto iter = _dict.begin(); iter != _dict.end(); ++iter)
    {
        cout <<  iter->first << " ---- " <<  iter->second << endl;
    }
#endif
}
void DictProducer::show_index() const
{
    for(auto iter = _hashtable.begin(); iter != _hashtable.end(); ++iter)
    {
        cout << iter->first << ": ";
        for(auto it = (iter->second).begin(); it != (iter->second).end(); ++it )
        {
            cout << *it << " ";
        }
        cout << endl;
    }
}
//void DictProducer::getDir(const char * path)
void DictProducer::get_files()
{
    DIR * dir;
    dir = opendir(_dir.c_str());
    ERROR_CHECK(dir, NULL, "opendir");
    struct dirent *p;
    char tmpPath[1024] = {0};
    while((p = readdir(dir)) != NULL)
    {
        if(!strcmp(p->d_name,".") || !strcmp(p->d_name,".."))
        {
            continue;
        }
        if(DT_DIR == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s",_dir.c_str() , "/",p->d_name);
            get_files();
        } else if(DT_REG == p->d_type)
        {
            sprintf(tmpPath, "%s%s%s", _dir.c_str(), "/", p->d_name);
            _files.push_back(tmpPath);
        }
    }
    closedir(dir);
}




void DictProducer::operatorEN(const string & filename)
{
    
    //打开文件
    ifstream input(filename);
    if(!input.good()){
        cout << "open file is failed!" << filename <<  endl;
    }
    //将文章的标点符号删除
    std::string line;
    std::vector<std::string> file;
    while(std::getline(input, line))
    {
        for (auto & ch : line)
        {
            if(isdigit(ch) || ispunct(ch))
                ch = ' ';
            ch = tolower(ch);
        }
        file.push_back(line);
    }
    input.close();
    
    std::vector<std::string> words;
    //分词
    char temp[20] = {0};
   for(auto lineno = file.begin(); lineno != file.end(); ++lineno)
    {
        auto i = lineno->begin();
        int k = 0;
        for(;i != lineno->end(); ++i)
        {
            //从75到92的分词核心，在于申请了一个用于存放单词的位置
            std::string tempWord;
            if(*i == ' ' || *i == '\n' || *i == '\t')
            {
                if(i == line.begin()){
                    continue;
                }else{
                    temp[k] = 0;
                    tempWord = std::string(temp);
                    if(tempWord.size() != 0){
                        words.push_back(tempWord);
                    }
                    k = 0;
                }
            }else{
                temp[k] = *i;
                k++;
            }
        }
    }
    //放入map<string, int>
    for(auto & word : words)
    {
        push_dict(word);
        //_dict[word]++;
    }
}

}
