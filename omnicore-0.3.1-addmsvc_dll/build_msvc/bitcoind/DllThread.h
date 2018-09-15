#pragma once

#include "DataHandler.h"
#include "bitcoind.h"


class CDataNotify {
public:
	//constructor
	CDataNotify();
	CDataNotify(int tp, const std::string& dt);

	enum { INIT_THREAD = 3, PAYLOAD_NOTIFY};
	int type;
	std::string data;
};

class CDllDataHandler : public CDataHandler<CDataNotify>
{
public:
	//constructor
	CDllDataHandler(void);

	//destructor
	~CDllDataHandler();
	void SetNetName(const char* name);
protected:
	virtual void DataFunc(CDataNotify& data);
	void InitOmni();
private:
	std::string _net_name;
};
