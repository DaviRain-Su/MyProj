#include "Dictonary.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <string.h>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

Dictonary::Dictonary(){
    cout << "Dictonary()" << endl;
}
Dictonary::~Dictonary(){
    cout << "~Dictonary()" << endl;
}

void Dictonary::read(const std::string & filename)
{
    //打开文件
    ifstream input(filename);
    if(!input.good())
    {
        cout << "open file is failed!" << filename <<  endl;
    }

    std::vector<char> table({'`','~','!','@','#','$','%','^','*','(',')','-','=','+',
                            '_','=',',','.','/','?','"',',','.','<','>',':',':',';','}','{','[',']','0','1','2','3','4','5','6','7','8','9'});
    //将文章的标点符号删除
    std::string line;
    std::vector<std::string> file;
    while(std::getline(input, line))
    {
        for (auto & ch : line)
        {
            for(auto & c: table)
            {
                if(ch == c)
                    ch = ' ';
            }
        }
        file.push_back(line);
    }
    input.close();
    //保存删除标点后的文件 
    std::string outfile = filename + "out";
    ofstream output(outfile);
    if(!output.good())
    {
        cout << "open file is failed !" << outfile << endl;
    }
    
    for(auto & line : file)
    {
        output << line << "\n";
    }
    output.close();

    //读取删除标点后的文件
    ifstream in(outfile);
    if(!in.good())
    {
        cout << "open file failed !" << outfile << endl;
    } 
    
    std::vector<std::string> word;
    //分词
    char temp[20] = {0};
    while(std::getline(in, line))
    {
        auto i = line.begin();
        int k = 0;
        for(;i != line.end(); ++i)
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
                        word.push_back(tempWord);
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
    for(auto & w : word)
    {
        _map[w]++;
    }
}

void Dictonary::store(const std::string & filename)
{
    ofstream outfile(filename);
    if(!outfile.good())
    {
        cout << "open file failed, " << filename << endl;
    }

    for(auto &item : _map)
    {
        outfile << item.first  << "   " << item.second << "\n";
    }
    outfile.close();
}
