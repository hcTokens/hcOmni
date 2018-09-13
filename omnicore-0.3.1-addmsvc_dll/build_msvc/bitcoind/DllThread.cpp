
#include "DllThread.h"

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

void CDllDataHandler::DataFunc(int& t)
{
	std::cout << t << std::endl;
	if (t < 0)
	{
		return;
	}
	switch (t)
	{
	case 0:
	{
		InitOmni();
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
