#pragma once

#include "DataHandler.h"
#include "bitcoind.h"


class CDllDataHandler : public CDataHandler<int>
{
public:
	//constructor
	CDllDataHandler(void);

	//destructor
	~CDllDataHandler();
	void SetNetName(const char* name);
protected:
	virtual void DataFunc(int& t);
	void InitOmni();
private:
	std::string _net_name;
};