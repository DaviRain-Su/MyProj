#pragma once
/*
#define logInfo(msg) \
    my_logInfo(__LINE__,__FILE__,__FUNCTION__,msg)
#define logWarn(msg)\
    my_logWarn(__LINE__,__FILE__,__FUNCTION__,msg)
#define logError(msg)\
    my_logError(__LINE__,__FILE__,__FUNCTION__,msg)
#define logDebug(msg)\
    my_logDebug(__LINE__,__FILE__,__FUNCTION__,msg)
*/
#include <stdlib.h>
#include <iostream>
#include <string>
#include <experimental/source_location>
using std::cout;
using std::endl;
using std::string;
using namespace std::experimental;

#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

using namespace log4cpp;
class Mylog
{
public:
    void Warn(const char *msg);
    void Error(const char *msg);
    void Debug(const char * msg);
    void Info(const char * msg);
    
    static Mylog * getInstance()
    {
        if(_pInstance == nullptr){
            _pInstance = new Mylog();
        }
        return _pInstance;
    }
    static void destory()
    {

        if(_pInstance)
        {
            
            Category::shutdown();
        }
    }
private:
    Mylog():root(Category::getRoot()){
        PatternLayout * ptnLayout1 = new PatternLayout();
        ptnLayout1->setConversionPattern("%d [%p] %m%n");
        PatternLayout * ptnLayout2 = new PatternLayout();
        ptnLayout2->setConversionPattern("%d [%p] %m%n");
        PatternLayout * ptnLayout3 = new PatternLayout();
        ptnLayout3->setConversionPattern("%d [%p] %m%n");

        OstreamAppender * ostreamAppender = new OstreamAppender("ostreamAppender",&cout);
        ostreamAppender->setLayout(ptnLayout1);

        FileAppender *fileAppender = new FileAppender("fileAppender","davarain.log");
        fileAppender->setLayout(ptnLayout2);

        RollingFileAppender * rollingAppender = new RollingFileAppender("rollingAppender","rollingAppender.log",5*1024,2);
        rollingAppender->setLayout(ptnLayout3);

        root.setAppender(ostreamAppender);
        root.addAppender(fileAppender);
        root.addAppender(rollingAppender);

        root.setPriority(Priority::DEBUG);
        cout << "Mylog()" << endl;
    }
    ~Mylog()
    {
        cout << "~Mylog()" << endl;
    }
private:
    Category & root;
    static Mylog * _pInstance;
};

Mylog * Mylog::_pInstance = nullptr;

void Mylog::Info(const char *msg)
{
    root.info(msg);
}
void Mylog::Warn(const char *msg)
{
    root.warn(msg);
}
void Mylog::Debug(const char *msg)
{
    root.debug(msg);
}
void Mylog::Error(const char *msg)
{
    root.error(msg);
}
void logInfo(const char *msg,const source_location& location= source_location::current())
{
    Mylog *log = Mylog::getInstance();  
    string tempMsg = msg;
    tempMsg = tempMsg + " doucument name:" + location.file_name() + " this is line: " + std::to_string(location.line()) + " func name: " + location.function_name();
    log->Info(tempMsg.c_str());
}
void logError(const char *msg, const source_location& location = source_location::current())
{
    Mylog *log = Mylog::getInstance();
    string tempMsg = msg;
    tempMsg = tempMsg + " doucument name:" + location.file_name() + " this is line: " + std::to_string(location.line()) + " func name: " + location.function_name();
    log->Error(tempMsg.c_str());
}
void logWarn(const char *msg,const source_location& location = source_location::current())
{
    Mylog *log = Mylog::getInstance();
    string tempMsg = msg;
    tempMsg = tempMsg + " doucument name:" + location.file_name() + " this is line: " + std::to_string(location.line()) + " func name: " + location.function_name();
    log->Warn(tempMsg.c_str());
}
void logDebug(const char *msg,const source_location& location = source_location::current())
{
    Mylog *log = Mylog::getInstance();
    string tempMsg = msg;
    tempMsg = tempMsg + " doucument name:" + location.file_name() + " this is line: " + std::to_string(location.line()) + " func name: " + location.function_name();
    log->Debug(tempMsg.c_str());
}

