#pragma once
#include <vector>
#include <string>

namespace  wd
{
class Configuration;

class SplitTool
{
public:
    SplitTool();
    virtual ~SplitTool();
    virtual std::vector<std::string> cut(const std::string & sentence)=0;
};
class SplitToolEN
: public SplitTool
{
public:
    SplitToolEN();
    ~SplitToolEN();
    std::vector<std::string> cut(const std::string & sentence);

private:
    Configuration & _conf;
};
class SplitToolNLPIR
: public SplitTool
{
public:
    SplitToolNLPIR();
    ~SplitToolNLPIR();
    std::vector<std::string> cut(const std::string & sentence);

private:
    Configuration & _conf;
};

class SplitToolCppJieba
: public SplitTool
{
public:
    SplitToolCppJieba();
    ~SplitToolCppJieba();
    std::vector<std::string> cut(const std::string & sentence);
private:
    Configuration & _conf;
};
}
