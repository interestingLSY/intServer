#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>

namespace IntServer{

	// from xmrig: https://github.com/xmrig/xmrig/

	#define CSI                 "\x1B["     // Control Sequence Introducer (ANSI spec name)
	#define CLEAR               CSI "0m"    // all attributes off
	#define BRIGHT_BLACK_S      CSI "0;90m" // somewhat MD.GRAY
	#define BLACK_S             CSI "0;30m"

	#define RED_S               CSI "0;31m"
	#define RED_BOLD_S          CSI "1;31m"
	#define GREEN_S             CSI "0;32m"
	#define GREEN_BOLD_S        CSI "1;32m"
	#define YELLOW_S            CSI "0;33m"
	#define YELLOW_BOLD_S       CSI "1;33m"
	#define BLUE_S              CSI "0;34m"
	#define BLUE_BOLD_S         CSI "1;34m"
	#define MAGENTA_S           CSI "0;35m"
	#define MAGENTA_BOLD_S      CSI "1;35m"
	#define CYAN_S              CSI "0;36m"
	#define CYAN_BOLD_S         CSI "1;36m"
	#define WHITE_S             CSI "0;37m" // another name for LT.GRAY
	#define WHITE_BOLD_S        CSI "1;37m" // actually white

	#define RED_BG_BOLD_S       CSI "41;1m"
	#define GREEN_BG_BOLD_S     CSI "42;1m"
	#define YELLOW_BG_BOLD_S    CSI "43;1m"
	#define BLUE_BG_S           CSI "44m"
	#define BLUE_BG_BOLD_S      CSI "44;1m"
	#define MAGENTA_BG_S        CSI "45m"
	#define MAGENTA_BG_BOLD_S   CSI "45;1m"
	#define CYAN_BG_S           CSI "46m"
	#define CYAN_BG_BOLD_S      CSI "46;1m"
	#define BLACK_BOLD_S     CSI "1;30m"

	#define Critical(...)	::IntServer::Print(::IntServer::Log::Level::CRIT,	"crit",	##__VA_ARGS__)
	#define Error(...)		::IntServer::Print(::IntServer::Log::Level::ERROR,	"error",##__VA_ARGS__)
	#define Warning(...)	::IntServer::Print(::IntServer::Log::Level::WARN,	"warn",	##__VA_ARGS__)
	#define Notice(...)		::IntServer::Print(::IntServer::Log::Level::NOTI,	"noti",	##__VA_ARGS__)
	#define Info(...)		::IntServer::Print(::IntServer::Log::Level::INFO,	"info",	##__VA_ARGS__)
	#ifdef APP_DEBUG
	#define Debug(...)		::IntServer::Print(::IntServer::Log::Level::DEBUG,	"debug",##__VA_ARGS__)
	#else
	#define Debug(...)
	#endif

	namespace Log{
		enum class Level : int {
	        NONE = -1,
	        CRIT = 0,    // critical conditions
	        ERROR = 1,     // error conditions
	        WARN = 2, // warning conditions
	        NOTI = 3,  // normal but significant condition
	        INFO = 4,    // informational
	        DEBUG = 5,   // debug-level messages
	    };

		static const char *colors_map[] = {
		    RED_BG_BOLD_S,	// CRIT
		    RED_BOLD_S,		// ERR
		    YELLOW_BOLD_S,	// WARNING
		    WHITE_BOLD_S,	// NOTICE
		    WHITE_BOLD_S,	// INFO
		    WHITE_S			// DEBUG
		};

		template<typename T>
		inline void _PrintOne( const T &t ){
			std::cout << t;
		}

		template<typename T0, typename... Ts>
		void _Print( T0 t0 , Ts... ts ){
			_PrintOne(t0);
			if constexpr( sizeof...(ts) > 0 ){
				_PrintOne(' ');
				_Print(ts...);
			}else{
				_PrintOne('\n');
				std::cout.flush();
			}
		}
	};

	template<typename... Ts>
	void Print( Log::Level level , const char type[] , Ts... ts ){
		Log::_PrintOne(' ');
		int len = strlen(type);
		Log::_PrintOne(Log::colors_map[static_cast<int>(level)]);
		Log::_PrintOne(type);
		Log::_PrintOne(CLEAR);
		for( int i = 0 ; i < 6-len ; ++i )
			Log::_PrintOne(' ');

		Log::_Print(ts...);
	}
}
