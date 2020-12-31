#include<string>
#include <locale>
#include <codecvt>

namespace arris {
namespace util {
//namespace str{
    std::wstring __stdcall string_to_wstring(const std::string& s)
    {
        using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
        static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
        return conv.from_bytes(s);
    }
    std::string __stdcall wstring_to_string(const std::wstring& s)
    {
        using default_convert = std::codecvt<wchar_t, char, std::mbstate_t>;
        static std::wstring_convert<default_convert>conv(new default_convert("CHS"));
        return conv.to_bytes(s);
    }
    std::string __stdcall ansi_to_utf8(const std::string& s)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
        return conv.to_bytes(string_to_wstring(s));
    }
    std::string __stdcall utf8_to_ansi(const std::string& s)
    {
        static std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
        return wstring_to_string(conv.from_bytes(s));
    }
	std::wstring __stdcall inttowstring(int para)
	{
		std::wstringstream ss;
		ss << para;
		std::wstring r = ss.str();
		return r;
	}
	std::string __stdcall inttostring(int para)
	{
		std::stringstream ss;
		ss << para;
		std::string r = ss.str();
		return r;
	}
	std::string __stdcall time2id()
	{
		struct tm t;
		time_t now;  //声明time_t类型变量
		time(&now);      //获取系统日期和时间
		localtime_s(&t, &now);   //获取当地日期和时间

		std::string year = inttostring(t.tm_year + 1900);
		std::string month;
		if ((t.tm_mon + 1) < 10)
		{
			month = "0" + inttostring(t.tm_mon + 1);
		}
		else
		{
			month = inttostring(t.tm_mon + 1);
		}

		std::string day;
		if (t.tm_mday < 10)
		{
			day = "0" + inttostring(t.tm_mday);
		}
		else
		{
			day = inttostring(t.tm_mday);
		}



		std::string hour;
		if (t.tm_hour < 10)
		{
			hour = "0" + inttostring(t.tm_hour);
		}
		else {
			hour = inttostring(t.tm_hour);

		}
		std::string min;
		if (t.tm_min < 10)
		{
			min = "0" + inttostring(t.tm_min);
		}
		else {
			min = inttostring(t.tm_min);
		}


		std::string sec;
		if (t.tm_sec < 10)
		{
			sec = "0" + inttostring(t.tm_sec);

		}
		else {
			sec = inttostring(t.tm_sec);
		}


		std::string format = year + month + day + hour + min + sec;
		return format;
	}
	std::wstring __stdcall wxtime()
	{
		struct tm t;
		time_t now;  //声明time_t类型变量
		time(&now);      //获取系统日期和时间
		localtime_s(&t, &now);   //获取当地日期和时间

		std::wstring year = inttowstring(t.tm_year + 1900);

		std::wstring month;
		if (t.tm_mon + 1 < 10)
		{
			month = TEXT("0") + inttowstring(t.tm_mon + 1);
		}
		else
		{
			month = inttowstring(t.tm_mon + 1);
		}

		std::wstring day;
		if (t.tm_mday < 10)
		{
			day = TEXT("0") + inttowstring(t.tm_mday);
		}
		else
		{
			day = inttowstring(t.tm_mday);
		}


		std::wstring hour;
		if (t.tm_hour < 10)
		{
			hour = TEXT("0") + inttowstring(t.tm_hour);

		}
		else {
			hour = inttowstring(t.tm_hour);
		}

		std::wstring min;
		if (t.tm_min < 10)
		{
			min = TEXT("0") + inttowstring(t.tm_min);

		}
		else
		{
			min = inttowstring(t.tm_min);
		}


		std::wstring sec;
		if (t.tm_sec < 10)
		{
			sec = TEXT("0") + inttowstring(t.tm_sec);

		}
		else
		{
			sec = inttowstring(t.tm_sec);

		}

		std::wstring format = year + TEXT("-") + month + TEXT("-") + day + TEXT(" ") + hour + TEXT(":") + min + TEXT(":") + sec;
		return format;
	}

    
//}//namespace str
}//namespace util
}//namespace arris