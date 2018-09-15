
#include "DllThread.h"

CDataNotify::CDataNotify() :
	type(0), data("")
{

}
CDataNotify::CDataNotify(int tp, const std::string& dt):
	type(tp), data(dt)
{
}

CDllDataHandler::CDllDataHandler(void)
{
}

CDllDataHandler::~CDllDataHandler()
{
}

void CDllDataHandler::SetNetName(const char* name)
{
	if (strcmp(name, "m") == 0)
	{
		_net_name = "";
	}
	else if (strcmp(name, "t") == 0)
	{
			_net_name = "testnet";
	}
	else if (strcmp(name, "s") == 0)
	{
		_net_name = "regtest";
	}

}

void CDllDataHandler::DataFunc(CDataNotify& data)
{
	switch (data.type)
	{
	case CDataNotify::INIT_THREAD:
		InitOmni();
	break;
	case CDataNotify::PAYLOAD_NOTIFY:
	{
		printf(data.data.c_str());
		//mastercore_handler_tx(tx, GetHeight(), nTxIdx++, pindexNew)
	} 
	break;
	}
}

void CDllDataHandler::InitOmni()
{
	if (_net_name.empty())
	{
		char* argv[] = { "-exe", "-txindex", "-server=1",  "-addnode=192.168.1.24", "-reindex-chainstate", "-debug=1" };
		main_import(6, argv);
	}
	else if (_net_name == "testnet")
	{
		char* argv[] = { "-exe", "-regtest", "-txindex", "-server=1",  "-addnode=192.168.1.24", "-reindex-chainstate", "-debug=1" };
		main_import(7, argv);
	}
	else if (_net_name == "regtest")
	{
		char* argv[] = { "-exe", "-regtest", "-txindex", "-server=1",  "-addnode=192.168.1.24", "-reindex-chainstate", "-debug=1" };
		main_import(7, argv);
	}
}
