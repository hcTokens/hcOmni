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
	// ����֪ͨ�ӿڣ�һ�㲻����ã�
	void NotifyOne() {m_event.notify_one();}

	// ȫ��֪ͨ�ӿڣ�һ�㲻����ã�
	void NotifyAll() {m_event.notify_all();}

	// ����������
	void Put(T& t)
	{
		m_record_set.push(t);

		// ����֪ͨ�ź�
		m_event.notify_one();
	}

	// ��ȡ������buffer size�Ľӿ�
	int BufferSize() { return m_record_set.size(); }

protected:
	// �������ݵ��̣߳���������ʱ��
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

	// �������ݵĺ�������������ʱ��
	virtual void DataFunc(T& t) {}

// ����Ϊ�ڲ�����
protected:
	// ��ʼ����
	void Start()
	{
		boost::thread t(&CDataHandler::DataThread, this);
	}

protected:
	// �����ݼ�
	CWnQueue<T> m_record_set;

	// �ź�
	CWnEvent m_event;	
};
