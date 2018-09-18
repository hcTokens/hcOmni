
#include <stdio.h>
#include "DllThread.h"
#include "DllCommon.h"
#include "DllInc.h"
#include "../../src/omnicore/tx.h"

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
			Sleep(100);
			g_DataHandler->Put(CDataNotify(3, (const char*)param));
		}
		break;
		case 4:
			if (g_DataHandler)
			{
				//g_DataHandler->Put(CDataNotify(4, (const char*)param));

				std::string txId((const char*)param);
				UniValue Value;
				Value.read((const char*)param);
				CMPTransaction mp_obj;
				printf(txId.c_str());
				std::string Sender = Value["Sender"].get_str();
				std::string Reference = Value["Reference"].get_str();

				std::vector<unsigned char> vecTxHash = ParseHex(Value["TxHash"].get_str());
				std::vector<unsigned char> vecBlockHash = ParseHex(Value["BlockHash"].get_str());

				INT64 Block = Value["Block"].get_int64();
				INT64 Idx = Value["Idx"].get_int64();
				std::string ScriptEncode = Value["ScriptEncode"].get_str();
				std::vector<unsigned char> Script = ParseHex(ScriptEncode);
				INT64 Time = Value["Time"].get_int64();
				INT64 Fee = Value["Fee"].get_int64();

				mp_obj.unlockLogic();
				mp_obj.Set(uint256(vecTxHash), Block, Idx, Time);
				mp_obj.SetBlockHash(uint256(vecBlockHash));
				mp_obj.Set(Sender, Reference, Block, uint256(vecTxHash), Block, Idx, &(Script[0]), Script.size(), 3, Fee);
				mp_obj.interpretPacket();
				//mastercore_handler_tx(tx, GetHeight(), nTxIdx++, pindexNew);
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