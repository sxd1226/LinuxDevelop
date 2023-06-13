#pragma once
#ifdef _WIN64
#include <crtdbg.h>
#include <tchar.h>
#include <WinSock2.h>
#else

#include <wchar.h>
#include <iconv.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************
函数名：WCharToMultiChar
功能：宽字节转换为多字节
参数：
	无
返回值：
************************************************************************/




/************************************************************************
函数名：MultiCharToWChar
功能：多字节转换为宽字节
参数：
	无
返回值：
************************************************************************/

