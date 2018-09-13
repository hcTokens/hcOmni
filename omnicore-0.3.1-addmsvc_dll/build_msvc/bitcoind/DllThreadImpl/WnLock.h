#pragma once


#include <boost/thread.hpp>

class CWnLock
{
public:
	CWnLock(void) {}
	~CWnLock(void) {}
public:
	virtual void lock() {m_lock.lock();}
	virtual void unlock() {m_lock.unlock();}
protected:
  boost::mutex m_lock;
};