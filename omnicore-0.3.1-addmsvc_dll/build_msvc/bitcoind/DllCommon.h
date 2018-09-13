#pragma once
#include "DllInc.h"

class CDllDataHandler;
typedef int (*fnDllCallBack_int)(int nType);
typedef char* (*fnDllCallBack_char)(int nType, const char* param);
typedef char* (*fnDllCallBack_charEx)(int nType, const char* param, int len);

extern fnDllCallBack_int		g_Callback_int;
extern fnDllCallBack_char		g_Callback_char;
extern fnDllCallBack_charEx		g_Callback_charEx;
extern CDllDataHandler* g_DataHandler;

std::string FuncCallbackChar(int nType, const char* param);
std::string FuncCallbackCharEx(int nType, const char* param, int len);