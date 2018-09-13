#pragma once


#include "WnQueue.h"
#include "WnEvent.h"
#include <boost/thread.hpp>

// a pure virtual function
template <class T> class CDataHandler
{
public:
	CDataHandler(void) {Start();}
	virtual ~CDataHandler() {}

public:
	// 单个通知接口（一般不需调用）
	void NotifyOne() {m_event.notify_one();}

	// 全部通知接口（一般不需调用）
	void NotifyAll() {m_event.notify_all();}

	// 推入流数据
	void Put(T& t)
	{
		m_record_set.push(t);

		// 发送通知信号
		m_event.notify_one();
	}

	// 获取缓冲区buffer size的接口
	int BufferSize() { return m_record_set.size(); }

protected:
	// 处理数据的线程，可在运行时绑定
	virtual void DataThread()
	{
		while(true)
		{
			m_event.wait();
			while(!m_record_set.empty())
			{
				T t;
				if(m_record_set.get(t))
				{
					DataFunc(t);
				}
			}
		}
	}

	// 处理数据的函数，可在运行时绑定
	virtual void DataFunc(T& t) {}

// 以下为内部函数
protected:
	// 开始运行
	void Start()
	{
		boost::thread t(&CDataHandler::DataThread, this);
	}

protected:
	// 流数据集
	CWnQueue<T> m_record_set;

	// 信号
	CWnEvent m_event;	
};
