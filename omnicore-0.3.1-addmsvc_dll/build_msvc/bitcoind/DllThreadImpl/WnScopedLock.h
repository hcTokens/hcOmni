#pragma once

#include "WnLock.h"

class CWnScopedLock : public CWnLock
{
public:
  CWnScopedLock(CWnLock& mutex);
  virtual ~CWnScopedLock(void);
public:
  virtual void lock() {return m_pMutex->lock();}
  virtual void unlock() {return m_pMutex->unlock();}
private:
  CWnLock* m_pMutex;
};
