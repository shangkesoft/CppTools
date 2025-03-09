#pragma once

// 头文件
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/time.h>
#endif  // _WIND32
#include <cstdarg>
#include <cstring>
#include <typeinfo>
#include <stdio.h>
#include <locale>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>

#ifdef __ANDROID__
    #include <android/log.h>
#endif

#ifdef SHOW_LOG
#define BASIC_INFO __FILE__, __LINE__, __FUNCTION__

#define LOG_DEBUG(fmt, ...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::DEBUG, BASIC_INFO, SKS_NAMESPACE::Logger::Format(fmt, ##__VA_ARGS__).c_str() );
#define LOG_WARNING(fmt, ...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::WARNING, BASIC_INFO, SKS_NAMESPACE::Logger::Format(fmt, ##__VA_ARGS__).c_str() );
#define LOG_ERROR(fmt, ...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::ERR, BASIC_INFO, SKS_NAMESPACE::Logger::Format(fmt, ##__VA_ARGS__).c_str() );
#define LOG_INFO(fmt, ...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::INFO, BASIC_INFO, SKS_NAMESPACE::Logger::Format(fmt, ##__VA_ARGS__).c_str() );

#define LOG_DEBUG_VALUE(...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::DEBUG, BASIC_INFO, SKS_NAMESPACE::Logger::Format( "%s", SKS_NAMESPACE::Logger::Merge( SKS_NAMESPACE::Logger::ParamNames(#__VA_ARGS__), SKS_NAMESPACE::Logger::ParamValues(__VA_ARGS__) ).c_str() ).c_str() );
#define LOG_WARNING_VALUE(...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::WARNING, BASIC_INFO, SKS_NAMESPACE::Logger::Format( "%s", SKS_NAMESPACE::Logger::Merge( SKS_NAMESPACE::Logger::ParamNames(#__VA_ARGS__), SKS_NAMESPACE::Logger::ParamValues(__VA_ARGS__) ).c_str() ).c_str() );
#define LOG_ERROR_VALUE(...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::ERR, BASIC_INFO, SKS_NAMESPACE::Logger::Format( "%s", SKS_NAMESPACE::Logger::Merge( SKS_NAMESPACE::Logger::ParamNames(#__VA_ARGS__), SKS_NAMESPACE::Logger::ParamValues(__VA_ARGS__) ).c_str() ).c_str() );
#define LOG_INFO_VALUE(...) SKS_NAMESPACE::Logger::WriteLog( SKS_NAMESPACE::Logger::INFO, BASIC_INFO, SKS_NAMESPACE::Logger::Format( "%s", SKS_NAMESPACE::Logger::Merge( SKS_NAMESPACE::Logger::ParamNames(#__VA_ARGS__), SKS_NAMESPACE::Logger::ParamValues(__VA_ARGS__) ).c_str() ).c_str() );

#else // #ifdef SHOW_LOG

#define LOG_DEBUG(fmt, ...) {};
#define LOG_INFO(fmt, ...) {};
#define LOG_WARNING(fmt, ...) {};
#define LOG_ERROR(fmt, ...) {};

#define LOG_DEBUG_VALUE( ... ) {};
#define LOG_INFO_VALUE( ... ) {};
#define LOG_WARNING_VALUE( ... ) {};
#define LOG_ERROR_VALUE( ... ) {};

#endif // #ifdef SHOW_LOG else

namespace SKS_NAMESPACE
{

class Logger
{
public:
    enum LogLevel
    {
        DEBUG = 0,
        WARNING,
        ERR,
        INFO,
    };

    static std::string to_str(const std::string &val) { return val; }
    static std::string to_str(const char *val) { return val ? val : "(nullptr)"; }
    static std::string to_str(char *val) { return val ? val : "(nullptr)"; }
    static std::string to_str(char val) { return SKS_NAMESPACE::Logger::Format("%c", val); }
    static std::string to_str(const void *val) { return SKS_NAMESPACE::Logger::Format("%p", val); }
    static std::string to_str(void *val) { return SKS_NAMESPACE::Logger::Format("%p", val); }
    static std::string to_str(int val) { return SKS_NAMESPACE::Logger::Format("%d", val); };
    static std::string to_str(long val) { return SKS_NAMESPACE::Logger::Format("%ld", val); };
    static std::string to_str(long long val) { return SKS_NAMESPACE::Logger::Format("%lld", val); };
    static std::string to_str(unsigned val) { return SKS_NAMESPACE::Logger::Format("%u", val); };
    static std::string to_str(unsigned long val) { return SKS_NAMESPACE::Logger::Format("%lu", val); };
    static std::string to_str(unsigned long long val) { return SKS_NAMESPACE::Logger::Format("%llu", val); };
    static std::string to_str(float val) { return SKS_NAMESPACE::Logger::Format("%f", val); };
    static std::string to_str(double val) { return SKS_NAMESPACE::Logger::Format("%f", val); };
    static std::string to_str(long double val) { return SKS_NAMESPACE::Logger::Format("%lf", val); };
    static std::string to_str(bool val) { return val ? "true" : "false"; }
    // static std::string to_str(wchar_t *val) { return to_str(std::wstring(val ? val : L"(nullptr)")); };
    // static std::string to_str(const std::wstring &val) { return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(val); }

    template <class T>
    static std::string to_str(const std::vector<T> &vec, const std::string &split = ",")
    {
        std::string re;
        for (const auto &itm : vec)
        {
            re += SKS_NAMESPACE::Logger::to_str(itm);
            re += split;
        }
        if (re.size() > split.size())
        {
            re.resize(re.size() - split.size());
        }
        return re;
    }
    template <class T>
    static std::string to_str(const std::list<T> &vec, const std::string &split = ",")
    {
        std::string re;
        for (const auto &itm : vec)
        {
            re += SKS_NAMESPACE::Logger::to_str(itm);
            re += split;
        }
        if (re.size() > split.size())
        {
            re.resize(re.size() - split.size());
        }
        return re;
    }
    template <class T>
    static std::string to_str(const std::set<T> &vec, const std::string &split = ",")
    {
        std::string re;
        for (const auto &itm : vec)
        {
            re += SKS_NAMESPACE::Logger::to_str(itm);
            re += split;
        }
        if (re.size() > split.size())
        {
            re.resize(re.size() - split.size());
        }
        return re;
    }
    template <class Key, class Value>
    static std::string to_str(const std::map<Key, Value> &vec, const std::string &split_kv = ":", const std::string &split_itm = ";")
    {
        std::string re;
        for (const auto &itm : vec)
        {
            re += SKS_NAMESPACE::Logger::to_str(itm.first);
            re += split_kv;
            re += SKS_NAMESPACE::Logger::to_str(itm.second);
            re += split_itm;
        }
        if (re.size() > split_itm.size())
        {
            re.resize(re.size() - split_itm.size());
        }
        return re;
    }

    static void WriteLogDefault(int nLevel, const char* srcFile, int line, const char* funcName, const char* msg)
    {
        auto log = Format( "%s:%d %s() %s", srcFile, line, funcName, msg );
#ifdef SHOW_LOG
#ifdef __ANDROID__
        __android_log_print(ANDROID_LOG_DEBUG + nLevel, "SsAlg", "%s", log.c_str() );
#endif // __ANDROID__
        char level = 'D';
        switch (nLevel)
        {
        case DEBUG:
            level = 'D';
            break;
        case WARNING:
            level = 'W';
            break;
        case ERR:
            level = 'E';
            break;
        case INFO:
            level = 'I';
            break;
        }

        printf("%s %c %s\n", SKS_NAMESPACE::Logger::TimeStr().c_str(), level, log.c_str() );
#endif // SHOW_LOG
    }

    static void WriteLog(int nLevel, const char* srcFile, int line, const char* funcName, const char* msg)
    {
        auto func = WriteLogFunction();
        if ( func )
        {
            func(nLevel, srcFile, line, funcName, msg);
        }
    }

    static std::string Format(const char *fmt, ...)
    {
        std::string strRe;
#if defined _MSC_VER && _MSC_VER < 1900
        va_list ptr;
        va_start(ptr, fmt);
        int nLen = _vscprintf(fmt, ptr);
        if (nLen <= 0)
        {
            return "";
        }
        strRe.resize(nLen + 1);

        vsprintf_s(&strRe[0], (int)strRe.size(), fmt, ptr);
        va_end(ptr);
        strRe.resize(nLen);
#else
        va_list ap;

        va_start(ap, fmt);
        strRe.resize(100);
        int size = vsnprintf(&strRe[0], (int)strRe.size(), fmt, ap);
        va_end(ap);

        if (size >= (int)strRe.size())
        {
            strRe.resize(size + 1);
            va_start(ap, fmt);
            size = vsnprintf(&strRe[0], (int)strRe.size(), fmt, ap);
            va_end(ap);
        }
        if (size < 0)
        {
            return "";
        }
        if (size < (int)strRe.size())
        {
            strRe.resize(size);
        }
#endif
        return strRe;
    }

    static std::string TimeStr(void)
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        std::time_t tt = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
#ifdef WIN32
        // 定义用于存储本地时间的结构体
        std::tm timeinfo;
        localtime_s(&timeinfo, &tt); // 获取本地时间

        // 使用 strftime 将时间格式化成字符串
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%m-%d %T", &timeinfo);

        // 输出格式化后的时间字符串，包含毫秒
        ss << buffer << "." << std::setw(3) << std::setfill('0') << ms.count() % 1000;
#else
        ss << std::put_time(std::localtime(&tt), "%m-%d %T") << "." << std::setw(3) << std::setfill('0') << ms.count() % 1000;
#endif
        return ss.str();
    }

    static std::string ParamValues(void) { return ""; }

    template <typename T, typename... Args>
    static std::string ParamValues(T first, Args... args)
    {
        auto re = to_str(first);
        auto after = ParamValues(args...);
        if (after.size())
        {
            re += "; ";
        }
        re += after;
        return re;
    }

    template <typename... Args>
    static std::string ParamNames(const char *ns) { return ns; }

    static std::vector<std::string> SplitString(const std::string &str, const std::string &strKey)
    {
        size_t end_position = 0;
        std::string str_tmp = str;
        std::vector<std::string> result;
        while (str.size() > 0 && end_position != std::string::npos)
        {
            end_position = str_tmp.find(strKey);
            std::string substr;
            if (end_position != std::string::npos)
            {
                substr = str_tmp.substr(0, end_position);
                str_tmp = str_tmp.substr(end_position + strKey.size(), str_tmp.size() - end_position);
            }
            else
            {
                substr = str_tmp.substr(0, str_tmp.size());
            }
            result.push_back(substr);
        }
        return result;
    }

    static std::string Merge(const std::string &names, const std::string &values)
    {
        std::vector<std::string> nms;
        std::vector<char> stack;
        size_t lastSubstrPos = 0;
        for (size_t i = 0; i < names.size(); i++)
        {
            switch( names.at(i) )
            {
            case '(':
                stack.push_back( names.at(i) );
                break;
            case ')':
                if ( stack.size() && stack.back() == '(')
                {
                    stack.pop_back();
                }
                else
                {
                    // 出错了！
                    return "";
                }
                break;
            case ',':
                if ( stack.empty() )
                {
                    // 分割字符串
                    nms.push_back( names.substr(lastSubstrPos, i - lastSubstrPos));
                    lastSubstrPos = i + 1;
                }
                break;
            }
        }
        if ( names.size() - lastSubstrPos )
        {
            nms.push_back( names.substr(lastSubstrPos, names.size() - lastSubstrPos));
        }

        auto vls = SplitString(values, "; ");

        size_t count = std::max(nms.size(), vls.size());
        nms.resize(count);
        vls.resize(count);
        std::string re;
        for (size_t i = 0; i < count; i++)
        {
            re += nms.at(i);
            re += ":";
            re += vls.at(i);
            if (i < count - 1)
            {
                re += "; ";
            }
        }
        return re;
    }

    typedef void (*WriteLogFuncType)( int level, const char* srcFile, int line, const char* funcName, const char* msg );

    /**
     * @brief 获得写日志的函数指针
     *
     * @return WriteLogFuncType
     */
    static WriteLogFuncType& WriteLogFunction( void )
    {
        static WriteLogFuncType func{WriteLogDefault};
        return func;
    }

private:

    Logger(void){};
    ~Logger(void){};
};

} // namespace SKS_NAMESPACE

