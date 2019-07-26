#include <iostream>
#include <string>
#include <cctype>
using std::string;
using std::endl;
using std::cout;

int main()
{
    string s = "AAAAA";
    for(auto &ch : s)
    {
        if(isupper(ch))
            ch = tolower(ch);
    }
    cout << s << endl;
    return 0;
}

