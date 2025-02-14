#include "Calculate.h"
#include <QThread>
#include <QThreadPool>

#include "CalculateRunnable.h"

namespace ThreadDemo
{

	Calculate::Calculate(QObject* parent/*=nullptr*/)
	{
		m_ThreadPool = nullptr;
	}

	void Calculate::directDoSomeThing()
	{
		//!@ �����ⲿ���ýӿ���ۺ�����Ӧ�Ƿ���ͬһ�߳���
		auto test_thread_id = QThread::currentThreadId(); 
		int i = 1;
	}

	Calculate::~Calculate()
	{

	}

	void Calculate::startCalculate(const CalculateInputStruct aInput)
	{
		auto test_thread_id = QThread::currentThreadId(); // �鿴��ǰ�̵߳�id�ͽ����ࡢ�������id�Ƿ���ͬ

		m_ThreadPool = new QThreadPool();
		m_ThreadPool->setMaxThreadCount(aInput.threadMaxCount); // �����̳߳ص�����߳���Ϊ1
		for (int i = 0; i < aInput.calculateCount; i++)
		{
			CalculateRunnable* runnable = new CalculateRunnable(aInput.calculateCount - i);
			runnable->setAutoDelete(true); // ��������������Զ�ɾ��
			m_ThreadPool->start(runnable);

			//! ������Ӧ��ʽΪ��Ϣ����ʱ������emit CalculateFinished(); ������Ӧ��������ʹ��ֱ����Ӧ
			connect(runnable, &CalculateRunnable::runnableFinishedSignal, this, [&]() {emit updateProssorbarSignal(); }, Qt::DirectConnection);
		}
		m_ThreadPool->waitForDone(); // �ȴ������������
		emit calculateFinishedSignal();

		delete m_ThreadPool;
		m_ThreadPool = nullptr;
	}

	void Calculate::cancelCalculate()
	{
		if (m_ThreadPool)
		{
			m_ThreadPool->clear(); // ����̳߳�
			// 		delete mThreadPool;
			// 		mThreadPool = nullptr;
		}
	}

	void Calculate::doSomeThingSlot()
	{
		auto test_thread_id = QThread::currentThreadId();
		int i = 1;
	}

// 	void Calculate::testtMultiDataSlot(const QVector<double>& aXDatas, const QVector<double>& aYDatas)
	void Calculate::testtMultiDataSlot(const QVector<QStringList>& aDatas)
	{
// 		int x_data_size = aXDatas.size();
// 		int y_data_size = aYDatas.size();
// 		if (x_data_size != y_data_size)
// 		{
// 			return;
// 		}


		int data_size = aDatas.size();
		int i = 1;
	}

}