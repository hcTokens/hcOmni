
#include <stdio.h>
#include "DllThread.h"
#include "DllCommon.h"
#include "DllInc.h"

fnDllCallBack_int		g_Callback_int = NULL;
fnDllCallBack_char		g_Callback_char = NULL;
fnDllCallBack_charEx	g_Callback_charEx = NULL;
CDllDataHandler* g_DataHandler = NULL;

extern "C" __declspec(dllexport) void BtcStart(int nType, void* param)
{
	switch (nType)
	{
		case 0:
		{
			g_Callback_int = (fnDllCallBack_int)param;
		}
		break;
		case 1:
		{
			g_Callback_char = (fnDllCallBack_char)param;
		}
		break;
		case 2:
		{
			g_Callback_charEx = (fnDllCallBack_charEx)param;
		}
		break;
		case 3:
		{
			g_DataHandler = new CDllDataHandler;
			g_DataHandler->SetNetName((const char*)param);
			int i = 0;
			Sleep(100);
			g_DataHandler->Put(i);
		}
		break;
		
	}	
}

std::string FuncCallbackChar(int nType, const char* param)
{
	if (g_Callback_char) {
		char* ret = g_Callback_char(nType, param);
		if (ret)
		{
			return ret;
		}
	}
	return "";
}


std::string FuncCallbackCharEx(int nType, const char* param, int len)
{
	if (g_Callback_charEx) {
		char* ret = g_Callback_charEx(nType, param, len);
		if (ret)
		{
			return ret;
		}
	}
	return "";
}