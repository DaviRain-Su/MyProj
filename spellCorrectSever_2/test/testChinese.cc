#include <iostream>
#include <string>
using std::string;
using std::endl;
using std::cout;

size_t nBytesCode(const char ch)
{
    if(ch & (1 << 7))
    {
        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx)
        {
            if(ch & (1 << (6 - idx)))
            {
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}

size_t length(const std::string &  str)
{
    size_t ilen = 0;
    for(size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
int main()
{
    string str1 = "abc";
    string str2 = "苏胤榕";
    string str3 = "苏胤榕abc";
    cout << "str1 length  = " << length(str1) << endl;
    cout << "str1 size =  " << str1.size() << endl;
    cout << "str2 length = " << length(str2) << endl;
    cout << "str2 size  = " << str2.size() << endl;
    cout << "str3 length = " << length(str3) << endl;
    cout << "str3 size  = " << str3.size() << endl;
    return 0;
}

